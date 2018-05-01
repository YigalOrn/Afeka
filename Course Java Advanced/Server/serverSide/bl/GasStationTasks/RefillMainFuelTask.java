package serverSide.bl.GasStationTasks;

import java.util.Random;
import java.util.concurrent.Semaphore;


import serverSide.bl.GasStationBL.FuelStock;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationExceptions.MainFuelStockOverFlow;

public class RefillMainFuelTask extends AbstractTask {

	private float amount;
	private Semaphore MainFuelPoolLock;
	private FuelStock fuelStock;
	private int numOfPumps;
	private float fulingTime;

	public RefillMainFuelTask(float amount, GasStation context) {
		super(context);
		this.amount = amount;
		this.MainFuelPoolLock = context.getMainFuelPoolLock();
		this.fuelStock = context.getMainFuelPool();
		this.numOfPumps = context.getNumOfPumps();

		/*
		 * 
		 * Moved here For AspectJ
		 */
		fulingTime = new Random().nextInt(210);
		context.setanimataionProgressBarTime((long) fulingTime);// GUI

	}

	@Override
	public void run() {

		try {

			acquire(numOfPumps);

			

			Thread.sleep((long) fulingTime);

			fuelStock.addFuel(amount);

			context.getGasStationStatistics().addMainFuelingInfo(fulingTime,
					amount);


		} catch (InterruptedException e) {
			release(numOfPumps);
			;
		} catch (MainFuelStockOverFlow e) {

			release(numOfPumps);

			context.getGasStationStatistics().addMainFuelingInfo(fulingTime,
					e.amount);

			context.throwException(e);
		}

	}

	private void acquire(int numOfPumps) throws InterruptedException {
		MainFuelPoolLock.acquire(numOfPumps);
	}

	private void release(int numOfPumps) {
		MainFuelPoolLock.release(numOfPumps);
	}
}
