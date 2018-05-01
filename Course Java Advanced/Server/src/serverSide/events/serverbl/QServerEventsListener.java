package serverSide.events.serverbl;

import java.io.IOException;

import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.StationClosedException;

public interface QServerEventsListener {

	int RequestNumberOfPumps();

	void submitNewCar(String[] param, boolean isFromClient)
			throws SecurityException, StationClosedException, IOException, InvalidPumpException;
	
	
	String requestCarHistory(String carId) throws Exception;
	
}
