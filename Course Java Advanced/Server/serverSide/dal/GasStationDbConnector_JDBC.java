/*
 * http://localhost:NEWAPACHEPORT/phpmyadmin/
 * 
 * http://www.w3schools.com/sql/
 * http://complete-concrete-concise.com/web-tools/how-to-change-the-apache-port-in-xampp
 * */

package serverSide.dal;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.time.LocalDateTime;
import java.util.HashMap;

import com.mysql.jdbc.PreparedStatement;

public class GasStationDbConnector_JDBC extends GasStationDbConnector {

	/** Data fields */

	private static GasStationDbConnector_JDBC dbConnector;

	private static String JDBS_DRIVER = "com.mysql.jdbc.Driver";
	private String dburl = "jdbc:mysql://localhost/";
	private String dbname = "java_refuels";

	private static Connection connection;

	/** C'tor */
	private GasStationDbConnector_JDBC() {

		try {
			Class.forName(JDBS_DRIVER).newInstance();
			dburl += dbname;
			connection = DriverManager.getConnection(dburl, "root", "");
		} catch (IllegalAccessException | InstantiationException
				| ClassNotFoundException | SQLException e) {

			e.printStackTrace();

			try {
				connection.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}

		}

	}//

	public static GasStationDbConnector_JDBC getInstance() {
		if (dbConnector == null) {
			dbConnector = new GasStationDbConnector_JDBC();
		}
		return dbConnector;
	}//

	@Override
	public synchronized void closeConnection() throws SQLException {
		if (!connection.isClosed()) {
			connection.close();
		}
	}//

	// ------------------DB Updates--------------------------

	@Override
	public synchronized void insertPumpActivity(String carId, int pumpNum,
			double pumpProfit) throws SQLException {

		if (!connection.isClosed()) {

			ldt = LocalDateTime.now();
			PreparedStatement statement = null;

			try {

				statement = (PreparedStatement) connection
						.prepareStatement("INSERT into Pump (Id, Profit, Time, Date, CarId) VALUES(?, ?, ?, ?, ?);");
				statement.setInt(1, pumpNum);
				statement.setDouble(2, pumpProfit);
				statement.setString(3, ldt.toLocalTime().format(dtfTime));
				statement.setString(4, ldt.toLocalDate().format(dtfDate));
				statement.setString(5, carId);

				statement.execute();

			} finally {
				statement.close();
			}

		}
	}

	@Override
	public synchronized void insertCleaningActivity(String carId, double profit)
			throws SQLException {

		if (!connection.isClosed()) {

			ldt = LocalDateTime.now();

			PreparedStatement statement = null;

			try {

				statement = (PreparedStatement) connection
						.prepareStatement("INSERT into CleaningService (Profit, Time, Date, CarId) VALUES(?, ?, ?, ?);");
				statement.setDouble(1, profit);
				statement.setString(2, ldt.toLocalTime().format(dtfTime));
				statement.setString(3, ldt.toLocalDate().format(dtfDate));
				statement.setString(4, carId);

				statement.execute();

			} finally {
				statement.close();
			}

		}
	}

	// ---------------------------------------------------

	// ------------------DB Queries--------------------------
	@Override
	public synchronized HashMap<String, Object> submitSqlString(String sql,
			String jpaSql) throws SQLException {

		HashMap<String, Object> hashMap = new HashMap<>();

		if (!connection.isClosed()) {

			Statement statement = connection.createStatement();
			ResultSet rs = statement.executeQuery(sql);

			hashMap.put("rs", rs);

		} else {

			hashMap.put("rs", null);

		}

		return hashMap;

	}

	@Override
	public synchronized HashMap<String, Object> getTotProfits()
			throws Exception {

		String sqlTotProfits = "SELECT SUM(Profit) AS TotProfit " + "FROM( "
				+ "SELECT SUM(Profit) AS Profit FROM Pump " + "UNION "
				+ "SELECT SUM(Profit) AS Profit FROM CleaningService) AS t";

		return submitSqlString(sqlTotProfits, null);
	}

	@Override
	public synchronized String getCarHistory(String carId) throws Exception {
		// servlet-->webservice-->server-->gas station-->dal<--

		String ans = "";

		ResultSet rs1 = (ResultSet) submitSqlString(
				"SELECT SUM(Profit) AS Profit FROM Pump WHERE CarId = '"
						+ carId + "'", null).get("rs");
		rs1.next();

		ResultSet rs2 = (ResultSet) submitSqlString(
				"SELECT SUM(Profit) AS Profit FROM CleaningService WHERE CarId = '"
						+ carId + "'", null).get("rs");
		rs2.next();

		if (rs1.getString("Profit") == null && rs2.getString("Profit") == null) {
			return "Car is not in db";
		}

		if (rs1.getString("Profit") == null) {
			ans += "Pump bill: 0.0";
		} else {
			ans += "Pump bill: " + rs1.getString("Profit");
		}

		if (rs2.getString("Profit") == null) {
			ans += ", Cleaning Service bill: 0.0";
		} else {
			ans += ", Cleaning Service bill: " + rs2.getString("Profit");
		}

		return ans;
	}
	// ---------------------------------------------------

}//

