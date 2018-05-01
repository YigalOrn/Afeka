package serverSide.bl.GasStationBL;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import serverSide.bl.GasStationEvents.GasStationUiEventListener;
import serverSide.bl.GasStationExceptions.InvalidPumpException;
import serverSide.bl.GasStationExceptions.MainFuelStockEmptyException;
import serverSide.bl.GasStationExceptions.MainFuelStockLowException;
import serverSide.bl.GasStationExceptions.StationClosedException;
import serverSide.bl.GasStationTasks.CleanTask;
import serverSide.bl.GasStationTasks.FuelTask;
import serverSide.bl.GasStationTasks.RefillMainFuelTask;
import serverSide.events.blui.BL1EventsListener;
import serverSide.events.serverbl.BL2EventsListener;
import serverSide.events.sqlbl.BL3EventsListener;
import serverSide.ui.ICloseStage;

public class GasStation {

	/** Data fields */
	private Vector<GasStationUiEventListener> listeners;
	private int numOfPumps;
	private float pricePerLiter;
	private FuelStock MainFuelPool;
	private WashService CleaningService;
	private ArrayList<Car> cars;
	private ArrayList<FuelPump> fuelPumps;
	private Semaphore MainFuelPoolLock;
	private boolean StationActive;
	private Statistics gasStationStatistics;

	// -----------------

	/*
	 * bl-ui
	 */
	private BL1EventsListener bl1Listener;

	/*
	 * bl-server
	 */
	private BL2EventsListener bl2Listener;
	/*
	 * bl-dal
	 */
	private BL3EventsListener bl3Listener;

	private ExecutorService executor;
	private ArrayList<Car> xmlCars;
	private ReentrantLock lock;
	private long animataionProgressBarTime;
	private ICloseStage stageCloser;

	// -----------------

	/** C'tor */
	public GasStation(int numOfPumps, float pricePerLiter)
			throws SecurityException, IOException {

		this.numOfPumps = numOfPumps;
		this.pricePerLiter = pricePerLiter;
		cars = new ArrayList<Car>();
		fuelPumps = new ArrayList<FuelPump>();
		for (int i = 0; i < numOfPumps; i++) {
			fuelPumps.add(new FuelPump(i));// Pumps start from 0
		}
		MainFuelPoolLock = new Semaphore(numOfPumps);
		listeners = new Vector<>();
		gasStationStatistics = new Statistics(numOfPumps, pricePerLiter);

		/*
		 * logHandler = new FileHandler("logs/GasStation.xml");
		 * logHandler.setFormatter(new GenericFotmat());
		 * logger.addHandler(logHandler); logger.setUseParentHandlers(false);
		 */

		// -----------------
		setIsActive(true);
		lock = new ReentrantLock(true);
		xmlCars = new ArrayList<>();
		executor = Executors.newCachedThreadPool();
		// -----------------

	}

	public void setFuelStock(FuelStock fuelStock) {
		this.MainFuelPool = fuelStock;
		//
		getGasStationStatistics().setStatisticsMainFuelPool(fuelStock);
	}

	public void setWashService(WashService washService) {
		this.CleaningService = washService;
	}

	public void addNewCar(Car car) throws InvalidPumpException,
			StationClosedException {
		if (!isActive())
			throw new StationClosedException();
		cars.add(car);
		moveToTasks(car);
	}

	public void moveToTasks(Car car) throws InvalidPumpException {

		if (car.isWantFuel() && isActive()) {

			FuelPump fp = this.findFuelPumpByID(car.getWantFuelPumpNum());
			FuelTask ft = new FuelTask(car, this, fp);

			// -----------------
			String msg = "Car " + car.getId() + " waits for refueling";
			car.setState(CarStatus.carState.FUELQUEUE);
			reportCarProgress(car, msg);
			// -----------------

			fp.fuel(ft);

		} else if (car.isWantCleaning() && isActive()) {

			CleanTask ct = new CleanTask(car, this);

			// -----------------
			String msg = "Car " + car.getId() + " waits for cleaning";
			car.setState(CarStatus.carState.CLEANQUEUE);
			reportCarProgress(car, msg);
			// -----------------

			CleaningService.clean(ct);

		} else {

			// -----------------
			String msg = "Car " + car.getId() + " exits gas station";
			car.setState(CarStatus.carState.DONE);
			reportCarProgress(car, msg);
			// -----------------

			// Close this car logger handler
			car.dispose();

			cars.remove(car);
		}

	}

