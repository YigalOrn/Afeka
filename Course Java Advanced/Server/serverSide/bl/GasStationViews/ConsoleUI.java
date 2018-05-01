package serverSide.bl.GasStationViews;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.Statistics;
import serverSide.bl.GasStationController.GasStationController;
import serverSide.bl.GasStationEvents.GasStationEventsListener;


public class ConsoleUI implements AbstractGasStationView {

	private static Scanner s = new Scanner(System.in);
	private  LinkedList<GasStationEventsListener> allListeners = new LinkedList<GasStationEventsListener>();
	@SuppressWarnings("unused")
	private  GasStationController gasControl;
	public  void showMenu() {
		String swValue;
		boolean exit = false;
		while (!exit) {
			// Display menu graphics
			System.out.println("===========================================================");
			System.out.println("|   Gas Station MENU                                      |");
			System.out.println("===========================================================");
			System.out.println("| Options:                                                |");
			System.out.println("|        1. Add car                                       |");
			System.out.println("|        2. add Fuel to MainFuelPool                      |");
			System.out.println("|        3. Show statistics                               |");
			System.out.println("|        4. Shutdown the GasStatopm and show statistics   |");
			System.out.println("|        5. Exit                                          |");
			System.out.println("===========================================================");
			swValue = s.next();
			// Switch construct
			switch (swValue) {
			case "1":
				addNewCar();
				break;
			case "2":
				fillMainFuelPool();
				break;
			case "3":
				showStatistics();
				break;
			case "4":
				CloseTheStation();
				showStatistics();
				exit=true;
				break;
			case "5":
				exit=true;
				break;
			default:
				System.out.println("Invalid selection");
				break; // This break is not really necessary
			}
		}
	}

	@Override
	public void registerListener(GasStationEventsListener uiEventListener) {
		allListeners.add(uiEventListener);

	}

	@Override
	public void getException(Exception e) {
		System.out.println("**********");
		System.out.println("Error-->"+e.getMessage());
		System.out.println("**********");
		
	}
	
	public void fillMainFuelPool(){
		try {
			System.out.println("Please enter the amout to fill");
			float amount =s.nextFloat();
			for (GasStationEventsListener lis:allListeners)
				lis.fillTheMainPumpModel(amount);
		} catch (Exception e) {
			getException(e);
		}
	}
	
	public void CloseTheStation(){
		for (GasStationEventsListener lis:allListeners)
			lis.closeTheDayModel();
	}
	
	public void addNewCar(){
		Car newCar;
		try {
			System.out.println("Please enter the Car id");
			int carId =s.nextInt();
			System.out.println("Tasks:0-Nothing,1-Fuel,2-Cleaning,3-Both");
			float task =s.nextInt();
			if(task<0 || task>3)
				throw new Exception("iligal number");
			
			if(task==2 || task==3)
				newCar = new Car(carId, true);
			else
				newCar = new Car(carId, false);
			
			if(task==1 || task==3)
			{
				System.out.println("Please enter Wanted amout of Fuel int Liters");
				float amount =s.nextFloat();
				newCar.setWantFuel(true);
				newCar.setWantFuelNumOfLiters(amount);
			}
			else
				newCar.setWantFuel(false);
			for (GasStationEventsListener lis:allListeners)
				lis.addcarModel(newCar);

		} catch (Exception e) {
			getException(e);
		}
		
	}
	
	public void showStatistics(){
		ArrayList<Statistics> statistics = new ArrayList<>();
		for (GasStationEventsListener lis:allListeners)
			statistics.add(lis.getStatistics());
		
		for (Statistics stat : statistics){
			System.out.println("********Fueling INFO************");
			System.out.println("Fueling Times: "+stat.getPumpFuelingTimes());
			System.out.println("Fueling Total Time: "+stat.getTotalPumpFuelngTime());
			System.out.println("Total Fuel Pumped: "+stat.getAmountFueled());
			System.out.println("********Main Fuel INFO**********");
			System.out.println("Fueling Times: "+stat.getMainFuelStockRefuelingTimes());
			System.out.println("Fueling Total Time: "+stat.getTotalMainFuelRefuelTime());
			System.out.println("Total Fuel Added: "+stat.getAmountMainFueled());
			System.out.println("********Cleaning INFO***********");
			System.out.println("Cleaning Times: "+stat.getCleanTimes());
			System.out.println("Clean Total Time: "+stat.getTotalCleanTime());
		}

	}
	
	
}
