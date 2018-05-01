package app.auth.interfaces;

import entities.Investor;

public interface ClientAuthDAOService extends AuthDAOService {
	Investor getEntityByInvestorUserName(String username);
}
