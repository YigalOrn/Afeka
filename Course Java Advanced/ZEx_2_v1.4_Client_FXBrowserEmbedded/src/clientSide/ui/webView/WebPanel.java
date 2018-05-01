/*
 *  http://docs.oracle.com/javafx/2/events/jfxpub-events.htm
 *  http://code.makery.ch/blog/javafx-8-event-handling-examples/
 *  http://docs.oracle.com/javase/8/javafx/embedded-browser-tutorial/overview.htm#JFXWV135
 * 
 * */

package clientSide.ui.webView;

import java.util.Arrays;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.embed.swing.JFXPanel;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ContentDisplay;
import javafx.scene.control.ListCell;
import javafx.scene.image.Image;
import javafx.scene.layout.VBox;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;
import javafx.scene.image.*;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.SpringLayout;
import javax.swing.border.BevelBorder;

public class WebPanel extends JPanel {

	/** Data fields */
	private static final long serialVersionUID = 1L;

	private JFXPanel jfxPanel;
	private WebView browser;
	private WebEngine webEngine;

	private static String[] titles = { "Afeka Software Engineering web site",
			"Kookle - Keren Kalif web site",
			"# Gas-Station add new car Servlet",
			"# Gas-Station WebService via Servlet", "Google" };

	private static final String[] urls = {
			"http://english.afeka.ac.il/academic-programs/bachelor-degree/software-engineering/",
			"http://www.kerenkalif.com",
			"http://localhost:8080/ZEx_2_v1.4_Client_FXBrowserEmbedded/AddNewCar.html",
			"http://localhost:8080/ZEx_2_v1.4_Client_FXBrowserEmbedded/CarHistoryMenu.html",
			"http://www.google.com" };

	private static Image[] images = new Image[urls.length];

	/** C'tor */
	public WebPanel() {
		initComponents();
		initLayout();
	}//

	private void initComponents() {
		Thread thrTask = new Thread(new Runnable() {
			@Override
			public void run() {
				// initTomcatEmbedded();
			}
		});
		thrTask.setDaemon(true);
		thrTask.start();
		initJFXPanelWithSWINGThread();
		initJFXPanelWithFXThread();
	}

	private void initLayout() {

		SpringLayout spLayout = new SpringLayout();
		setLayout(spLayout);

		spLayout.putConstraint(SpringLayout.NORTH, jfxPanel, 40,
				SpringLayout.NORTH, this);

		spLayout.putConstraint(SpringLayout.WEST, jfxPanel, 25,
				SpringLayout.WEST, this);
	}

	private void initJFXPanelWithSWINGThread() {
		jfxPanel = new JFXPanel();
		jfxPanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
		add(jfxPanel);
	}

	private void initJFXPanelWithFXThread() {
		Platform.runLater(new Runnable() {
			@Override
			public void run() {
				initFXApplication();
			}
		});
	}

	private void initFXApplication() {
		// This method is invoked on the JavaFX thread
		Scene scene = createScene();
		// Add Scene Graph to the JFXPanel
		jfxPanel.setScene(scene);
	}

	private Scene createScene() {
		// Holds the components that will put together the FX application
		VBox vBox = new VBox();

		/*
		 * // In use with the combo box initImages(); // In use with the combo
		 * box ObservableList<Image> data = FXCollections.observableList(Arrays
		 * .asList(images));
		 */

		// In use with the combo box
		ObservableList<String> data = FXCollections.observableList(Arrays
				.asList(titles));
		// Serves as an address holder
		ComboBox<String> cmb = new ComboBox<>(data);
		cmb.setPrefWidth(650);

		// ------------
		vBox.setOnMouseEntered((event) -> {
			// Knows to run of FX thread
			if (!vBox.getChildren().contains(cmb))
				vBox.getChildren().add(cmb);
		});
		vBox.setOnMouseExited((event) -> {
			// Knows to run of FX thread
			if (!cmb.isFocused())
				vBox.getChildren().remove(cmb);
		});
		// ------------

		// Setting the policy for a combo box event
		cmb.setOnAction((event) -> {
			int index = cmb.getSelectionModel().getSelectedIndex();
			// Knows to run of FX thread
			webEngine.load(urls[index]);
		});

		browser = new WebView();
		webEngine = browser.getEngine();
		webEngine.load(urls[0]);

		vBox.getChildren().add(browser);
		vBox.setAlignment(Pos.CENTER);

		Scene scene = new Scene(vBox, 650, 400);
		return scene;
	}

	/*
	 * private void initImages() { for (int i = 0; i < images.length; i++) {
	 * 
	 * images[i] = new Image(
	 * WebPanel.class.getResourceAsStream("BrowserPanelIcons/" + (i + 1) +
	 * ".png")); } }
	 * 
	 * private ComboBox<Image> initCmb(ObservableList<Image> data) {
	 * 
	 * ComboBox<Image> cmb = new ComboBox<>(); cmb.getItems().addAll(data);
	 * cmb.setButtonCell(new ImageListCell()); cmb.setCellFactory(listView ->
	 * new ImageListCell()); cmb.getSelectionModel().select(0);
	 * 
	 * return cmb; }
	 * 
	 * 
	 * class ImageListCell extends ListCell<Image> { private final ImageView
	 * view;
	 * 
	 * ImageListCell() { setContentDisplay(ContentDisplay.GRAPHIC_ONLY); view =
	 * new ImageView(); }
	 * 
	 * @Override protected void updateItem(Image item, boolean empty) {
	 * super.updateItem(item, empty);
	 * 
	 * if (item == null || empty) { setGraphic(null); } else {
	 * view.setImage(item);
	 * 
	 * view.setScaleX(1); view.setScaleY(1);
	 * 
	 * setGraphic(view); } }
	 * 
	 * }
	 */

}// WebPanel
