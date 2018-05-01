package serverSide;

import java.io.File;
import java.io.IOException;

import javafx.application.Platform;
import javafx.stage.Stage;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationDAL.ObjectLoader;
import serverSide.bl.GasStationExceptions.MainFuelStockLowException;
import serverSide.controllers.blui.BLUIController;
import serverSide.controllers.serverbl.ServerBLController;
import serverSide.controllers.sqlbl.BLDALController;
import serverSide.server.QServer;
import serverSide.ui.ICloseStage;
import serverSide.ui.mainScreen.tabsPane.TabsPane;

@SuppressWarnings("unused")
public class ControllersInitializer implements ICloseStage {

	// ----
	private GasStation g;
	private static final float TANKALERTPERCENT = 20 / 100;
	private TabsPane tabsPane;
	private BLUIController controller1;
	// ----

	// ----
	private QServer qServer;
	private ServerBLController controller2;
	// ----

	private BLDALController controller3;

	private Stage primaryStage;

	/** C'tor */
	public ControllersInitializer(TabsPane tabsPane, final Stage primaryStage)
			throws IOException {
		this.tabsPane = tabsPane;
		this.primaryStage = primaryStage;
		init();
	}//

	/***/
	private void init() throws IOException {

		// ----------------------------------------------------------
		initGasStation();
		controller1 = new BLUIController(tabsPane, g);
		// ----------------------------------------------------------

		// ----------------------------------------------------------
		qServer = QServer.getInstance(65000);
		controller2 = new ServerBLController(qServer, g);
		// ----------------------------------------------------------

		// ----------------------------------------------------------
		controller3 = new BLDALController(g);
		// ----------------------------------------------------------

		Thread activateXMLCarsThr = new Thread(new Runnable() {
			@Override
			public void run() {
				try {

					// Check fuel level on startup
					double n1 = g.getMainFuelPool().getfuelAmount();
					float n2 = g.getMainFuelPool().getMaxCapacity();

					if (n1 < (n2 * TANKALERTPERCENT)) {
						g.throwException(new MainFuelStockLowException(
								(float) n1));
					}// if

					Thread.sleep(6000);
					g.activateHoldList();

				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		activateXMLCarsThr.start();

	}

	private void initGasStation() {
		// Application.this.getParameters() // for main args
		// g = ObjectLoader.loadObject(new File("fXML_1.XML")).get(0);
		// g = ObjectLoader.loadObject(new File("fXML_2.XML")).get(0);
		g = ObjectLoader.loadObject(new File("DOOM_fXML_3.XML")).get(0);
		g.setWindowCloser(this);

	}//

	// ---------------

	public GasStation getGasStation() {
		return g;
	}

	public void closeGasStation() {
		g.closeStation();
	}

	@Override
	public void closeStage() {
		Thread thrCloseStage = new Thread(new Runnable() {
			@Override
			public void run() {
				/*
				 * http://stackoverflow.com/questions/10212366/javafx-2-0-closing
				 * -a-stage-window
				 */
				Platform.setImplicitExit(true);
				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						primaryStage.close();
					}
				});

			}// run
		});
		thrCloseStage.start();
	}

}//
