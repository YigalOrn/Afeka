package serverSide.controllers.blui;

import java.util.HashMap;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationBL.Statistics;
import serverSide.events.blui.BL1EventsListener;
import serverSide.events.blui.UIEventsListener;
import serverSide.ui.mainScreen.tabsPane.TabsPane;

public class BLUIController implements UIEventsListener, BL1EventsListener {

	/** Data fields */
	private TabsPane tabsPane;
	private GasStation gasStation;

	/** C'tor */
	public BLUIController(TabsPane tabsPane, GasStation gasStation) {
		this.gasStation = gasStation;
		this.tabsPane = tabsPane;

		// ---
		gasStation.registerBL1Listener(this);
		// ---

		// ---
		tabsPane.registerUIListener(this);
		// ---

	}// c'tor

	// ----------------------------------------------------
	// BLEvents

	@Override
	public void handleCarProgressTextualy(String descriptionStr) {
		tabsPane.postString(descriptionStr);
	}

	@Override
	public void handleCarProgressByImage(Car car) {
		tabsPane.handleCarVisualDisplay(car);
	}

	@Override
	public void handleTankFuelLevelLow() {
		tabsPane.handleTankFuelLevelLow();
	}

	// ----------------------------------------------------

	// ----------------------------------------------------
	// UIEvents

	@Override
	public void requestGasStationClosing() {
		gasStation.closeStation();
	}

	@Override
	public Statistics getStatistics() {
		return gasStation.getGasStationStatistics();
	}

	@Override
	public void addCarFromFX(String[] carParameters, boolean fromClient)
			throws Exception {
		gasStation.addNewCar(carParameters, fromClient);
	}

	@Override
	public int requestPumpNum() {
		return gasStation.getNumOfPumps();
	}

	@Override
	public void requestTankRefuel() {
		gasStation.fillTheMainPumpModel();
	}

	@Override
	public long requestTankRefuelTime() {
		return gasStation.getAnimationTime();
	}

	@Override
	public void requestTankLockRelease() {
		gasStation.releaseLockForTankRefill();
	}

	// SQL

	@Override
	public HashMap<String, Object> requestFuelFormSubmission(String sql,
			String jpaSql) throws Exception {
		// return using controller gas-station/db
		return gasStation.submitQueryFormDbTab(sql, jpaSql);
	}

	@Override
	public HashMap<String, Object> requestCleaningFormSubmission(String sql,
			String jpaSql) throws Exception {
		// return using controller gas-station/db
		return gasStation.submitQueryFormDbTab(sql, jpaSql);
	}

	@Override
	public HashMap<String, Object> requestTotProfitsFormSubmission()
			throws Exception {
		// return using controller gas-station/db
		return gasStation.getTotProfits();
	}
	// ----------------------------------------------------

}//
