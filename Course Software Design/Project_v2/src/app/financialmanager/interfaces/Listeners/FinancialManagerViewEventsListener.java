package app.financialmanager.interfaces.Listeners;

import entities.Lead.LeadStatus;

public interface FinancialManagerViewEventsListener {

	void executeGetLeadRequest();

	void executeChangeLeadStatus(LeadStatus leadStatus);

	void executeComposeReport(double feeVal);

	void executeAdviceSubmited(String subject, String body);

	void executeViewWindowIsClosing();
}
