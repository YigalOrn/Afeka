package serverSide.bl.GasStationTasks;

import java.sql.SQLException;
import java.util.concurrent.Semaphore;

import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.FuelPump;
import serverSide.bl.GasStationBL.FuelStock;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.MainFuelStockEmptyException;
import serverSide.bl.GasStationExceptions.MainFuelStockLowException;

public class FuelTask extends AbstractTask {

	private float fuelTimePerLiterSec;
	private Semaphore MainFuelPoolLock;
	private FuelStock fuelStock;
	private FuelPump fuelPump;

	public FuelTask(Car car, GasStation context, FuelPump fuelPump)
			throws InvalidPumpException {
		super(context);
		this.car = car;
		this.MainFuelPoolLock = context.getMainFuelPoolLock();
		this.fuelStock = context.getMainFuelPool();
		this.fuelPump = fuelPump;
		this.fuelTimePerLiterSec = fuelPump.getFuelTimePerLiterSec();

	}

	@Override
	public void run() {

		float fuelingTime = fuelTimePerLiterSec
				* this.car.getWantFuelNumOfLiters();

		synchronized (car) {

			try {

				setAndAcquire();

				

				// Checks the main fuel pool amount, throws
				fuelStock.pumpFuel(car.getWantFuelNumOfLiters());

				// -----------------
				String msg = "Car " + car.getId() + " is refueling";
				car.setState(CarStatus.carState.REFUELING);
				context.reportCarProgress(car, msg);
				// -----------------

				Thread.sleep((long) fuelingTime);

				MainFuelPoolLock.release();

				context.getGasStationStatistics().addFuelingInfo(fuelingTime,
						car.getWantFuelNumOfLiters());

				context.getGasStationStatistics().addFuelingInfoToPump(
						car.getWantFuelPumpNum(), car.getWantFuelNumOfLiters());

			} catch (InterruptedException e) {
				context.throwException(e);
			} catch (MainFuelStockEmptyException e) {

				context.getGasStationStatistics().addFuelingInfo(fuelingTime,
						e.amount);
				context.throwException(e);

				// -----------------
				String msg = "Car " + car.getId() + " No gas available!";
				car.setState(CarStatus.carState.TEXTONLY);
				context.reportCarProgress(car, msg);
				// -----------------

			} catch (MainFuelStockLowException e) {

				context.getGasStationStatistics().addFuelingInfo(fuelingTime,
						e.amount);
				context.throwException(e);

				/*
				 * 
				 * This exception is shown in GUI, blinking button
				 */

			} finally {

			

				// -----------------
				String msg = "Car " + car.getId() + " done refueling";
				car.setState(CarStatus.carState.TEXTONLY);
				context.reportCarProgress(car, msg);

				try {
					context.recordPumpActivity("" + car.getId(),
							car.getWantFuelPumpNum(),
							car.getWantFuelNumOfLiters());
				} catch (SQLException e) {
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}

				// -----------------

				setAndRelease();

				car.setWantFuel(false);

				try {

					context.moveToTasks(car);

				} catch (InvalidPumpException e) {
					context.throwException(e);
				}

			}

		}

	}

	/** For AspectJ */
	private void setAndAcquire() throws InterruptedException {
		fuelPump.setBusy(true);
		MainFuelPoolLock.acquire();
	}

	/** For AspectJ */
	private void setAndRelease() {
		MainFuelPoolLock.release();
		fuelPump.setBusy(false);

	}

}
