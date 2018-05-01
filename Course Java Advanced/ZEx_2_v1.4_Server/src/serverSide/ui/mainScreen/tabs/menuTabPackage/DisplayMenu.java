/*
 * 
 * https://docs.oracle.com/javafx/2/visual_effects/bloom.htm
 * 
 * https://community.oracle.com/thread/2488355
 * 
 * */

package serverSide.ui.mainScreen.tabs.menuTabPackage;

import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.animation.Animation;
import javafx.animation.FadeTransition;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Separator;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.util.Duration;

public class DisplayMenu extends Pane {

	/** Data fields */

	private final int SIZE = 3;
	private Pane[] displayPanes = new Pane[SIZE];

	private HBox hBox;
	private Button btnReFuel;
	private FadeTransition ft;

	private Button btnAddCar;
	private Button btnShowStatstics;
	private Button btnCloseGasStation;

	private Separator separator;
	private Separator separator2;

	private TabsPane tabPane;

	/** C'tor */
	public DisplayMenu(TabsPane tabPane) {

		this.tabPane = tabPane;

		init();
		initDisplays();
		getChildren().add(hBox);
		getChildren().addAll(separator, separator2);

		
		String image = DisplayMenu.class.getResource("background/3.jpg")
				.toExternalForm();
		setStyle("-fx-background-image: url('" + image + "'); "
				+ "-fx-background-size: 900 615;");

	}// c'tor

	/** Class methods */

	private void initDisplays() {

		// from left to right
		displayPanes[0] = new AddNewCarPane(tabPane);
		displayPanes[1] = new TankRefuel(tabPane);
		displayPanes[2] = new StatisticsPane(tabPane);

		for (int i = 0; i < displayPanes.length; i++) {
			if (displayPanes[i] != null) {
				DisplayMenu.this.getChildren().add(displayPanes[i]);
				displayPanes[i].setVisible(false);
			}// if

		}// for

	}//

	private void init() {

		DropShadow shadow = new DropShadow();

		btnReFuel = new Button();
		btnReFuel.setOnAction(new ButtonAction("btnReFuel"));
		btnReFuel.setGraphic(new ImageView(new Image(DisplayMenu.class
				.getResourceAsStream("MenuBtnIcons/2.png"))));
		btnReFuel.setStyle("-fx-background-color:transparent;");
		btnReFuel.setStyle("-fx-background-color:transparent;");
		// Adding the shadow when the mouse cursor is on
		btnReFuel.addEventHandler(MouseEvent.MOUSE_ENTERED, (MouseEvent e) -> {
			btnReFuel.setEffect(shadow);
		});
		// Removing the shadow when the mouse cursor is off
		btnReFuel.addEventHandler(MouseEvent.MOUSE_EXITED, (MouseEvent e) -> {
			btnReFuel.setEffect(null);
		});

		// Animation for when tank refuel is needed
		ft = new FadeTransition(Duration.millis(500), btnReFuel);
		ft.setFromValue(1.0);
		ft.setToValue(0.3);
		ft.setCycleCount(Animation.INDEFINITE);
		ft.setAutoReverse(true);

		btnAddCar = new Button();
		btnAddCar.setOnAction(new ButtonAction("btnAddCar"));
		btnAddCar.setGraphic(new ImageView(new Image(DisplayMenu.class
				.getResourceAsStream("MenuBtnIcons/4.png"))));
		btnAddCar.setStyle("-fx-background-color:transparent;");
		btnAddCar.setStyle("-fx-background-color:transparent;");
		// Adding the shadow when the mouse cursor is on
		btnAddCar.addEventHandler(MouseEvent.MOUSE_ENTERED, (MouseEvent e) -> {
			btnAddCar.setEffect(shadow);
		});

		// Removing the shadow when the mouse cursor is off
		btnAddCar.addEventHandler(MouseEvent.MOUSE_EXITED, (MouseEvent e) -> {
			btnAddCar.setEffect(null);
		});

		btnShowStatstics = new Button();
		btnShowStatstics.setOnAction(new ButtonAction("btnShowStatstics"));
		btnShowStatstics.setGraphic(new ImageView(new Image(DisplayMenu.class
				.getResourceAsStream("MenuBtnIcons/5.png"))));
		btnShowStatstics.setStyle("-fx-background-color:transparent;");
		btnShowStatstics.setStyle("-fx-background-color:transparent;");
		// Adding the shadow when the mouse cursor is on
		btnShowStatstics.addEventHandler(MouseEvent.MOUSE_ENTERED,
				(MouseEvent e) -> {
					btnShowStatstics.setEffect(shadow);
				});

		// Removing the shadow when the mouse cursor is off
		btnShowStatstics.addEventHandler(MouseEvent.MOUSE_EXITED,
				(MouseEvent e) -> {
					btnShowStatstics.setEffect(null);
				});

		btnCloseGasStation = new Button();
		btnCloseGasStation.setOnAction(new ButtonAction("btnCloseGasStation"));
		btnCloseGasStation.setGraphic(new ImageView(new Image(DisplayMenu.class
				.getResourceAsStream("MenuBtnIcons/1.png"))));
		btnCloseGasStation.setStyle("-fx-background-color:transparent;");
		// Adding the shadow when the mouse cursor is on
		btnCloseGasStation.addEventHandler(MouseEvent.MOUSE_ENTERED, (
				MouseEvent e) -> {
			btnCloseGasStation.setEffect(shadow);
		});

		// Removing the shadow when the mouse cursor is off
		btnCloseGasStation.addEventHandler(MouseEvent.MOUSE_EXITED, (
				MouseEvent e) -> {
			btnCloseGasStation.setEffect(null);
		});

		separator = new Separator();
		separator.setPrefSize(707, 0);
		separator.setStyle("-fx-background-color:#CD3700;");

		separator2 = new Separator();
		separator2.setPrefSize(800, 0);
		separator2.setStyle("-fx-background-color:#CD3700;");

		hBox = new HBox();
		hBox.setSpacing(15);

		hBox.getChildren().addAll(btnAddCar, btnReFuel, btnShowStatstics,
				btnCloseGasStation);

		hBox.setLayoutX(250);
		hBox.setLayoutY(25);

		separator.setLayoutX(100);
		separator.setLayoutY(100);

		separator2.setLayoutX(55);
		separator2.setLayoutY(107);

	}//

