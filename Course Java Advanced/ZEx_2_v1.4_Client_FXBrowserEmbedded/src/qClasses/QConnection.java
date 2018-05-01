package qClasses;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.locks.ReentrantLock;

public class QConnection<E> {

	/** Data fields */
	private Socket socket;
	private ObjectInputStream objectInputStream;
	private ObjectOutputStream objectOutputStream;
	private boolean isConnected;
	private ReentrantLock lock = new ReentrantLock(true);

	/** C'tor -1 */
	public QConnection(String ip, int port) throws UnknownHostException,
			IOException {
		createConnection(ip, port);
	}//

	/** C'tor -2 */
	public QConnection(Socket socket) throws IOException {
		setSocket(socket);
		setObjectOutputStream(socket.getOutputStream());
		setObjectInputStream(socket.getInputStream());
	}//

	/** C'tor -3 */
	public QConnection() {

	}//

	/***/

	public synchronized boolean isConnected() {
		return isConnected;
	}

	private synchronized void setConnected(boolean isConnected) {
		this.isConnected = isConnected;
	}

	public Socket getSocket() {
		return socket;
	}

	public void setSocket(Socket socket) {
		this.socket = socket;
		setConnected(true);
	}

	public ObjectInputStream getObjectInputStream() {
		return objectInputStream;
	}

	public void setObjectInputStream(InputStream inputStream)
			throws IOException {
		objectInputStream = new ObjectInputStream(new BufferedInputStream(
				inputStream));
	}

	public ObjectOutputStream getObjectOutputStream() {
		return objectOutputStream;
	}

	public void setObjectOutputStream(OutputStream outputStream)
			throws IOException {
		objectOutputStream = new ObjectOutputStream(new BufferedOutputStream(
				outputStream));
		objectOutputStream.flush();
	}

	// ----------------------------------------------
	public String toString() {
		return String.format("IP : %s\t Port : %s", socket.getInetAddress(),
				socket.getPort());
	}//

	/**
	 * 
	 * Many threads could be simultaneously sending data.
	 * 
	 * */
	public void sendData(E data) throws IOException {
		lock.lock();
		try {
			objectOutputStream.writeObject(data);
			objectOutputStream.flush();
		} finally {
			lock.unlock();
		}
	}//

	/**
	 * 
	 * Only one thread is in charge of all the incoming transmission
	 * 
	 * */
	public E getData() throws IOException, ClassNotFoundException {
		@SuppressWarnings("unchecked")
		E recievdData = (E) objectInputStream.readObject();// Blocking
		return recievdData;
	}//

	public void createConnection(String ip, int port)
			throws UnknownHostException, IOException {
		setSocket(new Socket(ip, port));
		setObjectOutputStream(getSocket().getOutputStream());
		setObjectInputStream(getSocket().getInputStream());
		setConnected(true);
	}//

	public void closeConnection() throws IOException {
		setConnected(false);
		try {
			getObjectOutputStream().close();
			getObjectInputStream().close();
			socket.close();
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
	// ----------------------------------------------

}// Connection