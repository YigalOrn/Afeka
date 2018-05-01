package aspectjLogging;

import java.util.logging.Level;

import serverSide.bl.GasStationTasks.ManulCleanTask;



privileged aspect ManulCleanTaskAspectJ {

	after(ManulCleanTask mt): execution(public void run()) && within(ManulCleanTask) && target(mt){

		LoggerAspect.logger.log(Level.INFO,
				"Manual Clean Started for Car" + mt.car.getId(), mt.context);

		LoggerAspect.logger.log(Level.INFO, "Manual Clean Started", mt.car);

	}

	after(ManulCleanTask mt): call( * Thread.sleep(..)) && within(ManulCleanTask) && this(mt){
		
		LoggerAspect.logger.log(Level.INFO, "Manual Clean Endded in: " + mt.cleanTime
				+ " for Car" + mt.car.getId(), mt.context);

		LoggerAspect.logger.log(Level.INFO, "Manual Clean Endded in: " + mt.cleanTime,
				mt.car);

	}
}
