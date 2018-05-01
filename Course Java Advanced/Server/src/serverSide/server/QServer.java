package serverSide.server;

import java.io.IOException;
import java.lang.reflect.Method;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import qClasses.QCodeAdapter;
import qClasses.QConnection;
import qClasses.QMessage;
import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.carComplementary.AnnotLeisurable;
import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.StationClosedException;
import serverSide.events.serverbl.QServerEventsListener;

public class QServer implements Runnable {

	/** Data fields */

	private QServerEventsListener qServerEventListener;

	private static QServer server;

	private ServerSocket welcomeSocket;
	private boolean onLine;

	private ArrayList<String> reflectionMethods;

	/*
	 * Server keeps track of : <key, value> = <carId,connection> In use for
	 * sending message back to a client that submitted a carId In use to check
	 * if such carId exists in the system
	 */
	private HashMap<String, SClient> trackingMap;
	/*
	 * 
	 * Primary use in case of disconnect
	 */
	private ArrayList<SClient> sclientsList;
	private ExecutorService executor;

	/** C'tor */
	private QServer(int port) throws IOException {

		welcomeSocket = new ServerSocket(port);
		trackingMap = new HashMap<String, SClient>();
		sclientsList = new ArrayList<>(3);
		reflectionMethods = new ArrayList<>(3);
		initReflectionMethods();

		executor = Executors.newCachedThreadPool();
		executor.execute(this);

	}// c'tor

	public static QServer getInstance(int port) throws IOException {
		if (server == null) {
			server = new QServer(port);
		}
		return server;
	}

	public void closeServer() {

		if (isOnLine()) {
			setOnLine(false);
			try {
				if (!welcomeSocket.isClosed())
					welcomeSocket.close();
			} catch (IOException e1) {
				e1.printStackTrace();
			}

			for (SClient sc : sclientsList) {
				sc.closeSClient();
				sc = null;
			}// for

			sclientsList.clear();
			executor.shutdownNow();
			executor = null;
			trackingMap.clear();
		}// if

	}//

	public synchronized boolean isOnLine() {
		return onLine;
	}//

	public synchronized void setOnLine(boolean onLine) {
		this.onLine = onLine;
	}

	// --------------------------------------------------------------------
	public void reportToClient(Car car, String msg) {
		synchronized (trackingMap) {
			int carId = -1;
			String carIdKey = "" + car.getId();
			if (checkIfExists(carIdKey)) {
				SClient client = trackingMap.get(carIdKey);
				if (car.getState() == CarStatus.carState.DONE) {
					removeCarFromTracking(carIdKey);
				}//
				else if ((car.getState() == CarStatus.carState.CLEANQUEUE)
						|| (car.getState() == CarStatus.carState.AUTOWASH)
						|| (car.getState() == CarStatus.carState.MANUALWASH)) {
					carId = car.getId();
				}//

				if (client.connection.isConnected()) {
					client.createMessageMsg(msg, carId);
				}// inner if
			}
		}// synchronized
	}

	private void removeCarFromTracking(String carId) {
		synchronized (trackingMap) {
			trackingMap.remove(carId);
		}
	}

	private boolean registerNewCarConnection(String carId, SClient client) {
		synchronized (trackingMap) {
			if (!checkIfExists(carId)) {
				trackingMap.put(carId, client);
				return true;
			} else {
				return false;
			}
		}// synchronized
	}

	private boolean checkIfExists(String key) {
		// Called from a synchronized method.
		return (trackingMap.containsKey(key));
	}

	private void removeSClientFromTrackingMap(SClient sc) {
		synchronized (trackingMap) {
			Set<Map.Entry<String, SClient>> set = trackingMap.entrySet();
			Iterator<Entry<String, SClient>> it = set.iterator();
			while (it.hasNext()) {
				SClient returnedVal = it.next().getValue();
				if (returnedVal == sc) {
					it.remove();
				}
			}// while
		}// synchronized
	}

	// -------------
	private void initReflectionMethods() {
		Method[] methods = Car.class.getMethods();
		for (Method method : methods) {
			if (method.isAnnotationPresent(AnnotLeisurable.class)) {
				reflectionMethods.add(method.getName());
			}// if
		}// for
	}

	private synchronized String getRandReflectionMethod() {
		Collections.shuffle(reflectionMethods);
		return reflectionMethods.get(0);
	}

	// -------------

	// --------------------------------------------------------------------

