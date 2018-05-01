package serverSide.bl.GasStationViews;

import java.io.File;

import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationController.GasStationController;
import serverSide.bl.GasStationDAL.ObjectLoader;
import serverSide.bl.GasStationExceptions.InvalidPumpException;


public class Runner {

	public static void main(String[] args) throws InvalidPumpException {
		GasStation g = ObjectLoader.loadObject(new File("DOOM_fXML_3.XML")).get(0);
		
		g.activateHoldList();
		
		ConsoleUI ui = new ConsoleUI();
		@SuppressWarnings("unused")
		GasStationController gasControl = new GasStationController(ui, g);
		ui.showMenu();
		

	}

}
