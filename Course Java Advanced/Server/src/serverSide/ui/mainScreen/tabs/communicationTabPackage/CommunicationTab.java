/*
 * 
 * 
 * 
 * 
 * */

package serverSide.ui.mainScreen.tabs.communicationTabPackage;

import javafx.application.Platform;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.ScrollPane.ScrollBarPolicy;
import javafx.scene.control.Tab;

public class CommunicationTab extends Tab {

	/** Data fields */

	/*
	 * 
	 * The CommunicationTextArea instance is a modified TextArea object. This
	 * object will show all textual communication between the server and the
	 * clients that are connected using name tags to distinguish among all
	 * participating threads.
	 * 
	 * Also will print each cars progress/status as it proceeds through the
	 * different gas station stops.
	 * 
	 * Basically it is the most simple solution to the progress monitoring
	 * problem and it just replaces the console as a GUI console...
	 */
	private final CommunicationTextArea textArea;

	/** C'tor */
	public CommunicationTab(String tabTilte) {
		super(tabTilte);
		setClosable(false);
		// Create a new instance
		textArea = new CommunicationTextArea();
		ScrollPane scrollPane = new ScrollPane();
		scrollPane.setVbarPolicy(ScrollBarPolicy.NEVER);
		scrollPane.setHbarPolicy(ScrollBarPolicy.NEVER);
		scrollPane.setContent(textArea);
		scrollPane.setFitToHeight(true);
		scrollPane.setFitToWidth(true);
		scrollPane.setId("scrollPaneStyle");

		// Add to the Tab
		setContent(scrollPane);
	}// c'tor

	/** Class methods */

	public void postString(String text) {
		Platform.runLater(new Runnable() {
			@Override
			public void run() {
				textArea.postString(text);
			}
		});
	}//

}// MyTab

