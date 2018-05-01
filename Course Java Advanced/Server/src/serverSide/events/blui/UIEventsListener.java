package serverSide.events.blui;

import java.util.HashMap;

import serverSide.bl.GasStationBL.Statistics;

public interface UIEventsListener {

	
	void requestGasStationClosing();
	
	
	/*
	 * In use with statisticsPane
	 */
	Statistics getStatistics();

	/*
	 * 
	 * In use with AddNewCarPane
	 * 
	 * carParameters : [carId, wantsCleaning, numOfLiters, pumpNum]
	 */
	void addCarFromFX(String[] carParameters, boolean fromClient)
			throws Exception;

	/*
	 * 
	 * add car form. DB form.
	 */
	int requestPumpNum();

	/*
	 * Tank refuel GUI related
	 */
	void requestTankRefuel();

	long requestTankRefuelTime();

	void requestTankLockRelease();

	/*
	 * DB related
	 */
	HashMap<String, Object> requestFuelFormSubmission(String sql, String jpaSql)
			throws Exception;

	HashMap<String, Object> requestCleaningFormSubmission(String sql,
			String jpaSql) throws Exception;

	HashMap<String, Object> requestTotProfitsFormSubmission() throws Exception;

}//