	public void registerListener(GasStationUiEventListener listener) {
		listeners.add(listener);

	}

	@Override
	public String toString() {
		return MainFuelPool.toString() + CleaningService.toString()
				+ numOfPumps + pricePerLiter + carsString();
	}

	public FuelPump findFuelPumpByID(int id) throws InvalidPumpException {
		for (FuelPump fp : fuelPumps)
			if (fp.getFuelPumpID() == id)
				return fp;
		throw new InvalidPumpException(id);
	}

	private String carsString() {
		String output = "";
		for (Car car : cars)
			output += car.toString();
		return output;
	}

	public void fillTheMainPumpModel(final float amount) {
		RefillMainFuelTask rmft = new RefillMainFuelTask(amount, this);
		this.MainFuelPool.performTask(rmft);
	}

	public WashService getCleaningService() {
		return CleaningService;
	}

	public Semaphore getMainFuelPoolLock() {
		return MainFuelPoolLock;
	}

	public FuelStock getMainFuelPool() {
		return MainFuelPool;
	}

	public int getNumOfPumps() {
		return numOfPumps;
	}

	public void throwException(Exception e) {

		if (e instanceof MainFuelStockLowException
				|| e instanceof MainFuelStockEmptyException) {
			fireTankFuelLevelAlert();
		}

		for (GasStationUiEventListener lis : listeners)
			lis.sendException(e);
	}

	public Statistics getGasStationStatistics() {
		return gasStationStatistics;
	}

	public void closeStation() {

		if (isActive()) {
			setIsActive(false);

			stageCloser.closeStage();

			try {
				for (FuelPump fp : fuelPumps)
					fp.close();
				MainFuelPool.close();
				MainFuelPoolLock.acquire(numOfPumps);
				CleaningService.close();
				MainFuelPoolLock.release(numOfPumps);
			} catch (InterruptedException e) {
				MainFuelPoolLock.release(numOfPumps);
				throwException(e);
			}

			// -----------------
			try {
				fireCloseServer();
				executor.shutdownNow();
				fireCloseDbConnection();
			} catch (Exception e) {
				e.printStackTrace();
			}
			// -----------------

		}

	}

	// ----------------------------------------------------------------------------------------------------------

	// --------------
	// GasStation related

	public void setWindowCloser(ICloseStage stageCloser) {
		this.stageCloser = stageCloser;
	}

	private synchronized boolean isActive() {
		return StationActive;
	}

	private synchronized void setIsActive(boolean newState) {
		StationActive = newState;
	}

	public void addToHoldList(Car car) {
		xmlCars.add(car);
	}

	public void activateHoldList() {
		for (Car car : xmlCars) {
			if (!executor.isShutdown() && isActive()) {
				Thread thrActivateCar = new Thread(new Runnable() {
					@Override
					public void run() {
						try {
							addNewCar(car);
						} catch (InvalidPumpException | StationClosedException e) {
							e.printStackTrace();
						}
					}
				});
				thrActivateCar.setName(thrActivateCar.getName()
						+ "thrActivateCar");
				executor.execute(thrActivateCar);
			}
		}
		xmlCars.clear();
		xmlCars = null;
	}

	/**
	 * Overloaded
	 */
	public void addNewCar(String[] carParameters, boolean fromClient)
			throws StationClosedException, SecurityException, IOException,
			InvalidPumpException {

		if (!isActive())
			throw new StationClosedException();

		Car car = null;

		int carId = Integer.parseInt(carParameters[0]);

		boolean wantCleaning = false;

		if (carParameters[1].equalsIgnoreCase("true"))
			wantCleaning = true;

		car = new Car(carId, wantCleaning);

		car.setFromClient(fromClient);

		if ((!carParameters[2].isEmpty()) && (!carParameters[3].isEmpty())) {
			double numOfLiters = Double.parseDouble(carParameters[2]);
			int pumpNum = Integer.parseInt(carParameters[3]);
			car.WantsFuel((float) numOfLiters, pumpNum);
		}// if

		cars.add(car);
		moveToTasks(car);

	}

