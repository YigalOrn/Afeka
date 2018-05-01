package app.financialmanager.interfaces.daoservices;

import java.util.List;


import entities.FinancialManager;
import entities.Investor;
import entities.Lead;

public interface FinancialManagerDAOService {

	void persistFinancialManager(FinancialManager financialManager);

	void persistInvestor(Investor investor);

	void persistLead(Lead lead);
	
	List<Lead> getLeadsList();

	List<Investor> getInvestorsList();
}
