package serverSide.dal;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;

public abstract class GasStationDbConnector implements DalInterface {

	protected LocalDateTime ldt;

	protected static DateTimeFormatter dtfDate = DateTimeFormatter
			.ofPattern("yyyy-MM-dd");
	protected static DateTimeFormatter dtfTime = DateTimeFormatter
			.ofPattern("HH:mm:ss");

	public GasStationDbConnector() {

	}

	@Override
	public void insertPumpActivity(String carId, int pumpNum, double pumpProfit)
			throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public void insertCleaningActivity(String carId, double profit)
			throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public HashMap<String, Object> submitSqlString(String sql, String jpaSql)
			throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public HashMap<String, Object> getTotProfits() throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getCarHistory(String carId) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void closeConnection() throws Exception {
		// TODO Auto-generated method stub

	}

}
