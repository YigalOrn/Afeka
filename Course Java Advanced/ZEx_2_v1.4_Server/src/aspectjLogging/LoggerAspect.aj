/*
 * https://www.eclipse.org/aspectj/doc/released/progguide/
 * */

package aspectjLogging;

import java.io.IOException;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Logger;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.FuelPump;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationBL.WashService;

import serverSide.bl.GasStationLogging.GenericFilter;
import serverSide.bl.GasStationLogging.GenericFotmat;


privileged aspect LoggerAspect {

	public static Logger logger = Logger.getLogger("GSLog");
	private ReentrantLock locky = new ReentrantLock(true);

	static {
		logger.setUseParentHandlers(false);
	}

	/*
	 * Register all handlers after each relevant C'tor call
	 */

	pointcut loggerCtors():
		execution(Car.new(..)) ||
		execution(FuelPump.new(..)) ||
		execution(GasStation.new(..)) ||
		execution(WashService.new(..));

	after(Object obj): loggerCtors() && target(obj)
	{

		locky.lock();

		try {

			String className = obj.getClass().getSimpleName();
			Handler logHandler = null;

			switch (className) {

			case "Car": {
				logHandler = new FileHandler("logs/Cars/Car-"
						+ ((Car) obj).getId() + ".txt");
				logHandler.setFilter(new GenericFilter(obj));

				logHandler.setFormatter(new GenericFotmat());
				logger.addHandler(logHandler);

				break;
			}
			case "GasStation": {
				logHandler = new FileHandler("logs/GasStation.txt");

				logHandler.setFormatter(new GenericFotmat());
				logger.addHandler(logHandler);

				break;
			}
			case "FuelPump": {
				logHandler = new FileHandler("logs/FuelPumps/FuelPump-"
						+ ((FuelPump) obj).id + ".txt");
				logHandler.setFilter(new GenericFilter(obj));

				logHandler.setFormatter(new GenericFotmat());
				logger.addHandler(logHandler);

				break;
			}
			case "WashService": {
				logHandler = new FileHandler(
						"logs/WashServices/WashService.txt");
				logHandler.setFilter(new GenericFilter(obj));

				logHandler.setFormatter(new GenericFotmat());
				logger.addHandler(logHandler);

				break;
			}
			default:
				// Do nothing
				break;
			}// switch

		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			locky.unlock();
		}

	}

	after(): execution(public void closeStation()) && within(serverSide.bl.GasStationBL.GasStation)
	{
		Handler[] handlers = logger.getHandlers();
		for (Handler handler : handlers) {
			handler.close();
		}
	}

}//

