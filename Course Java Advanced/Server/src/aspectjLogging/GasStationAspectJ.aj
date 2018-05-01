package aspectjLogging;

import java.util.logging.Level;

import serverSide.bl.GasStationBL.Car;

privileged aspect GasStationAspectJ {

	before(Car car): call(public void dispose()) && target(car){

		LoggerAspect.logger.log(Level.INFO, "Car" + car.getId()
				+ " exited the GasStation", car);

	}

}
