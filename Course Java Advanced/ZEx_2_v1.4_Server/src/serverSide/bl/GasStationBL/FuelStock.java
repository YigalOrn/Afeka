package serverSide.bl.GasStationBL;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import serverSide.bl.GasStationExceptions.MainFuelStockEmptyException;
import serverSide.bl.GasStationExceptions.MainFuelStockLowException;
import serverSide.bl.GasStationExceptions.MainFuelStockOverFlow;
import serverSide.bl.GasStationTasks.AbstractTask;

public class FuelStock {
	private float maxCapacity;
	private float currentCapacity;
	private ExecutorService jobExecutorService;
	private final float redLine = 0.2f;

	public FuelStock(float maxCapacity, float currentCapacity) {
		this.maxCapacity = maxCapacity;
		this.currentCapacity = currentCapacity;
		this.jobExecutorService = Executors.newSingleThreadExecutor();
	}

	public synchronized double getfuelAmount() {
		return currentCapacity;
	}

	public synchronized void pumpFuel(float pumpAmount)
			throws MainFuelStockLowException, MainFuelStockEmptyException {
		if (currentCapacity - pumpAmount < 0) {
			float diff = currentCapacity;
			currentCapacity = 0;
			throw new MainFuelStockEmptyException(diff);
		}
		currentCapacity -= pumpAmount;
		
	
		if (currentCapacity / maxCapacity <= redLine)
			throw new MainFuelStockLowException(currentCapacity);
	
	
	
	
	}

	public synchronized void addFuel(float amount) throws MainFuelStockOverFlow {
		if (amount + currentCapacity > maxCapacity) {
			float diff = maxCapacity - currentCapacity;
			currentCapacity = maxCapacity;
			throw new MainFuelStockOverFlow(diff);
		} else
			currentCapacity += amount;
	}

	public String toString() {
		return "Fuel maxCapacity=" + maxCapacity + " currentCapacity="
				+ currentCapacity;
	}

	public void performTask(AbstractTask rmft) {
		if (!jobExecutorService.isShutdown())
			jobExecutorService.execute(rmft);
	}

	public void close() throws InterruptedException {
		jobExecutorService.shutdown();
		jobExecutorService.awaitTermination(Long.MAX_VALUE,
				TimeUnit.NANOSECONDS);
	}

	public float getMaxCapacity() {
		return maxCapacity;
	}

}