	public void fillTheMainPumpModel() {

		float maxCapcity = getMainFuelPool().getMaxCapacity();
		float currentFuelAmount = (float) getMainFuelPool().getfuelAmount();

		if ((maxCapcity - currentFuelAmount) != 0) {
			fillTheMainPumpModel(maxCapcity - currentFuelAmount);
		} else {
			setanimataionProgressBarTime(-1);
		}
	}

	public void releaseLockForTankRefill() {
		getMainFuelPoolLock().release(getNumOfPumps());
	}

	public void setanimataionProgressBarTime(long time) {
		animataionProgressBarTime = time;
	}

	public long getAnimationTime() {
		return animataionProgressBarTime;
	}

	// --------------

	// --------------
	// SQL related
	public synchronized void recordPumpActivity(String carId, int pumpNum,
			double amount) throws Exception {
		double pumpProfit = amount * pricePerLiter;
		fireRecordPumpActivity(carId, pumpNum, pumpProfit);
	}

	public synchronized void recordCleanActivity(String carId) throws Exception {
		double profit = getCleaningService().getCleaningPrice();
		fireRecordCleanActivity(carId, profit);
	}

	public synchronized HashMap<String, Object> submitQueryFormDbTab(
			String sql, String jpaSql) throws Exception {
		return fireSubmitQueryFormDbTab(sql, jpaSql);
	}

	public synchronized HashMap<String, Object> getTotProfits()
			throws Exception {
		return fireGetTotProfits();
	}

	public synchronized String getCarHistory(String carId) throws Exception {
		return fireGetCarHistory(carId);
	}

	// --------------

	// --------------
	public void registerBL1Listener(BL1EventsListener newListener) {
		this.bl1Listener = newListener;
	}

	public void registerBL2Listener(BL2EventsListener newListener) {
		bl2Listener = newListener;
	}

	public void registerBL3Listener(BL3EventsListener newListener) {
		bl3Listener = newListener;
	}

	// --------------

	// --------------
	// Event related
	public void reportCarProgress(Car car, String msg) {

		if (!isActive())
			return;

		lock.lock();
		try {
			firePostCarProgressReportTextual(msg);
			if (car.getState() != CarStatus.carState.TEXTONLY) {
				firePostCarProgressReportByImage(car);
			}
			if (car.isFromClient() && fireGetIsServerOnline()) {
				fireReportToServerClient(car, msg);
			}
		} finally {
			lock.unlock();
		}
	}

	private void firePostCarProgressReportTextual(String msg) {
		bl1Listener.handleCarProgressTextualy(msg);
	}

	private void firePostCarProgressReportByImage(Car car) {
		bl1Listener.handleCarProgressByImage(car);
	}

	private void fireTankFuelLevelAlert() {
		bl1Listener.handleTankFuelLevelLow();
	}

	// ----

	private void fireCloseServer() {
		bl2Listener.reqeustCloseServer();
	}

	private boolean fireGetIsServerOnline() {
		return bl2Listener.getIsServerOnline();
	}

	private void fireReportToServerClient(Car car, String msg) {
		bl2Listener.ReportToServerClient(car, msg);
	}

	// ----
	private void fireCloseDbConnection() throws Exception {
		bl3Listener.closeDbConnection();
	}

	private void fireRecordPumpActivity(String carId, int pumpNum, double amount)
			throws Exception {
		bl3Listener.recordPumpActivity(carId, pumpNum, amount);
	}

	private void fireRecordCleanActivity(String carId, double profit)
			throws Exception {
		bl3Listener.recordCleanActivity(carId, profit);
	}

	private HashMap<String, Object> fireSubmitQueryFormDbTab(String sql,
			String jpaSql) throws Exception {
		return bl3Listener.submitQueryFormDbTab(sql, jpaSql);
	}

	private HashMap<String, Object> fireGetTotProfits() throws Exception {
		return bl3Listener.getTotProfits();
	}

	private String fireGetCarHistory(String carId) throws Exception {
		return bl3Listener.getCarHistory(carId);
	}
	// --------------

	// ----------------------------------------------------------------------------------------------------------

}
