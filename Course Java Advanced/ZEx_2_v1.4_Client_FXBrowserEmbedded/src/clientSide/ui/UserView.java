package clientSide.ui;

import java.util.ArrayList;

import javax.swing.JSplitPane;

import clientSide.listenersInterFace.UIEventsListener;
import clientSide.ui.clientView.ClientPanel;
import clientSide.ui.webView.WebPanel;

public class UserView extends JSplitPane {

	/** Data fields */
	private ClientPanel clientPanel;
	private WebPanel webPanel;

	private MainFrameRunner mainFrameRunner;

	/** C'tor */
	public UserView(MainFrameRunner mainFrameRunner) {
		super(JSplitPane.HORIZONTAL_SPLIT);
		// Set views size, frame uses pack()
		setSize(720, 542);
		// Arrows on slider
		setOneTouchExpandable(true);
		// Initial position
		setDividerLocation(this.getWidth());
		// setResizeWeight(0);
		initUserViewComponents();

		this.mainFrameRunner = mainFrameRunner;

	}// c'tor

	private void initUserViewComponents() {

		webPanel = new WebPanel();
		clientPanel = new ClientPanel(this);

		setLeftComponent(clientPanel);
		setRightComponent(webPanel);

	}

	// -----------------------------------------------------------
	// BL events
	public void requestSetChatText(String serverEchoMessage) {
		clientPanel.setChatText(serverEchoMessage);
	}

	public void requestreSetCmb(int pumpCount) {
		clientPanel.requestreSetCmb(pumpCount);
	}

	public void requestSetConnectedState() {
		clientPanel.requestSetConnectedState();
	}

	public void requestSetDisConnectedState() {
		clientPanel.requestSetDisConnectedState();
	}

	public void requestFreezeConnectionBtns() {
		clientPanel.requestFreezeConnectionBtns();
	}

	// -----------------------------------------------------------

	// ------------------------------------------
	// UI events
	public void submitAddCarForm(ArrayList<String> formData) {
		mainFrameRunner.submitAddCarForm(formData);
	}

	public void connectToServer(String ip, String port) {
		mainFrameRunner.connectToServer(ip, port);
	}

	public void disconnectFromServer() {
		mainFrameRunner.disconnectFromServer();
	}
	// ------------------------------------------
}// SlideMenu
