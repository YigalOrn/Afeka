package serverSide.ui;

import java.io.IOException;
import java.util.List;

import serverSide.ControllersInitializer;
import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class MainPaneRunner extends Application {

	private ControllersInitializer controllersInitializer;
	private TabsPane tabsPane;
	private static final String[] STYLESHEETS = {

			"serverSide/ui/mainScreen/tabsPane/css/TabsPane.css",

			"serverSide/ui/mainScreen/tabs/menuTabPackage/css/MenuTab.css",
			"serverSide/ui/mainScreen/tabs/menuTabPackage/css/AddNewCarPane.css",
			"serverSide/ui/mainScreen/tabs/menuTabPackage/css/DisplayMenu.css",
			"serverSide/ui/mainScreen/tabs/menuTabPackage/css/StatisticsPane.css",
			"serverSide/ui/mainScreen/tabs/menuTabPackage/css/TankRefuel.css",

			"serverSide/ui/mainScreen/tabs/dbTabPackge/css/DbTab.css",
			"serverSide/ui/mainScreen/tabs/dbTabPackge/css/UIDateChosser.css",

			"serverSide/ui/mainScreen/tabs/communicationTabPackage/css/CommunicationTab.css",
			"serverSide/ui/mainScreen/tabs/communicationTabPackage/css/CommunicationTextArea.css",

			"serverSide/ui/mainScreen/tabs/carsStatusTabPackage/css/CarsStatusTab.css",
			"serverSide/ui/mainScreen/tabs/carsStatusTabPackage/css/DisplayCarUnit.css",
			"serverSide/ui/mainScreen/tabs/carsStatusTabPackage/css/DisplayPane.css",

	};

	public static void main(String[] args) {
		launch(args);
	}// main

	@Override
	public void start(Stage primaryStage) {

		setUserAgentStylesheet(STYLESHEET_CASPIAN);

		tabsPane = new TabsPane();

		try {
			controllersInitializer = new ControllersInitializer(tabsPane,
					primaryStage);
		} catch (IOException e) {
			e.printStackTrace();
		}

		Scene scene = new Scene(tabsPane, 900, 615);
		scene.getStylesheets().addAll(STYLESHEETS);

		primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
			@Override
			public void handle(WindowEvent event) {
				Thread closeGasStationThr = new Thread(new Runnable() {
					@Override
					public void run() {
						controllersInitializer.closeGasStation();
					}// run
				});
				closeGasStationThr.start();
			}
		});

		// -------------
		final Parameters params = getParameters();
		final List<String> args = params.getRaw();
		final String arg0 = !args.isEmpty() ? args.get(0) : "";
		// -------------

		primaryStage.setScene(scene);
		primaryStage.setTitle(arg0);
		primaryStage.setResizable(false);
		primaryStage.show();

	}// start

}// MainPane

