package app.client.controllers;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import app.auth.interfaces.ClientAuthDAOService;
import app.auth.interfaces.ClientAuthViewEventsListener;
import app.auth.view.ClientAuthView;
import app.client.dao.ClientAuthDAO;
import app.client.views.ClientView;
import app.client.views.LeadView;
import entities.Investor;

public class ClientAuthViewController implements ClientAuthViewEventsListener {

	private final ClientAuthView clientAuthView;
	private final ClientAuthDAOService authDAO = new ClientAuthDAO();

	public ClientAuthViewController(ClientAuthView view) {
		clientAuthView = view;
		clientAuthView.registerListener(this);
	}

	@Override
	public void loginSubmission(String username, String password) {

		String retrievedPasswordHash = authDAO.getPassworHashByUserName(username);
		String passwordHash = org.apache.commons.codec.digest.DigestUtils.sha256Hex(password);

		// error: no such user
		if (retrievedPasswordHash == null) {

			clientAuthView.setLoginError("user name is incorrect");
		}
		// compare hashes
		else {

			// Investor user fully authenticated
			if (passwordHash.equals(retrievedPasswordHash)) {

				clientAuthView.dispose();

				ClientView clienView = new ClientView(username);// view
				Investor investor = authDAO.getEntityByInvestorUserName(username);// model

				ClientViewController controller = new ClientViewController(investor, clienView);
			}
			// error: password incorrect
			else {
				clientAuthView.setLoginError("password is incorrect");
			}
		}
	}

	@Override
	public void leadRegistartion() {

		clientAuthView.dispose();

		LeadView leadView = new LeadView();
	}
}
