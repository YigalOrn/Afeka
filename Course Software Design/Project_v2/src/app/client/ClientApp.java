package app.client;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import app.auth.view.ClientAuthView;
import app.client.controllers.ClientAuthViewController;

public class ClientApp {

	public static void main(String[] args) {
		setAppMVC();
	}

	public static void setAppMVC() {
		setUILookAndFeel();
		ClientAuthView clientAuthView = new ClientAuthView("Client Auth");
		ClientAuthViewController controller = new ClientAuthViewController(clientAuthView);
	}

	private static void setUILookAndFeel() {

		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}

	}
}
