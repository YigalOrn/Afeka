package app.financialmanager.controllers;

import app.auth.interfaces.AuthViewEventsListener;
import app.auth.interfaces.FinancialManagerAuthDAOService;
import app.auth.view.AuthView;
import app.financialmanager.dao.FinancialManagerAuthDAO;
import app.financialmanager.views.FinancialManagerView;
import entities.FinancialManager;

public class FinancialManagerAuthViewController implements AuthViewEventsListener {

	private final AuthView authView;
	private final FinancialManagerAuthDAOService authDAO = new FinancialManagerAuthDAO();

	public FinancialManagerAuthViewController(AuthView view) {
		authView = view;
		authView.registerListener(this);
	}

	@Override
	public void loginSubmission(String username, String password) {

		String retrievedPasswordHash = authDAO.getPassworHashByUserName(username);
		String passwordHash = org.apache.commons.codec.digest.DigestUtils.sha256Hex(password);

		// error: no such user
		if (retrievedPasswordHash == null) {

			authView.setLoginError("user name is incorrect");
		}
		// compare hashes
		else {

			// Investor user fully authenticated
			if (passwordHash.equals(retrievedPasswordHash)) {

				authView.dispose();
				FinancialManagerView financialManagerView = new FinancialManagerView();
				FinancialManager financialManager = authDAO.getEntityByFinancialManagerUserName(username);

				FinancialManagerViewController controller = new FinancialManagerViewController(financialManager,
						financialManagerView);
			}
			// error: password incorrect
			else {

				authView.setLoginError("password is incorrect");
			}
		}
	}
}
