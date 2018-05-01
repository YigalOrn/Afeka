package aspectjLogging;

import java.util.logging.Level;

import serverSide.bl.GasStationTasks.CleanTask;

privileged aspect CleanTaskAspectJ {

	after(CleanTask ct): execution(public void run()) && within(CleanTask) && target(ct){

		LoggerAspect.logger.log(Level.INFO, "Auto Clean Started for Car" + ct.car.getId()
				+ "Cleaning Time" + ct.cleanTime * 1000, ct.context);
		LoggerAspect.logger.log(Level.INFO, "Auto Clean Started Cleaning Time"
				+ ct.cleanTime * 1000, ct.car);

	}

	after(CleanTask ct): call( * Thread.sleep(..)) && within(CleanTask) && this(ct){

		LoggerAspect.logger.log(Level.INFO, "Auto Clean Endded in: " + ct.cleanTime
				+ " for Car" + ct.car.getId(), ct.context);
		LoggerAspect.logger.log(Level.INFO, "Auto Clean Endded in: " + ct.cleanTime,
				ct.car);

	}

}
