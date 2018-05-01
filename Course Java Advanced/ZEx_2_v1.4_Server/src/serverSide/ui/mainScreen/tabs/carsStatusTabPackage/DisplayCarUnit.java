package serverSide.ui.mainScreen.tabs.carsStatusTabPackage;

import serverSide.bl.GasStationBL.carComplementary.CarStatus;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
//import javafx.scene.text.Font;
//import javafx.scene.text.FontWeight;

public class DisplayCarUnit extends Label {

	/** Data Fields */
	private Image carImg;
	private CarStatus.carState currentState;

	/** C'tor */
	public DisplayCarUnit(Image img) {
		this.carImg = img;
		setLabelProperties();
	}// c'tor

	private void setLabelProperties() {
		setGraphic(new ImageView(carImg));

		// ----
		setOnMouseEntered((MouseEvent e) -> {
			setScaleX(1.2);
			setScaleY(1.2);
		});

		setOnMouseExited((MouseEvent e) -> {
			setScaleX(1);
			setScaleY(1);
		});
		// ----

	}//

	public void setCurrentState(CarStatus.carState currentState) {
		this.currentState = currentState;
	}//

	public CarStatus.carState getCurrentState() {
		return currentState;
	}//

}// DisplayCarUnit