	private class ButtonAction implements EventHandler<ActionEvent> {

		private String btnName;

		public ButtonAction(String btnName) {
			this.btnName = btnName;
		}

		@Override
		public void handle(ActionEvent event) {

			setStyle("");//clear intro background

			for (int i = 0; i < displayPanes.length; i++) {
				if (displayPanes[i] != null)
					displayPanes[i].setVisible(false);
			}

			switch (btnName) {

			case "btnReFuel":

				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						displayPanes[1].setVisible(true);
						displayPanes[1].setLayoutY(75);
						displayPanes[1].setLayoutX(27);
						/*
						 * Run through menu button!
						 */
						ft.stop();

						btnReFuel.setOpacity(1.0);

						((TankRefuel) displayPanes[1]).activate();
						resetMenuButtons();
						((Button) event.getSource()).setDisable(true);
					}
				});

				break;
			case "btnAddCar":
				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						displayPanes[0].setVisible(true);
						displayPanes[0].setLayoutY(110);
						displayPanes[0].setLayoutX(27);
						resetMenuButtons();
						((Button) event.getSource()).setDisable(true);
					}
				});
				break;
			case "btnShowStatstics":
				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						((StatisticsPane) displayPanes[2]).refreshStatistics();
						displayPanes[2].setVisible(true);
						displayPanes[2].setLayoutY(113);
						displayPanes[2].setLayoutX(27);
						resetMenuButtons();
						((Button) event.getSource()).setDisable(true);
					}// run
				});
				break;
			case "btnCloseGasStation":

				Thread closeTask = new Thread(new Runnable() {
					@Override
					public void run() {
						tabPane.requestGasStationClosing();
					}
				});
				closeTask.start();

				resetMenuButtons();
				((Button) event.getSource()).setDisable(true);
				break;
			}// switch

		}

	}//

	private void resetMenuButtons() {
		btnAddCar.setDisable(false);
		btnCloseGasStation.setDisable(false);
		btnReFuel.setDisable(false);
		btnShowStatstics.setDisable(false);
	}//

	public void createAlertAffectOnbtnReFuel() {

		/*
		 * F2:
		 * 
		 * ...If the Animation is running, it has no effect...
		 * 
		 * same for stop()
		 */
		ft.play();
	}

}// TopButtonMenu

