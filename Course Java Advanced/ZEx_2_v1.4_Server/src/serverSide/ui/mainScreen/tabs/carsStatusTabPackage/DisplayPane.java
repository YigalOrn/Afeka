package serverSide.ui.mainScreen.tabs.carsStatusTabPackage;

import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.ScrollPane.ScrollBarPolicy;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class DisplayPane extends Pane {

	/** Data fields */
	private HBox hBrefuelQueuesView;
	private HBox hBrefuelsView;
	private HBox hBcleaningQueueView;
	private HBox hBautoWashView;
	private HBox hBmanualWashView;

	private HBox trash = new HBox();
	private int ctr = 0;

	private ScrollPane spRefuelQueuesView;
	private ScrollPane spRefuelsView;
	private ScrollPane spCleaningQueueView;
	private ScrollPane spAutoWashView;
	private ScrollPane spManualWashView;

	private Label lBtitle1;
	private Label lBtitle2;
	private Label lBtitle3;
	private Label lBtitle4;
	private Label lBtitle5;

	/** C'tor */
	public DisplayPane() {
		initComponents();
	}// c'tor

	private void initComponents() {

		setId("dispPaneStyle");

		// ----
		lBtitle1 = new Label("Cleaning queue -");
		lBtitle1.setPrefSize(130, 64);
		lBtitle1.setTextFill(Color.web("#FF3300"));
		lBtitle1.setFont(Font.font("David", FontWeight.BOLD, 17));

		lBtitle2 = new Label("Fueling queue -");
		lBtitle2.setPrefSize(130, 64);
		lBtitle2.setTextFill(Color.web("#FF3300"));
		lBtitle2.setFont(Font.font("David", FontWeight.BOLD, 17));

		lBtitle3 = new Label("Pumps -");
		lBtitle3.setPrefSize(130, 64);
		lBtitle3.setTextFill(Color.web("#FF3300"));
		lBtitle3.setFont(Font.font("David", FontWeight.BOLD, 17));

		lBtitle4 = new Label("AutoWash -");
		lBtitle4.setPrefSize(130, 64);
		lBtitle4.setTextFill(Color.web("#FF3300"));
		lBtitle4.setFont(Font.font("David", FontWeight.BOLD, 17));

		lBtitle5 = new Label("Manual clean -");
		lBtitle5.setPrefSize(130, 64);
		lBtitle5.setTextFill(Color.web("#FF3300"));
		lBtitle5.setFont(Font.font("David", FontWeight.BOLD, 17));
		// ----

		// ----
		hBrefuelQueuesView = new HBox();
		hBrefuelQueuesView.setSpacing(20);
		hBrefuelQueuesView.setPadding(new Insets(6, 20, 30, 20));
		hBrefuelQueuesView.getChildren().add(lBtitle2);

		hBrefuelsView = new HBox();
		hBrefuelsView.setSpacing(20);
		hBrefuelsView.setPadding(new Insets(6, 20, 30, 20));
		hBrefuelsView.getChildren().add(lBtitle3);

		hBcleaningQueueView = new HBox();
		hBcleaningQueueView.setSpacing(20);
		hBcleaningQueueView.setPadding(new Insets(6, 20, 30, 20));
		hBcleaningQueueView.getChildren().add(lBtitle1);

		hBautoWashView = new HBox();
		hBautoWashView.setSpacing(20);
		hBautoWashView.setPadding(new Insets(6, 20, 30, 20));
		hBautoWashView.getChildren().add(lBtitle4);

		hBmanualWashView = new HBox();
		hBmanualWashView.setSpacing(20);
		hBmanualWashView.setPadding(new Insets(6, 20, 30, 20));
		hBmanualWashView.getChildren().add(lBtitle5);
		// ----

		// ----
		spRefuelQueuesView = new ScrollPane(hBrefuelQueuesView);
		spRefuelQueuesView.setPrefSize(890, 85);
		spRefuelQueuesView.setVbarPolicy(ScrollBarPolicy.NEVER);
		spRefuelQueuesView.setHbarPolicy(ScrollBarPolicy.AS_NEEDED);
		spRefuelQueuesView.setLayoutX(5);
		spRefuelQueuesView.setLayoutY(7);
		spRefuelQueuesView.setStyle("-fx-background-color:transparent;");

		spRefuelsView = new ScrollPane(hBrefuelsView);
		spRefuelsView.setPrefSize(890, 85);
		spRefuelsView.setVbarPolicy(ScrollBarPolicy.NEVER);
		spRefuelsView.setHbarPolicy(ScrollBarPolicy.AS_NEEDED);
		spRefuelsView.setLayoutX(5);
		spRefuelsView.setLayoutY(125);
		spRefuelsView.setStyle("-fx-background-color:transparent;");

		spCleaningQueueView = new ScrollPane(hBcleaningQueueView);
		spCleaningQueueView.setPrefSize(890, 85);
		spCleaningQueueView.setVbarPolicy(ScrollBarPolicy.NEVER);
		spCleaningQueueView.setHbarPolicy(ScrollBarPolicy.AS_NEEDED);
		spCleaningQueueView.setLayoutX(5);
		spCleaningQueueView.setLayoutY(245);
		spCleaningQueueView
				.setStyle("-fx-border-color: #B4155D;\n -fx-border-style: dashed;");

		spAutoWashView = new ScrollPane(hBautoWashView);
		spAutoWashView.setPrefSize(890, 85);
		spAutoWashView.setVbarPolicy(ScrollBarPolicy.NEVER);
		spAutoWashView.setHbarPolicy(ScrollBarPolicy.AS_NEEDED);
		spAutoWashView.setLayoutX(5);
		spAutoWashView.setLayoutY(370);
		spAutoWashView.setStyle("-fx-background-color:transparent;");

		spManualWashView = new ScrollPane(hBmanualWashView);
		spManualWashView.setPrefSize(890, 85);
		spManualWashView.setVbarPolicy(ScrollBarPolicy.NEVER);
		spManualWashView.setHbarPolicy(ScrollBarPolicy.AS_NEEDED);
		spManualWashView.setLayoutX(5);
		spManualWashView.setLayoutY(485);
		spManualWashView.setStyle("-fx-background-color:transparent;");

		// ----

		this.getChildren().addAll(spRefuelQueuesView, spRefuelsView,
				spCleaningQueueView, spAutoWashView, spManualWashView);

	}

	public void handleCarDisplay(CarStatus.carState newState,
			DisplayCarUnit disp) {

		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		switch (newState) {
		case AUTOWASH:
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					hBautoWashView.getChildren().add(disp);
				}
			});
			break;
		case CLEANQUEUE:
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					hBcleaningQueueView.getChildren().add(disp);
				}
			});
			break;
		case REFUELING:
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					hBrefuelsView.getChildren().add(disp);
				}
			});
			break;
		case FUELQUEUE:
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					hBrefuelQueuesView.getChildren().add(disp);
				}
			});
			break;
		case MANUALWASH:
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					hBmanualWashView.getChildren().add(disp);
				}
			});
			break;
		case DONE:
		case TEXTONLY:
			removeFromDispalyByState(disp);
			break;

		}// switch

		disp.setCurrentState(newState);
	}

	private void removeFromDispalyByState(DisplayCarUnit disp) {
		Platform.runLater(new Runnable() {
			@Override
			public void run() {
				trash.getChildren().add(disp);
				ctr = (ctr + 1) % 11;
				if (ctr == 10) {
					trash.getChildren().clear();
				}
			}
		});
	}//

}//
