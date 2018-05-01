package serverSide.ui.mainScreen.tabsPane;

import java.util.HashMap;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.Statistics;
import serverSide.events.blui.UIEventsListener;
import serverSide.ui.mainScreen.tabs.carsStatusTabPackage.CarsStatusTab;
import serverSide.ui.mainScreen.tabs.communicationTabPackage.CommunicationTab;
import serverSide.ui.mainScreen.tabs.dbTabPackage.DbTab;
import serverSide.ui.mainScreen.tabs.menuTabPackage.MenuTab;
import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.geometry.Side;
import javafx.scene.control.SelectionModel;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;

public class TabsPane extends TabPane {

	/** Data fields */
	private MenuTab menuTab;
	private CommunicationTab communicationTab;
	private CarsStatusTab carsStatusTab;
	private DbTab dbTab;

	private UIEventsListener uiListener;

	/** C'tor */
	public TabsPane() {

		communicationTab = new CommunicationTab("Text Tube");
		carsStatusTab = new CarsStatusTab("Cars Tube");
		dbTab = new DbTab("Db Tube", this);
		menuTab = new MenuTab("Menu", this);

		getTabs().addAll(menuTab, communicationTab, carsStatusTab, dbTab);

		/*
		 * SelectionModel<Tab> selectionModel = this.getSelectionModel();
		 * selectionModel.select(2);
		 */

		setSide(Side.BOTTOM);

		getStyleClass().add(TabPane.STYLE_CLASS_FLOATING);

	}// c'tor

	public void registerUIListener(UIEventsListener newListener) {
		this.uiListener = newListener;
	}

	// BLEvents
	// ----------------------------------------------------
	public void handleCarVisualDisplay(Car car) {
		carsStatusTab.handleCarVisualDisplay(car);
	}

	public void postString(String descriptionStr) {
		communicationTab.postString(descriptionStr);
	}

	public void handleTankFuelLevelLow() {
		menuTab.handleTankFuelLevelLow();
	}

	// ----------------------------------------------------

	// UIEvents
	// ----------------------------------------------------

	public void requestGasStationClosing() {
		Platform.runLater(new Runnable() {
			@Override
			public void run() {
				freezeGUI();
			}
		});
		uiListener.requestGasStationClosing();
	}

	public Statistics getStatistics() {
		return uiListener.getStatistics();
	}

	public void addCarFromFX(String[] carParameters, boolean fromClient)
			throws Exception {
		uiListener.addCarFromFX(carParameters, fromClient);
	}

	public int requestPumpNum() {
		return uiListener.requestPumpNum();
	}

	public void requestTankRefuel() {
		uiListener.requestTankRefuel();
	}

	public long requestTankRefuelTime() {
		return uiListener.requestTankRefuelTime();
	}

	public void requestTankLockRelease() {
		uiListener.requestTankLockRelease();
	}

	// SQL

	public HashMap<String, Object> requestFuelFormSubmission(String sql,
			String jpaSql) throws Exception {
		return uiListener.requestFuelFormSubmission(sql, jpaSql);
	}

	public HashMap<String, Object> requestCleaningFormSubmission(String sql,
			String jpaSql) throws Exception {
		return uiListener.requestCleaningFormSubmission(sql, jpaSql);
	}

	// ---

	public HashMap<String, Object> requestTotProfitsFormSubmission()
			throws Exception {
		return uiListener.requestTotProfitsFormSubmission();
	}

	// ----------------------------------------------------

	private void freezeGUI() {
		ObservableList<Tab> tabList = getTabs();
		for (Tab tab : tabList) {
			tab.setDisable(true);
		}
	}
}// TabsPane

