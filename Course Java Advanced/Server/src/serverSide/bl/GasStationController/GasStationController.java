package serverSide.bl.GasStationController;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationBL.Statistics;
import serverSide.bl.GasStationEvents.GasStationEventsListener;
import serverSide.bl.GasStationEvents.GasStationUiEventListener;
import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.StationClosedException;
import serverSide.bl.GasStationViews.AbstractGasStationView;

public class GasStationController implements GasStationUiEventListener,
		GasStationEventsListener {

	private GasStation theStationModel;
	private AbstractGasStationView stationView;

	public GasStationController(AbstractGasStationView theView,
			GasStation station) {
		theStationModel = station;
		stationView = theView;

		theStationModel.registerListener(this);
		stationView.registerListener(this);
	}

	@Override
	public void addcarModel(Car car) throws InvalidPumpException,
			StationClosedException {
		theStationModel.addNewCar(car);
	}

	@Override
	public void fillTheMainPumpModel(float amount) {
		theStationModel.fillTheMainPumpModel(amount);
	}

	@Override
	public void closeTheDayModel() {
		theStationModel.closeStation();
	}

	@Override
	public void sendException(Exception e) {
		stationView.getException(e);

	}

	@Override
	public Statistics getStatistics() {
		return theStationModel.getGasStationStatistics();
	}

}
