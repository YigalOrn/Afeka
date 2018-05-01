package aspectjLogging;

import java.util.logging.Level;

import serverSide.bl.GasStationTasks.FuelTask;

privileged aspect FuelTaskAspectJ {

	private float fuelingTime;

	before(FuelTask ft): execution(public void run()) && within(FuelTask) && target(ft){

		this.fuelingTime = ft.fuelTimePerLiterSec
				* ft.car.getWantFuelNumOfLiters();

	}

	after(FuelTask ft): call(private void setAndAcquire()) && within(FuelTask) && target(ft)
	{

		LoggerAspect.logger.log(Level.INFO, "Fuel task Started for Car" + ft.car.getId()
				+ " Fueling Time " + fuelingTime, ft.fuelPump);

		LoggerAspect.logger.log(Level.INFO, "Fuel task Started Fueling Time "
				+ fuelingTime, ft.car);

	}

	after(FuelTask ft): execution(public void run()) && within(FuelTask) && target(ft){

		LoggerAspect.logger.log(Level.INFO, "Fuel task Endded in: " + fuelingTime
				+ " for Car" + ft.car.getId(), ft.fuelPump);

		LoggerAspect.logger.log(Level.INFO, "Fuel task Endded in: " + fuelingTime, ft.car);

	}

}
