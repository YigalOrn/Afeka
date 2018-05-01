package app.client.interfaces.Listeners;

import javax.swing.table.DefaultTableModel;

public interface ClientViewEventsListener {

	void executeCommand(String stockName, int amount, double limitPrice, String type);

	void executeReportRequest();

	void executeAdviceRequest();

	void executeTransactionsrequestForCommand(long cid);
	
	void executeViewWindowIsClosing();
	
	void executeTickersUpdateRequest(DefaultTableModel tickersModel);
}
