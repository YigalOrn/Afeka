package clientSide.ui;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import clientSide.bl.bl.Model;
import clientSide.controller.Controller;
import clientSide.listenersInterFace.UIEventsListener;

public class MainFrameRunner extends JFrame {

	private UserView userView;
	private UIEventsListener uiListener;

	public MainFrameRunner() {

		setTitle("Client");
		setVisible(true);
		setLocation(50, 100);
		setSize(720, 542);// or use pack()
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		setAlwaysOnTop(true);

		userView = new UserView(this);
		setContentPane(userView);

		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {

				Thread thrDisCorrectly = new Thread(new Runnable() {
					@Override
					public void run() {
						uiListener.disconnectFromServer();
					}
				});
				thrDisCorrectly.run();
			}
		});

	}// c'tor

	public static void main(String[] args) {

		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				setLookAndFeel();

				MainFrameRunner mainFrame = new MainFrameRunner();
				Model model = new Model();

				@SuppressWarnings("unused")
				Controller controller = new Controller(mainFrame, model);
			}// run
		});
	}// main

	private static void setLookAndFeel() {
		try {
			UIManager
					.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
		} catch (ClassNotFoundException | InstantiationException
				| IllegalAccessException | UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
	}

	public void registerListener(UIEventsListener newListener) {
		uiListener = newListener;
	}

	// -----------------------------------------------------------
	// BL events

	public void requestSetChatText(String serverEchoMessage) {
		userView.requestSetChatText(serverEchoMessage);
	}

	public void requestreSetCmb(int pumpCount) {
		userView.requestreSetCmb(pumpCount);
	}

	public void requestSetConnectedState() {
		userView.requestSetConnectedState();
	}

	public void requestSetDisConnectedState() {
		userView.requestSetDisConnectedState();
	}

	public void requestFreezeConnectionBtns() {
		userView.requestFreezeConnectionBtns();
	}

	// -----------------------------------------------------------

	// ------------------------------------------
	// UI events
	public void submitAddCarForm(ArrayList<String> formData) {
		uiListener.submitAddCarForm(formData);
	}

	public void connectToServer(String ip, String port) {
		uiListener.connectToServer(ip, port);
	}

	public void disconnectFromServer() {
		uiListener.disconnectFromServer();
	}
	// ------------------------------------------

}// MainFrame
