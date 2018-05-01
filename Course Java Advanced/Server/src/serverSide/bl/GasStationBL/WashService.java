package serverSide.bl.GasStationBL;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import serverSide.bl.GasStationTasks.CleanTask;
import serverSide.bl.GasStationTasks.ManulCleanTask;

public class WashService {
	private int numOfTeams;
	private float price;
	private int secondsPerAutoClean;
	private ExecutorService machine;
	private ExecutorService cleaningTeams;

	public WashService(int numOfTeams, float price, int secondsPerAutoClean)
			throws SecurityException, IOException {
		
		this.numOfTeams = numOfTeams;
		this.price = price;
		this.secondsPerAutoClean = secondsPerAutoClean;
		machine = Executors.newSingleThreadExecutor();
		cleaningTeams = Executors.newFixedThreadPool(numOfTeams);

	}

	public void clean(CleanTask ct) {
		if (!machine.isShutdown())
			machine.execute(ct);
	}

	@Override
	public String toString() {
		return "WashService [numOfTeams=" + numOfTeams + ", price=" + price
				+ ", secondsPerAutoClean=" + secondsPerAutoClean + "]";
	}

	public int getSecondsPerAutoClean() {
		return secondsPerAutoClean;
	}

	public void setManualClean(ManulCleanTask mct) {
		if (!cleaningTeams.isShutdown())
			cleaningTeams.execute(mct);
	}

	public void close() {
		cleaningTeams.shutdown();
		machine.shutdown();
	}

	public float getCleaningPrice() {
		return price;
	}

}
