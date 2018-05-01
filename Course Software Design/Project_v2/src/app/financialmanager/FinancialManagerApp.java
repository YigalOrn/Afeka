package app.financialmanager;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import app.auth.view.AuthView;
import app.financialmanager.controllers.FinancialManagerAuthViewController;

public class FinancialManagerApp {

	public static void main(String[] args) {
		setAppMVC();
	}

	public static void setAppMVC() {
		setUILookAndFeel();
		AuthView authView = new AuthView("Financial Manager Auth");
		FinancialManagerAuthViewController controller = new FinancialManagerAuthViewController(authView);
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
