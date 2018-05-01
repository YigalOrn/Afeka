package serverSide.bl.GasStationBL;

public class Statistics {
	private int mainFuelStockRefuelingTimes;
	private float TotalMainFuelRefuelTime;
	private float amountMainFueled;
	private float TotalPumpFuelngTime;

	private int CleanTimes;
	private float TotalCleanTime;
	private double cleaningProfit;

	private float amountFueled;
	private int pumpFuelingTimes;

	private double[] pumpsFuel;
	private double pricePerLiter;

	private FuelStock MainFuelPool;

	public Statistics(int numOfPumps, double pricePerLiter) {
		super();
		this.mainFuelStockRefuelingTimes = 0;
		this.pumpFuelingTimes = 0;
		this.CleanTimes = 0;
		this.TotalMainFuelRefuelTime = 0;
		this.TotalPumpFuelngTime = 0;
		this.TotalCleanTime = 0;
		this.cleaningProfit = 0;
		this.amountMainFueled = 0;
		this.amountFueled = 0;
		this.pricePerLiter = pricePerLiter;
		this.pumpsFuel = new double[numOfPumps];
	}

	public synchronized void addFuelingInfoToPump(int pumpNum, double amount) {
		pumpsFuel[pumpNum] += amount;
	}

	public synchronized void addFuelingInfo(double time, double amount) {
		this.pumpFuelingTimes++;
		this.amountFueled += amount;
	}

	public synchronized void addMainFuelingInfo(float time, float amount) {
		this.mainFuelStockRefuelingTimes++;
		this.amountMainFueled += amount;
	}

	public synchronized void addCleaningprofit(double price) {
		cleaningProfit += (getCleanTimes() * price);
	}

	public synchronized void addCleaningInfo(float time) {
		this.CleanTimes++;
	}

	public synchronized double getFuelingInfoOfPump(int pumpNum) {
		return pumpsFuel[pumpNum];
	}

	public synchronized int getMainFuelStockRefuelingTimes() {
		return mainFuelStockRefuelingTimes;
	}

	public synchronized float getTotalMainFuelRefuelTime() {
		return TotalMainFuelRefuelTime;
	}

	public synchronized double getCleaningProfit() {
		return cleaningProfit;
	}

	public synchronized float getAmountMainFueled() {
		return amountMainFueled;
	}

	public synchronized int getPumpFuelingTimes() {
		return pumpFuelingTimes;
	}

	public synchronized float getTotalPumpFuelngTime() {
		return TotalPumpFuelngTime;
	}

	public synchronized float getAmountFueled() {
		return amountFueled;
	}

	public synchronized double getPumpProfit(int pumpNum) {
		return (pumpsFuel[pumpNum] * pricePerLiter);
	}

	public synchronized double[] getPumpsFuel() {
		return pumpsFuel;
	}

	public synchronized int getCleanTimes() {
		return CleanTimes;
	}

	public synchronized float getTotalCleanTime() {
		return TotalCleanTime;
	}

	public synchronized double getTotalPumpsProfit() {
		double sum = 0;
		for (int i = 0; i < pumpsFuel.length; i++) {
			sum += getPumpProfit(i);
		}
		return sum;
	}

	public synchronized void setStatisticsMainFuelPool(FuelStock MainFuelPool) {
		this.MainFuelPool = MainFuelPool;
	}

	public synchronized float getCurrentCapacity() {

		if (MainFuelPool == null)
			return 0;
		else
			return (float) MainFuelPool.getfuelAmount();
	}
}