	// --------------------------------------------------------------------
	@Override
	public void run() {

		setOnLine(true);

		try {
			while (isOnLine()) {
				final Socket socket = welcomeSocket.accept();
				SClient newClient = new SClient(socket);
				executor.execute(newClient);
				sclientsList.add(newClient);
			}// while

			welcomeSocket.close();

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				welcomeSocket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	// --------------------------------------------------------------------

	// --------------------------------------------------------------------
	private class SClient extends QCodeAdapter implements Runnable {

		/** Data fields */
		private QConnection<QMessage> connection;
		private ArrayBlockingQueue<QMessage> qmessageList;
		private Thread qmessageListWorker;

		/** C'tor */
		public SClient(Socket socket) throws IOException {
			setConnection(new QConnection<>(socket));
			qmessageList = new ArrayBlockingQueue<QMessage>(10, true);
			activateWorker();
		}// c'tor

		private void activateWorker() {
			qmessageListWorker = new Thread(new Runnable() {
				@Override
				public void run() {
					try {
						while (connection.isConnected()) {
							QMessage message = qmessageList.take();
							connection.sendData(message);
						}// while
					} catch (InterruptedException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			});
			executor.execute(qmessageListWorker);
		}

		public void setConnection(QConnection<QMessage> connection) {
			this.connection = connection;
		}

		public void closeSClient() {

			if (connection.isConnected()) {

				try {
					connection.closeConnection();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}

			removeSClientFromTrackingMap(this);
			/*
			 * No problem with closing any related resources!
			 */
			qmessageListWorker.interrupt();
			qmessageList.clear();
		}

		public String toString() {
			return "SClient";
		}

		// ---------------------
		@SuppressWarnings("incomplete-switch")
		@Override
		public void run() {
			try {
				while (connection.isConnected()) {

					QMessage message = new QMessage();
					message = connection.getData();

					Code code = (Code) message.getMessageMap().get("code");

					switch (code) {

					case DATA: {
						readDataMsg(message);
						break;
					}
					case PUMPCOUNT: {
						readPumpCountMsg(message);
						break;
					}
					case WEBSERVICE: {
						readWebServiceMsg(message);
						break;
					}
					}// switch

				}// while

			} catch (ClassNotFoundException | IOException e) {
				e.printStackTrace();
			} finally {
				closeSClient();
			}
		}

		// ---------------------

		@Override
		public void readDataMsg(QMessage message) {

			executor.execute(new Runnable() {

				@SuppressWarnings("incomplete-switch")
				@Override
				public void run() {

					Code code = (Code) message.getMessageMap().get("subcode");

					String[] param = (String[]) message.getMessageMap().get(
							"data");

					boolean isCarNew = registerNewCarConnection(param[0],
							SClient.this);

					if (isCarNew) {

						switch (code) {

						case CLIENT: {

							try {

								fireSubmitNewCar(param, true);

							} catch (NumberFormatException
									| InvalidPumpException e) {
								createMessageMsg("# Some parameters are incorrect !#");
								removeCarFromTracking(param[0]);
							} catch (StationClosedException e) {
								createMessageMsg("# Gas Station is closed #");
								removeCarFromTracking(param[0]);
							} catch (SecurityException | IOException e) {
								removeCarFromTracking(param[0]);
								e.printStackTrace();
							}

							break;
						}// case
						case SERVLET: {

							try {

								fireSubmitNewCar(param, false);

								createMessageMsg("Success adding car from web servlet");

							} catch (NumberFormatException
									| InvalidPumpException e) {
								String msgErr = "# Some parameters are incorrect !#";
								if (e instanceof InvalidPumpException) {
									msgErr += "  :: PumpNum[0-"
											+ (fireRequestNumberOfPumps() - 1)
											+ "]";
								}
								createMessageMsg(msgErr);
							} catch (StationClosedException e) {
								createMessageMsg("# Gas Station is closed #");
							} catch (SecurityException | IOException e) {
								e.printStackTrace();
							} finally {
								removeCarFromTracking(param[0]);
							}

							break;
						}// case

						}// switch

					}// if
					else {

						createMessageMsg("Car id : " + param[0]
								+ " already exists");

					}// else

				}// run
			});

		}

		@Override
		public void createMessageMsg(String msg) {
			QMessage message = new QMessage();
			message.getMessageMap().put("code", Code.MESSAGE);
			message.getMessageMap().put("message", msg);
			try {
				qmessageList.put(message);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void createMessageMsg(String msg, int carId) {

			QMessage message = new QMessage();
			message.getMessageMap().put("code", Code.MESSAGE);
			message.getMessageMap().put("message", msg);

			if (carId != -1) {
				message.getMessageMap().put("reflection",
						getRandReflectionMethod());
				message.getMessageMap().put("carId", carId);
			}

			try {
				qmessageList.put(message);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void createPumpCountMsg() {
			QMessage message = new QMessage();
			int pumpCount = fireRequestNumberOfPumps();
			message.getMessageMap().put("code", Code.PUMPCOUNT);
			message.getMessageMap().put("pumpcount", pumpCount);
			try {
				qmessageList.put(message);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void readPumpCountMsg(QMessage message) {
			createPumpCountMsg();
		}

		@Override
		public void readWebServiceMsg(QMessage message) {
			createWebServiceMsg((String) message.getMessageMap().get("carId"));
		}

		@Override
		public void createWebServiceMsg(String carId) {
			QMessage message = new QMessage();
			message.getMessageMap().put("code", Code.WEBSERVICE);
			String ans = "Error";
			try {
				ans = fireRequestCarHistory(carId);
			} catch (Exception e1) {
				e1.printStackTrace();
			}
			message.getMessageMap().put("webservice", ans);
			try {
				qmessageList.put(message);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		// ---------------------

	}// SClient

	// --------------------------------------------------------------------

	// --------------------------------------------------------------------
	// QServer Events

	public void registerServerBlListener(QServerEventsListener newListener) {
		qServerEventListener = newListener;
	}

	private void fireSubmitNewCar(String[] param, boolean isFromClient)
			throws SecurityException, StationClosedException, IOException,
			InvalidPumpException {
		qServerEventListener.submitNewCar(param, isFromClient);
	}

	private int fireRequestNumberOfPumps() {
		return qServerEventListener.RequestNumberOfPumps();
	}

	private String fireRequestCarHistory(String carId) throws Exception {
		return qServerEventListener.requestCarHistory(carId);
	}

	// --------------------------------------------------------------------

}// Server

