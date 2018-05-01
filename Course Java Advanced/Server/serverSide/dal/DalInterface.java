package serverSide.dal;

import java.util.HashMap;

public interface DalInterface {

	void insertPumpActivity(String carId, int pumpNum, double pumpProfit)
			throws Exception;

	void insertCleaningActivity(String carId, double profit) throws Exception;

	HashMap<String, Object> submitSqlString(String sql, String jpaSql) throws Exception;

	HashMap<String, Object> getTotProfits() throws Exception;
	
	String getCarHistory(String carId) throws Exception;
	
	void closeConnection() throws Exception;

}
