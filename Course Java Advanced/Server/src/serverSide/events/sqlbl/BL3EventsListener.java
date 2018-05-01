package serverSide.events.sqlbl;

import java.util.HashMap;

public interface BL3EventsListener {

	void recordPumpActivity(String carId, int pumpNum, double amount)
			throws Exception;

	void recordCleanActivity(String carId, double profit) throws Exception;

	HashMap<String, Object> submitQueryFormDbTab(String sql, String jpaSql) throws Exception;

	public HashMap<String, Object> getTotProfits() throws Exception;
	
	public String getCarHistory(String carId) throws Exception;
	
	void closeDbConnection() throws Exception;

}
