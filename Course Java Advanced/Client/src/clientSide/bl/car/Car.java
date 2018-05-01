package clientSide.bl.car;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.logging.Handler;
import java.util.logging.FileHandler;
import java.util.logging.Logger;

import clientSide.bl.car.carComplementary.AnnotLeisurable;
import clientSide.bl.car.carComplementary.CarStatus;
import clientSide.bl.car.carComplementary.Leisurable;

;

public class Car implements Leisurable {

	private static Logger logger = Logger.getLogger("GSLog");
	private int id;
	private boolean wantCleaning;
	private boolean wantFuel;
	private float WantFuelNumOfLiters;
	private int WantFuelPumpNum;
	private Handler logHandler;

	// ---------------
	private boolean isFromClient;

	private CarStatus.carState state;

	private static ArrayList<String> newsLines = new ArrayList<String>();

	private static ArrayList<String> games = new ArrayList<String>();

	private static ArrayList<String> contactNames = new ArrayList<String>();

	// ---------------

	static {
		// ----
		newsLines.add("Reading news1...");
		newsLines.add("Reading news2...");
		newsLines.add("Reading news3...");
		newsLines.add("Reading news4...");
		newsLines.add("Reading news5...");
		// ----

		// ----
		games.add("Playing ClashOfClans...");
		games.add("Playing Sudoku...");
		games.add("Playing Kakuro...");
		games.add("Playing Candy Crush Saga...");
		games.add("Playing Texas Holdem...");
		// ----

		// ----
		contactNames.add("Calling Mom...");
		contactNames.add("Calling Dad...");
		contactNames.add("Calling Obama...");
		contactNames.add("Calling Putin...");
		contactNames.add("Calling Bibi...");
		contactNames.add("Calling last passengers...");
		contactNames.add("Calling 911...");
		contactNames.add("Calling the Pope...");
		contactNames.add("Calling Queen Elizabeth...");
		contactNames.add("Calling Bill Gates...");
		contactNames.add("Calling Mark Zuckerberg...");
		contactNames.add("Calling sick...");
		contactNames.add("Calling superman...");
		contactNames.add("Calling a taxi...");
		// ----
	}

	/** Default c'tor */
	public Car() {
	}

	public Car(int id, boolean wantCleaning) throws SecurityException,
			IOException {
		this.id = id;
		this.wantCleaning = wantCleaning;
		this.WantFuelNumOfLiters = 0;
		this.WantFuelPumpNum = 0;
		this.wantFuel = false;
		logHandler = new FileHandler("logs/Cars/Car-" + id + ".xml");
		logHandler.setFilter(new GenericFilter(this));
		logHandler.setFormatter(new GenericFotmat());
		logger.addHandler(logHandler);

	}

	public void WantsFuel(float WantFuelNumOfLiters, int WantFuelPumpNum) {
		this.WantFuelNumOfLiters = WantFuelNumOfLiters;
		this.WantFuelPumpNum = WantFuelPumpNum;
		this.wantFuel = true;
	}

	@Override
	public String toString() {
		return "Car [id=" + id + ", wantCleaning=" + wantCleaning
				+ ", wantFuel=" + wantFuel + ", WantFuelNumOfLiters="
				+ WantFuelNumOfLiters + ", WantFuelPumpNum=" + WantFuelPumpNum
				+ "]";
	}

	public int getId() {
		return id;
	}

	public boolean isWantCleaning() {
		return wantCleaning;
	}

	public boolean isWantFuel() {
		return wantFuel;
	}

	public float getWantFuelNumOfLiters() {
		return WantFuelNumOfLiters;
	}

	public int getWantFuelPumpNum() {
		return WantFuelPumpNum;
	}

	public void setWantCleaning(boolean wantCleaning) {
		this.wantCleaning = wantCleaning;
	}

	public void setWantFuel(boolean wantFuel) {
		this.wantFuel = wantFuel;
	}

	public void setWantFuelPumpNum(int wantFuelPumpNum) {
		WantFuelPumpNum = wantFuelPumpNum;
	}

	public void setWantFuelNumOfLiters(float wantFuelNumOfLiters) {
		WantFuelNumOfLiters = wantFuelNumOfLiters;
	}

	public void dispose() {
		logHandler.close();
	}

	public boolean isFromClient() {
		return isFromClient;
	}

	public void setFromClient(boolean isFromClient) {
		this.isFromClient = isFromClient;
	}

	// ------------------------------------------
	@AnnotLeisurable
	@Override
	public String readAnewsPaper() {
		for (int i = 0; i < 5; i++)
			Collections.shuffle(newsLines);
		return newsLines.get(0);
	}

	@AnnotLeisurable
	@Override
	public String playWithTheSmartPhone() {
		for (int i = 0; i < 5; i++)
			Collections.shuffle(games);
		return games.get(0);

	}

	@AnnotLeisurable
	@Override
	public String makeAcall() {
		for (int i = 0; i < 5; i++)
			Collections.shuffle(contactNames);
		return contactNames.get(0);
	}

	public CarStatus.carState getState() {
		return state;
	}

	public void setState(CarStatus.carState status) {
		this.state = status;
	}

	// ------------------------------------------

}//
