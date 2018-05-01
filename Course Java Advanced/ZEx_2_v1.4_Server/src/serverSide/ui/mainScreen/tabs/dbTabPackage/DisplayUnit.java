/*
 * 
 * http://docs.oracle.com/javafx/2/ui_controls/table-view.htm
 * 
 * https://docs.oracle.com/javafx/2/ui_controls/accordion-titledpane.htm
 * 
 * 
 * Coloring empty rows in a table view with CSS:
 * http://docs.oracle.com/javase/8/javafx/user-interface-tutorial/custom.htm#CACDJEHJ
 * 
 * 
 * 
 * */

package serverSide.ui.mainScreen.tabs.dbTabPackage;

import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TitledPane;

public class DisplayUnit extends TitledPane {

	/** Data Fields */
	protected ScrollPane scrollPane;
	/*
	 * Place holder
	 */
	protected ProgressIndicator pin = new ProgressIndicator(-1);

	/** C'tor */
	public DisplayUnit(String title) {
		setText(title);
		scrollPane = new ScrollPane();
		initProperties();
		setContent(scrollPane);
	}// c'tor

	private void initProperties() {
		pin.setPrefSize(100, 100);
		scrollPane.setContent(pin);

		// :)
		scrollPane.setFitToHeight(true);
		scrollPane.setFitToWidth(true);

	}//

	public void setPlaceHolder() {
		scrollPane.setContent(pin);
	}

}// DisplayTable

