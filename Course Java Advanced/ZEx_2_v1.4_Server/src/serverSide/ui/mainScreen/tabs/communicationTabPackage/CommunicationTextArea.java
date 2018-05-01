package serverSide.ui.mainScreen.tabs.communicationTabPackage;

import javafx.scene.control.TextArea;

public class CommunicationTextArea extends TextArea {

	/** Data Fields */

	/** C'tor */
	public CommunicationTextArea() {
		setProperties();
	}// c'tor

	/** Class methods */

	private void setProperties() {
		setEditable(false);
		setWrapText(true);
		setId("textAreaStyle");
	}//

	public void postString(String text) {
		CommunicationTextArea.this.appendText(">> " + text + "\n");
	}//

}//
