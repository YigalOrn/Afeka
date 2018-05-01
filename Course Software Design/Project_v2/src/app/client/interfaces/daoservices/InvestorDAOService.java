package app.client.interfaces.daoservices;

import entities.Advice;
import entities.Investor;

public interface InvestorDAOService {

	void persistIvestor(Investor investor);

	Advice getAdvice();
}
