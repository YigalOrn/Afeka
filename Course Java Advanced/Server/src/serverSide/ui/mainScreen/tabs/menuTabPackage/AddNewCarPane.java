/*
 * http://blog.ngopal.com.np/2012/07/11/customize-scrollbar-via-css/
 * 
 * 
 * */

package serverSide.ui.mainScreen.tabs.menuTabPackage;

import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Orientation;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Separator;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;

public class AddNewCarPane extends GridPane {

	/** Data fields */
	private Text titleTextFX;
	private Label lbCarId;
	private Label lbNumOfLiters;
	private Label lbErrorNumOfLiters;
	private Label lbSubmitError;
	private TextField tfCarId;
	private TextField tfNumOfLiters;
	private ComboBox<String> cmbPumpNum;
	private RadioButton rbWantCleaning;

	private Button btnSubmit;
	private Separator sp;

	private TabsPane tabPane;

	/** C'tor */
	public AddNewCarPane(TabsPane tabPane) {
		registerListener(tabPane);
		initControllers();
		setLayout();
		freezeSubmit();
	}// c'tor

	/** Class methods */

	private void initControllers() {

		titleTextFX = new Text("Add New Car Menu");

		lbCarId = new Label("Car id : ");
		lbNumOfLiters = new Label("Num of liters : ");

		cmbPumpNum = new ComboBox<>();
		cmbPumpNum.setEditable(false);
		cmbPumpNum.setVisibleRowCount(5);

		cmbPumpNum.setId("cmbPumpNumStyle");

		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				Platform.runLater(new Runnable() {
					@Override
					public void run() {
						int n = fireReqeustPumpNum();
						for (int i = 0; i < n; i++) {
							cmbPumpNum.getItems().add("Pump " + i);
						}
						cmbPumpNum.getSelectionModel().clearSelection();
						unFreezeSubmit();
					}// run
				});
			}
		});
		taskThr.start();

		rbWantCleaning = new RadioButton("With cleaning ?");
		rbWantCleaning.setTextAlignment(TextAlignment.LEFT);
		rbWantCleaning.setId("rbWantCleaningStyle");

		tfCarId = new TextField("Notice Cars id fromat... ");
		tfCarId.setPrefWidth(200);
		tfCarId.setFont(Font.font("Arial", FontWeight.BOLD, 15));

		/*
		 * New in FX
		 */
		lbErrorNumOfLiters = new Label();
		lbErrorNumOfLiters.setFont(Font.font("OCR A Extended", FontWeight.BOLD,
				13));

		tfNumOfLiters = new TextField() {

			@Override
			public void replaceText(int start, int end, String text) {
				if (!text.matches("[a-z, A-Z]")) {
					super.replaceText(start, end, text);
					lbErrorNumOfLiters.setText("");
				} else {
					lbErrorNumOfLiters
							.setText("            # Enter a numeric value");
				}
			}

			@Override
			public void replaceSelection(String text) {
				if (!text.matches("[a-z, A-Z]")) {
					super.replaceSelection(text);
					lbErrorNumOfLiters.setText("");
				} else {
					lbErrorNumOfLiters.setText("Enter a numeric value");
				}
			}
		};
		tfNumOfLiters.setPrefWidth(100);
		tfNumOfLiters.setFont(Font.font("Arial", FontWeight.BOLD, 15));

		btnSubmit = new Button("submit");
		btnSubmit.addEventHandler(MouseEvent.MOUSE_CLICKED,
				new EventHandler<MouseEvent>() {

					@Override
					public void handle(MouseEvent event) {

						lbSubmitError.setText("");
						checkUserInput();

						// Process from data...
						String[] params = new String[4];

						params[0] = tfCarId.getText();

						if (rbWantCleaning.isSelected()) {
							params[1] = "true";
						} else {
							params[1] = "false";
						}

						params[2] = tfNumOfLiters.getText();
						params[3] = ""
								+ cmbPumpNum.getSelectionModel()
										.getSelectedIndex();

						// ---------
						resetFormComponents();
						fireSubmitCar(params);
						cmbPumpNum.getSelectionModel().clearSelection();
					}
				});

		btnSubmit.setId("btnSubmitStyle");

		lbSubmitError = new Label();
		lbErrorNumOfLiters.setFont(Font.font("OCR A Extended", FontWeight.BOLD,
				13));

		sp = new Separator(Orientation.VERTICAL);
		sp.setStyle("-fx-background-color:#CD3700;");

		// CSS id set
		titleTextFX.setId("titleTextFXStyle");
		lbCarId.setId("lbCarIdStyle");
		lbNumOfLiters.setId("lbNumOfLitersStyle");
		lbErrorNumOfLiters.setId("lbErrorNumOfLitersStyle");
		lbSubmitError.setId("lbSubmitErrorStyle");

	}//

	private void setLayout() {

		setVgap(10);
		setHgap(10);
		setPadding(new Insets(25, 25, 25, 25));

		add(titleTextFX, 1, 0, 3, 3);

		HBox hBoxCarId = new HBox(55);
		hBoxCarId.getChildren().addAll(lbCarId, tfCarId);
		add(hBoxCarId, 1, 4);

		HBox hBoxNumOfliters = new HBox(18);
		hBoxNumOfliters.getChildren().addAll(lbNumOfLiters, tfNumOfLiters);
		add(hBoxNumOfliters, 1, 5);

		add(lbErrorNumOfLiters, 1, 6);

		HBox hBox = new HBox(30);
		hBox.getChildren().addAll(cmbPumpNum, rbWantCleaning);

		add(hBox, 1, 7);

		add(btnSubmit, 1, 11);

		add(lbSubmitError, 1, 12);

		add(sp, 0, 0, 1, 18);

	}//

	private void resetFormComponents() {
		tfCarId.setText("Notice Cars id fromat... ");
		tfNumOfLiters.setText("");
		lbErrorNumOfLiters.setText("");
		rbWantCleaning.setSelected(false);
		cmbPumpNum.getSelectionModel().clearSelection();
	}//

	private void checkUserInput() {
		if (tfCarId.getText().isEmpty() || tfNumOfLiters.getText().isEmpty()
				|| (cmbPumpNum.getSelectionModel().getSelectedIndex() == -1)
				|| !rbWantCleaning.isSelected()) {

			lbSubmitError.setText("# Notice some of the fields are empty");
		}
	}//

	private void freezeSubmit() {
		btnSubmit.setDisable(true);
	}

	private void unFreezeSubmit() {
		btnSubmit.setDisable(false);
	}

	// --------------------------------------------
	public void registerListener(TabsPane tabPane) {
		this.tabPane = tabPane;
	}

	private int fireReqeustPumpNum() {
		return tabPane.requestPumpNum();
	}

	private void fireSubmitCar(String[] carParameters) {
		Thread taskThr = new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					tabPane.addCarFromFX(carParameters, false);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}// run
		});
		taskThr.start();
	}
	// --------------------------------------------

}//
