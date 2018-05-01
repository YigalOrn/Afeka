package serverSide.ui.mainScreen.tabs.menuTabPackage;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import serverSide.bl.GasStationBL.Statistics;

import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.PieChart;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Pagination;
import javafx.scene.control.TextArea;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class StatisticsPane extends Pane {

	/** Data fields */

	private TabsPane tabPane;

	/*
	 * http://docs.oracle.com/javase/8/javafx/user-interface-tutorial/charts.htm#
	 * JFXUI577
	 */
	private BarChart<String, Number> fuelBc;
	private BarChart<String, Number> pumpsBc;
	private BarChart<String, Number> cleaningBc;

	private PieChart pieChart;

	private TextArea textArea;

	private LocalDateTime ldt = LocalDateTime.now();
	private DateTimeFormatter dtf = DateTimeFormatter
			.ofPattern("dd/MM/yyyy\n  HH:mm:ss");// Set pattern
	/*
	 * 
	 * A nice component to view the charts i.e holds and displays the charts in
	 * numbered pages with a control to switch between them.
	 */
	private Pagination pagination;
	private Button btnRefresh;

	/** C'tor */
	public StatisticsPane(TabsPane tabPane) {
		registerListener(tabPane);
		initTextArea();
		initBarChart();
		initPieChart();
		initPagination();
		getChildren().add(pagination);
	}// c'tor

	/** Class methods */

	private void initPagination() {

		btnRefresh = new Button();
		btnRefresh.setGraphic(new ImageView(new Image(StatisticsPane.class
				.getResourceAsStream("statisticsPaneIcons/1.png"))));

		btnRefresh.setStyle("-fx-background-color:transparent;");

		DropShadow shadow = new DropShadow();
		// Adding the shadow when the mouse cursor is on
		btnRefresh.addEventHandler(MouseEvent.MOUSE_ENTERED,
				(MouseEvent e) -> {
					btnRefresh.setEffect(shadow);
				});

		// Removing the shadow when the mouse cursor is off
		btnRefresh.addEventHandler(MouseEvent.MOUSE_EXITED, (MouseEvent e) -> {
			btnRefresh.setEffect(null);
		});

		btnRefresh.setOnAction(new EventHandler<ActionEvent>() {

			@Override
			public void handle(ActionEvent e) {
				refreshStatistics();
			}
		});

		pagination = new Pagination(5, 0);
		/*
		 * The pagination page creation requires to implement a functional
		 * interface Callback<Integer, Node>, doing so allows to use the Lambda
		 * syntax. Integer - the page index : 0, 1 ... Node - any appropriate
		 * graphical component to be displayed!
		 */
		pagination
				.setPageFactory((Integer pageIndex) -> createPaginationPage(pageIndex));
		pagination.setPrefSize(855, 460);
		pagination
				.setStyle("-fx-border-color: #B4155D;\n -fx-border-style: dashed;");
		pagination.getStyleClass().add(Pagination.STYLE_CLASS_BULLET);
	}//

	private void initTextArea() {
		textArea = new TextArea();
		textArea.setFont(Font.font("Consolas", FontWeight.BOLD, 15));
		textArea.setEditable(false);
		textArea.setWrapText(true);
	}

	private void initPieChart() {
		pieChart = new PieChart();
		pieChart.setTitle("Statistics segmentation");
	}

	private void initBarChart() {
		// Setting the axis titles
		CategoryAxis xAxisPumpsBc = new CategoryAxis();
		NumberAxis yAxisPumpsBc = new NumberAxis();

		xAxisPumpsBc.setLabel("Source");
		yAxisPumpsBc.setLabel("Amount");

		CategoryAxis xAxisfuelBc = new CategoryAxis();
		NumberAxis yAxisfuelBc = new NumberAxis();

		xAxisfuelBc.setLabel("Source");
		yAxisfuelBc.setLabel("Amount");

		CategoryAxis xAxiscleaningBc = new CategoryAxis();
		NumberAxis yAxiscleaningBc = new NumberAxis();

		xAxiscleaningBc.setLabel("Source");
		yAxiscleaningBc.setLabel("Amount");
		// ------------

		// Setting the Bar charts scheme
		fuelBc = new BarChart<>(xAxisfuelBc, yAxisfuelBc);
		fuelBc.setTitle("Fueling Statistics");
		fuelBc.setBarGap(-6);
		fuelBc.setCategoryGap(23);

		pumpsBc = new BarChart<>(xAxisPumpsBc, yAxisPumpsBc);
		pumpsBc.setTitle("Pumps Statistics");
		pumpsBc.setBarGap(-6);
		pumpsBc.setCategoryGap(23);

		cleaningBc = new BarChart<>(xAxiscleaningBc, yAxiscleaningBc);
		cleaningBc.setTitle("Cleaning servise Statistics");
		cleaningBc.setBarGap(-6);
		cleaningBc.setCategoryGap(23);
		// ------------
	}

	private void setPieChart(Statistics statistics) {

		pieChart.getData().clear();

		ObservableList<PieChart.Data> pieChartDataColl = FXCollections
				.observableArrayList(new PieChart.Data("PumpsProfit",
						statistics.getTotalPumpsProfit()), new PieChart.Data(
						"CleaningProfit", statistics.getCleaningProfit()));

		pieChart.setData(pieChartDataColl);
	}//

	private void setBarChart(Statistics statistics) {

		// Setting the Bar charts data "structure", no data is included here!
		XYChart.Series pumpsBcSeries = new XYChart.Series();
		// pumpsBcSeries.setName(ldt.format(dtf));
		pumpsBcSeries.setName(ldt.format(dtf));

		XYChart.Series fuelBcSeries = new XYChart.Series();
		fuelBcSeries.setName(ldt.format(dtf));

		XYChart.Series cleaningBcSeries = new XYChart.Series();
		cleaningBcSeries.setName(ldt.format(dtf));
		// ------------

		// Clear BarCharts GUI
		pumpsBc.getData().clear();
		fuelBc.getData().clear();
		cleaningBc.getData().clear();
		// ------------

		// Set new data to pumpsBc
		for (int i = 0; i < statistics.getPumpsFuel().length; i++) {
			pumpsBcSeries.getData().add(
					new XYChart.Data("Pump " + i, statistics.getPumpProfit(i)));
		}
		// ------------

		// Set new data to fuelBc

		fuelBcSeries.getData().add(
				new XYChart.Data("amountFueled", statistics.getAmountFueled()));

		fuelBcSeries.getData().add(
				new XYChart.Data("fuelingTimes", statistics
						.getPumpFuelingTimes()));
		// ------------

		// Set new data to cleaningBc
		cleaningBcSeries.getData().add(
				new XYChart.Data("CleanTimes", statistics.getCleanTimes()));

		cleaningBcSeries.getData()
				.add(new XYChart.Data("CleanProfit", statistics
						.getCleaningProfit()));
		// ------------

		// Add the new data to the Bars GUI
		pumpsBc.getData().add(pumpsBcSeries);
		fuelBc.getData().add(fuelBcSeries);
		cleaningBc.getData().add(cleaningBcSeries);
		// ------------

	}//

	private void setTextArea(Statistics statistics) {

		StringBuilder sb = new StringBuilder();

		/*
		 * Use StringFormat
		 */

		sb.append("currentTankLevel - " + statistics.getCurrentCapacity()
				+ "\n" + "mainFuelStockRefuelingTimes - "
				+ statistics.getMainFuelStockRefuelingTimes() + "\n"
				+ "TotalMainFuelRefuelTime - "
				+ statistics.getTotalMainFuelRefuelTime() + "\n"
				+ "amountMainFueled - " + statistics.getAmountMainFueled()
				+ "\n" + "TotalPumpFuelngTime - "
				+ statistics.getTotalPumpFuelngTime() + "\n" + "CleanTimes - "
				+ statistics.getCleanTimes() + "\n" + "TotalCleanTime - "
				+ statistics.getTotalCleanTime() + "\n" + "cleaningProfit - "
				+ statistics.getCleaningProfit() + "\n" + "amountFueled - "
				+ statistics.getAmountFueled() + "\n" + "pumpFuelingTimes - "
				+ statistics.getPumpFuelingTimes() + "\n");

		for (int i = 0; i < statistics.getPumpsFuel().length; i++) {
			sb.append("Pump " + i + " - " + statistics.getPumpProfit(i) + "\n");
		}

		textArea.setText(sb.toString());

	}

	/**
	 * This method creates the contents to display in each page in the
	 * pagination
	 */
	private GridPane createPaginationPage(int pageIndex) {

		GridPane gridPane = new GridPane();

		switch (pageIndex) {

		case 0:
			gridPane.setVgap(10);
			gridPane.setHgap(10);
			gridPane.setPadding(new Insets(25, 25, 25, 165));
			gridPane.add(fuelBc, 0, 0, 10, 10);
			gridPane.add(btnRefresh, 0, 11);
			break;
		case 1:
			gridPane.setVgap(10);
			gridPane.setHgap(10);
			gridPane.setPadding(new Insets(25, 25, 25, 165));
			gridPane.add(pumpsBc, 0, 0, 10, 10);
			gridPane.add(btnRefresh, 0, 11);
			break;
		case 2:
			gridPane.setVgap(10);
			gridPane.setHgap(10);
			gridPane.setPadding(new Insets(25, 25, 25, 165));
			gridPane.add(cleaningBc, 0, 0, 10, 10);
			gridPane.add(btnRefresh, 0, 11);
			break;
		case 3:
			gridPane.setVgap(10);
			gridPane.setHgap(10);
			// gridPane.setGridLinesVisible(true);
			gridPane.setPadding(new Insets(25, 25, 25, 165));
			gridPane.add(pieChart, 0, 0, 10, 10);
			gridPane.add(btnRefresh, 0, 11);
			break;
		case 4:
			gridPane.setVgap(10);
			gridPane.setHgap(10);
			// gridPane.setGridLinesVisible(true);
			gridPane.setPadding(new Insets(25, 25, 25, 165));
			gridPane.add(textArea, 0, 0, 40, 28);
			gridPane.add(btnRefresh, 0, 29);
			break;
		}// switch

		return gridPane;
	}//

	/** 
	 * 
	 * */
	public void refreshStatistics() {
		btnRefresh.setDisable(true);
		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				Statistics statistics = fireGetStatistics();
				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						setBarChart(statistics);
						setPieChart(statistics);
						setTextArea(statistics);
						btnRefresh.setDisable(false);
					}
				});
			}
		});
		taskThr.start();
	}//

	// --------------------------------------------
	public void registerListener(TabsPane tabPane) {
		this.tabPane = tabPane;
	}

	private Statistics fireGetStatistics() {
		return tabPane.getStatistics();
	}
	// --------------------------------------------

}//
