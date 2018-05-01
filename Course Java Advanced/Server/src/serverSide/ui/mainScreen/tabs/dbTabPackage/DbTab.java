/*
 * 
 * https://docs.oracle.com/javafx/2/ui_controls/accordion-titledpane.htm
 * https://docs.oracle.com/javase/8/javafx/api/javafx/scene/control/Spinner.html
 * import javafx.scene.control.Spinner;
 * 
 * https://docs.oracle.com/javafx/2/ui_controls/accordion-titledpane.htm
 * 
 * */

package serverSide.ui.mainScreen.tabs.dbTabPackage;

import java.util.HashMap;

import serverSide.ui.mainScreen.tabs.dbTabPackage.tableViews.TableCleaning;
import serverSide.ui.mainScreen.tabs.dbTabPackage.tableViews.TablePump;
import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.geometry.Orientation;
import javafx.scene.control.Accordion;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.Separator;
import javafx.scene.control.Tab;
import javafx.scene.control.TextField;
import javafx.scene.control.TitledPane;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;

public class DbTab extends Tab {

	/** Data Fields */

	/*
	 * Will hold DisplayTable instances.
	 */
	private Accordion accordionPane;
	private TablePump tbPump;
	private TableCleaning tbCleaning;
	private ProfitTitledPane profitsTitledPane;

	private AnchorPane anchorPane;

	/*
	 * Oracle: JavaFX DatePicker is a control that enables selection of a day
	 * from the given calendar. It is used mainly on web sites or in
	 * applications that require users to enter a date. The DatePicker control
	 * consists of a combo box with a date field and a date chooser.
	 * 
	 * http://docs.oracle.com/javase/8/javafx/user-interface-tutorial/date-picker
	 * .htm#CCHHJBEA
	 */
	private UIDateChooser pumpDatePickerFrom;
	private UIDateChooser pumpDatePickerTo;

	private UIDateChooser cleanDatePickerFrom;
	private UIDateChooser cleanDatePickerTo;

	private Label lbPumpDatePicker;
	private Label lbPumpEnterTime;

	private Label lbCleanDatePicker;
	private Label lbCleanEnterTime;

	private TextField tfPumpEnterTimeFrom;
	private TextField tfPumpEnterTimeTo;

	private TextField tfCleanEnterTimeFrom;
	private TextField tfCleanEnterTimeTo;

	private Label lbFuelService;
	private Label lbCleaningService;

	private ComboBox<String> cmbPumpsNum;
	private Label lbChoosePump;

	private Button btnFuelSubmit;
	private Button btnFuelClear;

	private Button btnCleaningSubmit;
	private Button btnCleaningClear;

	private Separator spViews;
	private Separator spMenu;

	private Separator spPumpTitlelb;
	private Separator spCleanTitlelb;

	private TabsPane tabPane;

	/** C'tor */
	public DbTab(String tabTilte, TabsPane tabPane) {
		super(tabTilte);
		registerListener(tabPane);
		setClosable(false);

		anchorPane = new AnchorPane();

		initComponents();
		initLayout();

		setContent(anchorPane);

	}// c'tor

	/** Class methods */

