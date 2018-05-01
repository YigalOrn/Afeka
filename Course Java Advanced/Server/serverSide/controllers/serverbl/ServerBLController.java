package serverSide.controllers.serverbl;

import java.io.IOException;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.StationClosedException;
import serverSide.events.serverbl.BL2EventsListener;
import serverSide.events.serverbl.QServerEventsListener;
import serverSide.server.QServer;

public class ServerBLController implements QServerEventsListener,
		BL2EventsListener {

	private QServer qServer;
	private GasStation gasStation;

	public ServerBLController(QServer server, GasStation gasStation) {
		this.qServer = server;
		this.gasStation = gasStation;

		// ---
		gasStation.registerBL2Listener(this);
		// ---

		// ---
		qServer.registerServerBlListener(this);
		// ---

	}

	// BL2Events
	// ----------------------------------------------------

	@Override
	public void reqeustCloseServer() {
		qServer.closeServer();
	}

	@Override
	public boolean getIsServerOnline() {
		return qServer.isOnLine();
	}

	@Override
	public void ReportToServerClient(Car car, String msg) {
		qServer.reportToClient(car, msg);
	}

	// ----------------------------------------------------

	// QServerEvents
	// ----------------------------------------------------

	@Override
	public void submitNewCar(String[] param, boolean isFromClient)
			throws SecurityException, StationClosedException, IOException,
			InvalidPumpException {
		gasStation.addNewCar(param, isFromClient);
	}

	@Override
	public int RequestNumberOfPumps() {
		return gasStation.getNumOfPumps();
	}

	@Override
	public String requestCarHistory(String carId) throws Exception {
		return gasStation.getCarHistory(carId);
	}

	// ----------------------------------------------------
}
