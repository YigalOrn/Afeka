package aspectjLogging;

import java.util.logging.Level;

import serverSide.bl.GasStationTasks.RefillMainFuelTask;



privileged aspect RefillMainFuelTaskAspectJ {

	after(RefillMainFuelTask rt): call(private void acquire(int)) && within(RefillMainFuelTask) && target(rt){
		LoggerAspect.logger.log(Level.INFO, "refuel the main Fuel Stock Started",
				rt.fuelStock);
	}

	// fuelStock.addFuel(amount);
	after(RefillMainFuelTask rt): call( * Thread.sleep(..)) && within(RefillMainFuelTask) && this(rt){
		LoggerAspect.logger.log(Level.INFO, "refuel the main Fuel Stock Endded",
				rt.fuelStock);
	}

}
