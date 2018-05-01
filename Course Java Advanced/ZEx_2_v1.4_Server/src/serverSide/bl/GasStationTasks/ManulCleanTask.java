package serverSide.bl.GasStationTasks;

import java.sql.SQLException;
import java.util.Random;


import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationExceptions.InvalidPumpException;

public class ManulCleanTask extends AbstractTask {

	private float cleanTime;

	public ManulCleanTask(Car car, GasStation context) {
		super(context);
		this.cleanTime = new Random().nextFloat() * 10;
		this.car = car;
	}

	@Override
	public void run() {
		synchronized (car) {
			try {

		

				// -----------------
				String msg = "Car " + car.getId() + " enters manual cleaning";
				car.setState(CarStatus.carState.MANUALWASH);
				context.reportCarProgress(car, msg);
				// -----------------

				Thread.sleep((long) cleanTime * 100);

				// -----------------
				msg = "Car " + car.getId() + " finished manual cleaning";
				car.setState(CarStatus.carState.TEXTONLY);
				context.reportCarProgress(car, msg);

				try {
					context.recordCleanActivity("" + car.getId());
				} catch (SQLException e) {
					e.printStackTrace();
				} catch (Exception e) {

					e.printStackTrace();
				}

				// -----------------

			

				context.getGasStationStatistics().addCleaningInfo(
						cleanTime * 100);

				context.getGasStationStatistics().addCleaningprofit(
						context.getCleaningService().getCleaningPrice());

				car.setWantCleaning(false);

				context.moveToTasks(car);

			} catch (InterruptedException e) {
				context.throwException(e);
			} catch (InvalidPumpException e) {
				context.throwException(e);
			}
		}

	}

}
