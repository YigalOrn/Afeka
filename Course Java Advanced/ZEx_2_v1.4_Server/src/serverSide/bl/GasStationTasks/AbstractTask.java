package serverSide.bl.GasStationTasks;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.GasStation;

public abstract class AbstractTask implements Runnable {

	protected Car car;
	protected GasStation context;

	// protected static Logger logger = Logger.getLogger("GSLog");

	protected AbstractTask(GasStation context) {
		this.context = context;
	}

}
