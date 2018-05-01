package serverSide.bl.GasStationBL;

import java.io.IOException;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import serverSide.bl.GasStationTasks.FuelTask;

public class FuelPump {

	private int id;
	private float fuelTimePerLiterSec;
	private ExecutorService thePump;
	private boolean busy;

	public FuelPump(int id) throws SecurityException, IOException {
		this.id = id;

		fuelTimePerLiterSec = new Random().nextInt(100);
		thePump = Executors.newSingleThreadExecutor();
	}

	public int getFuelPumpID() {
		return this.id;
	}

	public float getFuelTimePerLiterSec() {
		return fuelTimePerLiterSec;
	}

	public void fuel(FuelTask ft) {
		Thread thrFuelTask = new Thread(ft);
		thrFuelTask.setName(thrFuelTask.getName() + "thrFuelTask");
		thePump.execute(thrFuelTask);
	}

	public synchronized boolean isBusy() {
		return busy;
	}

	public synchronized void setBusy(boolean busy) {
		this.busy = busy;
	}

	public void close() throws InterruptedException {
		thePump.shutdown();
	}

}
