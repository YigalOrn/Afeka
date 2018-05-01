package serverSide.bl.GasStationTasks;



import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.GasStation;

public class CleanTask extends AbstractTask {

	protected float cleanTime;

	public CleanTask(Car car, GasStation context) {
		super(context);
		this.car = car;
	}

	@Override
	public void run() {
		synchronized (car) {
			try {

				/** Logger, AspectJ */

				// -----------------
				String msg = "Car " + car.getId() + " enters autowash";
				car.setState(CarStatus.carState.AUTOWASH);
				context.reportCarProgress(car, msg);
				// -----------------

				Thread.sleep((long) cleanTime * 1000);

				// -----------------
				msg = "Car " + car.getId() + " finished autowash";
				car.setState(CarStatus.carState.TEXTONLY);
				context.reportCarProgress(car, msg);
				// -----------------

				/** Logger, AspectJ */

			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}

		ManulCleanTask mct = new ManulCleanTask(car, context);
		context.getCleaningService().setManualClean(mct);
	}

}
