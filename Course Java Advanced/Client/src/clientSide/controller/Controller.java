package clientSide.controller;

import java.util.ArrayList;

import clientSide.bl.bl.Model;
import clientSide.listenersInterFace.BLEventsListener;
import clientSide.listenersInterFace.UIEventsListener;
import clientSide.ui.MainFrameRunner;

public class Controller implements UIEventsListener, BLEventsListener {

	/** Data fields */
	private MainFrameRunner mainFrame;
	private Model model;

	/** C'tor */
	public Controller(MainFrameRunner mainFrame, Model model) {

		this.mainFrame = mainFrame;
		this.model = model;

		mainFrame.registerListener(this);
		model.registerListener(this);

	}// c'tor

	// ------------------------------------------
	// UI events
	@Override
	public void submitAddCarForm(ArrayList<String> formData) {
		model.submitUserFormToServer(formData);
	}//

	@Override
	public void connectToServer(String ip, String port) {
		model.connectToServer(ip, port);
	}//

	@Override
	public void disconnectFromServer() {
		model.disConnectFromServer();
	}

	// ------------------------------------------

	// ------------------------------------------
	// BL events
	@Override
	public void postServerEcho(String serverEchoMessage) {
		mainFrame.requestSetChatText(serverEchoMessage);
	}

	@Override
	public void resetPumpCount(int pumpCount) {
		mainFrame.requestreSetCmb(pumpCount);
	}

	@Override
	public void setConnectedState() {
		mainFrame.requestSetConnectedState();
	}

	@Override
	public void setDisConnectedState() {
		mainFrame.requestSetDisConnectedState();
	}

	@Override
	public void freezeConnectionBtns() {
		mainFrame.requestFreezeConnectionBtns();
	}

	// ------------------------------------------

}// Controller

