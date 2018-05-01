package app.auth.interfaces;

import entities.FinancialManager;

public interface FinancialManagerAuthDAOService extends AuthDAOService {
	FinancialManager getEntityByFinancialManagerUserName(String username);
}
