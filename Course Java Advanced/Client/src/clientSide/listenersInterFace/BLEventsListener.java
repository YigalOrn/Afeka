package clientSide.listenersInterFace;

public interface BLEventsListener {

	void postServerEcho(String serverEchoMessage);

	void resetPumpCount(int pumpCount);

	void setConnectedState();

	void setDisConnectedState();

	void freezeConnectionBtns();
}
