package serverSide.bl.GasStationEvents;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.Statistics;
import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.StationClosedException;



public interface GasStationEventsListener {
	void addcarModel(Car car) throws InvalidPumpException, StationClosedException;
	void fillTheMainPumpModel(float amount);
	Statistics getStatistics();
	void closeTheDayModel();
}
