package clientSide.bl.bl;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import qClasses.QCodeAdapter;
import qClasses.QConnection;
import qClasses.QMessage;
import clientSide.listenersInterFace.BLEventsListener;

public class Model extends QCodeAdapter implements Runnable {

	/** Data fields */
	private QConnection<QMessage> clientConnection;
	private ExecutorService executor;
	private ArrayBlockingQueue<QMessage> qmessageList;
	private Thread qmessageListWorker;
	private BLEventsListener bLlistener;

	/** C'tor */
	public Model() {
		clientConnection = new QConnection<>();
		qmessageList = new ArrayBlockingQueue<QMessage>(10, true);
	}// c'tor

	private void activateWorker() {
		qmessageListWorker = new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					while (clientConnection.isConnected()) {
						QMessage message = qmessageList.take();
						clientConnection.sendData(message);
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

	public void registerListener(BLEventsListener newListener) {
		this.bLlistener = newListener;
	}//

	/**
	 * Format: [carId, wantsCleaning, numOfLiters, pumpNum]
	 * 
	 * */
	public void submitUserFormToServer(ArrayList<String> formData) {
		executor.execute(new Runnable() {
			@Override
			public void run() {
				createDataMsg(formData);
			}// run
		});
	}//

	public void disConnectFromServer() {
		if (clientConnection.isConnected()) {
			try {
				fireFreezeConnectionBtns();
				qmessageListWorker.interrupt();
				executor.shutdown();
				while (!executor.isShutdown())
					;
				fireSetDisConnectedState();
			} catch (Exception e) {
				e.printStackTrace();
				fireSetConnectedState();
			}
		}// if
	}//

	public void connectToServer(String ip, String port) {

		try {
			fireFreezeConnectionBtns();

			int portNum = Integer.parseInt(port);
			clientConnection.createConnection(ip, portNum);

			executor = Executors.newCachedThreadPool();
			activateWorker();
			executor.execute(this);
			requestPumpInfo();
			fireSetConnectedState();

		} catch (NumberFormatException | IOException e) {
			e.printStackTrace();
			fireSetDisConnectedState();
		}

	}//

	private void requestPumpInfo() throws IOException {
		createPumpCountMsg();
	}//

	private void closeConnection() {
		try {
			clientConnection.closeConnection();

			fireSetDisConnectedState();
			fireServerEchoBack("\n\n\n<<----Disconnected---->>\n\n");

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// ------------------------------------------
	@SuppressWarnings("incomplete-switch")
	@Override
	/**
	 * 
	 * Accepts incoming data from the server and process it!
	 * Runs on an ExecutorService
	 * 
	 * */
	public void run() {

		try {

			while (clientConnection.isConnected()) {

				// final ?
				QMessage message = new QMessage();
				message = clientConnection.getData();

				Code code = (Code) message.getMessageMap().get("code");

				switch (code) {

				case MESSAGE: {
					readMessageMsg(message);
					break;
				}
				case PUMPCOUNT: {
					readPumpCountMsg(message);
					break;
				}

				}// switch

			}// while

		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			closeConnection();

			/*
			 * Optional to close all clients GUI when gas station is down
			 * 
			 * System.exit(1);
			 */

		}

	}// run

	@Override
	public void createDataMsg(ArrayList<String> formData) {

		String[] param = formData.toArray(new String[0]);

		QMessage message = new QMessage();
		message.getMessageMap().put("code", Code.DATA);
		message.getMessageMap().put("subcode", Code.CLIENT);
		message.getMessageMap().put("data", param);

		try {
			qmessageList.put(message);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

	@Override
	public void readMessageMsg(QMessage message) {

		executor.execute(new Runnable() {

			@Override
			public void run() {

				if (message.getMessageMap().containsKey("reflection")) {

					String methodName = (String) message.getMessageMap().get(
							"reflection");
					try {

						ReflectionUtil.activateByMethodName(
								"clientSide.bl.car.Car", methodName);

					} catch (ClassNotFoundException e) {
						e.printStackTrace();
					}

					Object val = ReflectionUtil
							.getReturnValByMethodName(methodName);

					if (val != null) {
						String msg = "Server>>"
								+ (String) message.getMessageMap().get(
										"message") + "\nClient>>Car "
								+ message.getMessageMap().get("carId") + " - "
								+ (String) val;

						fireServerEchoBack(msg);
					}
				} else {
					String msg = "Server>>"
							+ (String) message.getMessageMap().get("message");

					fireServerEchoBack(msg);
				}// else

			}// run

		});
	}

	@Override
	public void createPumpCountMsg() {
		QMessage message = new QMessage();
		message.getMessageMap().put("code", Code.PUMPCOUNT);

		try {
			qmessageList.put(message);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

	@Override
	public void readPumpCountMsg(QMessage message) {
		executor.execute(new Runnable() {
			@Override
			public void run() {
				int pumpCount = (int) message.getMessageMap().get("pumpcount");
				firePumpCountReset(pumpCount);
			}// run
		});
	}

	// ------------------------------------------

	// ------------------------------------------

	private void firePumpCountReset(int pumpCount) {
		bLlistener.resetPumpCount(pumpCount);
	}

	private void fireServerEchoBack(String serverEchoMessage) {
		bLlistener.postServerEcho(serverEchoMessage);
	}

	/*
	 * Disables connected btn. Enables disconnected btn.
	 */
	private void fireSetConnectedState() {
		bLlistener.setConnectedState();
	}

	/*
	 * Enables connected btn. Disables disconnected btn.
	 */
	private void fireSetDisConnectedState() {
		bLlistener.setDisConnectedState();
	}

	/*
	 * Disables both btn(s).
	 */
	private void fireFreezeConnectionBtns() {
		bLlistener.freezeConnectionBtns();
	}
	// ------------------------------------------

}//
