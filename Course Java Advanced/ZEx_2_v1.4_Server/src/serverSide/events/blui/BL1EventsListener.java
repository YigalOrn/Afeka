package serverSide.events.blui;


import serverSide.bl.GasStationBL.Car;


public interface BL1EventsListener {

	/*
	 * Appends the description string to the CommunicationTab TextArea for Cars
	 * created from clients or gas station FX GUI
	 */
	void handleCarProgressTextualy(String descriptionStr);

	/*
	 * handles the visual Car progress presented in the CarsView
	 */
	void handleCarProgressByImage(Car car);
	
	
	void handleTankFuelLevelLow();
	
}