	private void initComponents() {

		accordionPane = new Accordion();
		accordionPane.expandedPaneProperty().addListener(
				new ChangeListener<TitledPane>() {
					@Override
					public void changed(
							ObservableValue<? extends TitledPane> arg0,
							TitledPane oldVal, TitledPane newVal) {

						if (accordionPane.getExpandedPane() instanceof ProfitTitledPane) {
							handleTotProfitSubmission();
						}
					}
				});

		// TitledPanes
		tbCleaning = new TableCleaning();
		tbPump = new TablePump();
		profitsTitledPane = new ProfitTitledPane();

		// Menus

		pumpDatePickerFrom = new UIDateChooser();
		pumpDatePickerTo = new UIDateChooser();

		lbPumpDatePicker = new Label("Enter date interval : ");

		lbPumpEnterTime = new Label("Enter time interval :");

		// ------------
		tfPumpEnterTimeFrom = new TextField() {

			@Override
			public void replaceText(int start, int end, String text) {

				/*
				 * 
				 * Make the wanted pattern!! Using regular expressions.
				 * 
				 * Deitel 9th edition: page 736.
				 */

				if (!text.matches("[a-z, A-Z]")) {
					super.replaceText(start, end, text);

				} else {

				}
			}

			@Override
			public void replaceSelection(String text) {
				if (!text.matches("[a-z, A-Z]")) {
					super.replaceSelection(text);

				} else {

				}
			}
		};
		tfPumpEnterTimeFrom.setPromptText("Pattern HH:mm:ss");

		tfPumpEnterTimeTo = new TextField() {

			@Override
			public void replaceText(int start, int end, String text) {

				/*
				 * 
				 * Make the wanted pattern!! Using regular expressions.
				 * 
				 * Deitel 9th edition: page 736.
				 */

				if (!text.matches("[a-z, A-Z]")) {
					super.replaceText(start, end, text);

				} else {

				}
			}

			@Override
			public void replaceSelection(String text) {
				if (!text.matches("[a-z, A-Z]")) {
					super.replaceSelection(text);

				} else {

				}
			}
		};
		tfPumpEnterTimeTo.setPromptText("Pattern HH:mm:ss");

		tfPumpEnterTimeFrom.setPrefWidth(110);
		tfPumpEnterTimeTo.setPrefWidth(110);

		// ------------

		lbFuelService = new Label("Fuel Service");
		lbCleaningService = new Label("Cleaning Service");

		cmbPumpsNum = new ComboBox<>();
		cmbPumpsNum.setVisibleRowCount(5);
		cmbPumpsNum.setPrefWidth(140);

		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						int n = fireReqeustPumpNum();
						for (int i = 0; i < n; i++) {
							cmbPumpsNum.getItems().add("Pump " + i);
						}
						cmbPumpsNum.getSelectionModel().clearSelection();
					}// run
				});
			}
		});
		taskThr.start();

		lbChoosePump = new Label("Choose pump num : ");

		btnFuelSubmit = new Button("submit sql query");
		btnFuelSubmit.addEventHandler(MouseEvent.MOUSE_CLICKED,
				new EventHandler<MouseEvent>() {

					@Override
					public void handle(MouseEvent event) {
						handleFuelFormSubmission();
					}

				});

		btnFuelClear = new Button("reset form");
		btnFuelClear.addEventHandler(MouseEvent.MOUSE_CLICKED,
				new EventHandler<MouseEvent>() {

					@Override
					public void handle(MouseEvent event) {
						resetFuelComponents();
					}
				});

		btnCleaningSubmit = new Button("submit sql query");
		btnCleaningSubmit.addEventHandler(MouseEvent.MOUSE_CLICKED,
				new EventHandler<MouseEvent>() {

					@Override
					public void handle(MouseEvent event) {
						handleCleaningFormSubmission();
					}

				});

		btnCleaningClear = new Button("reset form");
		btnCleaningClear.addEventHandler(MouseEvent.MOUSE_CLICKED,
				new EventHandler<MouseEvent>() {

					@Override
					public void handle(MouseEvent event) {
						resetCleaningComponents();
					}
				});

		spViews = new Separator(Orientation.VERTICAL);
		spViews.setPrefSize(2, 530);

		spPumpTitlelb = new Separator();
		spPumpTitlelb.setPrefSize(140, 5);

		spCleanTitlelb = new Separator();
		spCleanTitlelb.setPrefSize(140, 5);

		spMenu = new Separator();
		spMenu.setPrefSize(275, 5);

		cleanDatePickerFrom = new UIDateChooser();
		cleanDatePickerTo = new UIDateChooser();
		lbCleanDatePicker = new Label("Enter date interval : ");

		lbCleanEnterTime = new Label("Enter time interval :");
		// ------------
		tfCleanEnterTimeFrom = new TextField() {

			@Override
			public void replaceText(int start, int end, String text) {

				/*
				 * 
				 * Make the wanted pattern!! Using regular expressions.
				 * 
				 * Deitel 9th edition: page 736.
				 */

				if (!text.matches("[a-z, A-Z]")) {
					super.replaceText(start, end, text);

				} else {

				}
			}

			@Override
			public void replaceSelection(String text) {
				if (!text.matches("[a-z, A-Z]")) {
					super.replaceSelection(text);

				} else {

				}
			}
		};
		tfCleanEnterTimeFrom.setPromptText("Pattern HH:mm:ss");

		tfCleanEnterTimeTo = new TextField() {

			@Override
			public void replaceText(int start, int end, String text) {

				/*
				 * 
				 * Make the wanted pattern!! Using regular expressions.
				 * 
				 * Deitel 9th edition: page 736.
				 */

				if (!text.matches("[a-z, A-Z]")) {
					super.replaceText(start, end, text);

				} else {

				}
			}

			@Override
			public void replaceSelection(String text) {
				if (!text.matches("[a-z, A-Z]")) {
					super.replaceSelection(text);

				} else {

				}
			}
		};
		tfCleanEnterTimeTo.setPromptText("Pattern HH:mm:ss");

		tfCleanEnterTimeFrom.setPrefWidth(110);
		tfCleanEnterTimeTo.setPrefWidth(110);

		// ------------

		/*
		 * 
		 * Set mnemonics:
		 * 
		 * http://stackoverflow.com/questions/12710468/using-javafx-2-2-mnemonic
		 */

	}//

	private void initLayout() {

		// -------
		accordionPane.setPrefSize(610, 500);
		accordionPane.getPanes().addAll(tbPump, tbCleaning, profitsTitledPane);
		// accordion.setExpandedPane();
		accordionPane.setLayoutX(290);
		accordionPane.setLayoutY(25);
		// -------

		// -------
		spViews.setLayoutX(281);
		spViews.setLayoutY(22);
		// -------

		// -------

		// Pump menu
		lbFuelService.setLayoutX(20);
		lbFuelService.setLayoutY(35);
		spPumpTitlelb.setLayoutX(20);
		spPumpTitlelb.setLayoutY(55);

		lbChoosePump.setLayoutX(20);
		lbChoosePump.setLayoutY(65);
		cmbPumpsNum.setLayoutX(20);
		cmbPumpsNum.setLayoutY(90);

		lbPumpEnterTime.setLayoutX(20);
		lbPumpEnterTime.setLayoutY(135);

		tfPumpEnterTimeFrom.setLayoutX(20);
		tfPumpEnterTimeFrom.setLayoutY(160);

		tfPumpEnterTimeTo.setLayoutX(150);
		tfPumpEnterTimeTo.setLayoutY(160);

		lbPumpDatePicker.setLayoutX(20);
		lbPumpDatePicker.setLayoutY(195);

		pumpDatePickerFrom.setLayoutX(20);
		pumpDatePickerFrom.setLayoutY(220);

		pumpDatePickerTo.setLayoutX(150);
		pumpDatePickerTo.setLayoutY(220);

		btnFuelClear.setLayoutX(20);
		btnFuelClear.setLayoutY(270);

		btnFuelSubmit.setLayoutX(150);
		btnFuelSubmit.setLayoutY(270);

		// -------
		spMenu.setLayoutX(5);
		spMenu.setLayoutY(325);
		// -------

		// Cleaning menu
		lbCleaningService.setLayoutX(20);
		lbCleaningService.setLayoutY(340);

		spCleanTitlelb.setLayoutX(20);
		spCleanTitlelb.setLayoutY(360);

		lbCleanEnterTime.setLayoutX(20);
		lbCleanEnterTime.setLayoutY(375);

		tfCleanEnterTimeFrom.setLayoutX(20);
		tfCleanEnterTimeFrom.setLayoutY(395);

		tfCleanEnterTimeTo.setLayoutX(150);
		tfCleanEnterTimeTo.setLayoutY(395);

		lbCleanDatePicker.setLayoutX(20);
		lbCleanDatePicker.setLayoutY(425);

		cleanDatePickerFrom.setLayoutX(20);
		cleanDatePickerFrom.setLayoutY(450);

		cleanDatePickerTo.setLayoutX(150);
		cleanDatePickerTo.setLayoutY(450);

		btnCleaningClear.setLayoutX(20);
		btnCleaningClear.setLayoutY(500);

		btnCleaningSubmit.setLayoutX(150);
		btnCleaningSubmit.setLayoutY(500);

		// -------

		// Add all components
		anchorPane.getChildren().addAll(lbCleanEnterTime, cleanDatePickerFrom,
				cleanDatePickerTo, tfCleanEnterTimeFrom, tfCleanEnterTimeTo,
				lbCleaningService, btnCleaningSubmit, btnCleaningClear, spMenu,
				lbFuelService, accordionPane, spPumpTitlelb, spCleanTitlelb,
				spViews, btnFuelSubmit, lbPumpEnterTime, tfPumpEnterTimeFrom,
				tfPumpEnterTimeTo, pumpDatePickerFrom, pumpDatePickerTo,
				cmbPumpsNum, lbPumpDatePicker, lbChoosePump, btnFuelClear,
				lbCleanDatePicker);

	}//

	private void resetFuelComponents() {
		cmbPumpsNum.getSelectionModel().clearSelection();
		tfPumpEnterTimeFrom.clear();
		tfPumpEnterTimeTo.clear();
		pumpDatePickerFrom.resetDate();
		pumpDatePickerTo.resetDate();

	}//

	private void resetCleaningComponents() {

		tfCleanEnterTimeFrom.clear();
		tfCleanEnterTimeTo.clear();
		cleanDatePickerFrom.resetDate();
		cleanDatePickerTo.resetDate();

	}//

	private void handleFuelFormSubmission() {

		String jpaSql = "SELECT p FROM jpaEntities.Pump p ";
		String jpaWhere = "";

		String sql = "SELECT * FROM Pump ";
		String where = "";

		if (cmbPumpsNum.getSelectionModel().getSelectedItem() != null) {
			where += ((where == "") ? " WHERE " : " AND ") + "Id = " + "'"
					+ cmbPumpsNum.getSelectionModel().getSelectedIndex() + "'";

			jpaWhere += ((jpaWhere == "") ? " WHERE " : " AND ") + "p.Id = "
					+ "'" + cmbPumpsNum.getSelectionModel().getSelectedIndex()
					+ "'";

		}

		/*
		 * 1) Ensure time pattern using regular expressions. Deitel 9th page
		 * 736. 2)Check "Like" works.
		 */
		if (!tfPumpEnterTimeFrom.getText().isEmpty()) {

			where += ((where == "") ? " WHERE " : " AND ") + "Time BETWEEN "
					+ "'" + tfPumpEnterTimeFrom.getText() + "'";

			jpaWhere += ((jpaWhere == "") ? " WHERE " : " AND ")
					+ "p.Time BETWEEN " + "'" + tfPumpEnterTimeFrom.getText()
					+ "'";

		}

		if (!tfPumpEnterTimeTo.getText().isEmpty()) {

			where += " AND '" + tfPumpEnterTimeTo.getText() + "'";

			jpaWhere += " AND '" + tfPumpEnterTimeTo.getText() + "'";

		}

		/*
		 * 
		 * MySQL retrieves and displays DATE values in 'YYYY-MM-DD' format.
		 */

		if (!pumpDatePickerFrom.getFormattedValue().isEmpty()) {
			where += ((where == "") ? " WHERE " : " AND ") + "Date BETWEEN "
					+ "'" + pumpDatePickerFrom.getFormattedValue() + "'";

			jpaWhere += ((jpaWhere == "") ? " WHERE " : " AND ")
					+ "p.Date BETWEEN " + "'"
					+ pumpDatePickerFrom.getFormattedValue() + "'";

		}

		if (!pumpDatePickerTo.getFormattedValue().isEmpty()) {
			where += " AND '" + pumpDatePickerTo.getFormattedValue() + "'";
			jpaWhere += " AND '" + pumpDatePickerTo.getFormattedValue() + "'";
		}

		fireSubmitFuelFormDbTabRequest(sql + where, jpaSql + jpaWhere);

	}//

	private void handleCleaningFormSubmission() {

		String jpaSql = "SELECT cs FROM jpaEntities.CleaningService cs ";
		String jpaWhere = "";

		String sql = "SELECT * FROM CleaningService ";
		String where = "";

		/*
		 * 1) Ensure time pattern using regular expressions. Deitel 9th page
		 * 736. 2)Check "Like" works.
		 */
		if (!tfCleanEnterTimeFrom.getText().isEmpty()) {
			where += ((where == "") ? " WHERE " : " AND ") + "Time BETWEEN "
					+ "'" + tfCleanEnterTimeFrom.getText() + "'";

			jpaWhere += ((jpaWhere == "") ? " WHERE " : " AND ")
					+ "cs.Time BETWEEN " + "'" + tfCleanEnterTimeFrom.getText()
					+ "'";

		}

		if (!tfCleanEnterTimeTo.getText().isEmpty()) {
			where += " AND '" + tfCleanEnterTimeTo.getText() + "'";

			jpaWhere += " AND '" + tfCleanEnterTimeTo.getText() + "'";

		}

		if (!cleanDatePickerFrom.getFormattedValue().isEmpty()) {
			where += ((where == "") ? " WHERE " : " AND ") + "Date BETWEEN "
					+ "'" + cleanDatePickerFrom.getFormattedValue() + "'";

			jpaWhere += ((jpaWhere == "") ? " WHERE " : " AND ")
					+ "cs.Date BETWEEN " + "'"
					+ cleanDatePickerFrom.getFormattedValue() + "'";
		}

		if (!cleanDatePickerTo.getFormattedValue().isEmpty()) {
			where += " AND '" + cleanDatePickerTo.getFormattedValue() + "'";

			jpaWhere += " AND '" + cleanDatePickerTo.getFormattedValue() + "'";
		}

		fireSubmitCleaningFormDbTabRequest(sql + where, jpaSql + jpaWhere);
	}//

	private void handleTotProfitSubmission() {
		fireGetTotProfitFormDbTabRequest();
	}

	// --------------------------------------------
	public void registerListener(TabsPane tabPane) {
		this.tabPane = tabPane;
	}//

	private int fireReqeustPumpNum() {
		return tabPane.requestPumpNum();
	}

	private void fireSubmitFuelFormDbTabRequest(String sql, String jpaSql) {
		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				HashMap<String, Object> hashMap = null;
				try {
					hashMap = tabPane.requestFuelFormSubmission(sql, jpaSql);
					tbPump.setRows(hashMap);
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}// run
		});
		taskThr.start();
	}

	private void fireSubmitCleaningFormDbTabRequest(String sql, String jpaSql) {
		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				HashMap<String, Object> hashMap = null;
				try {
					hashMap = tabPane
							.requestCleaningFormSubmission(sql, jpaSql);
					tbCleaning.setRows(hashMap);
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}// run
		});
		taskThr.start();
	}

	private void fireGetTotProfitFormDbTabRequest() {
		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				HashMap<String, Object> hashMap;
				try {

					hashMap = tabPane.requestTotProfitsFormSubmission();

					profitsTitledPane.setData(hashMap);

				} catch (Exception e) {
					e.printStackTrace();
				}
			}// run
		});
		taskThr.start();
	}

	// --------------------------------------------

}// DbTab

