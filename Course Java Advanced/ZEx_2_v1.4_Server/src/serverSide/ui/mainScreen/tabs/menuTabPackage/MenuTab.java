package serverSide.ui.mainScreen.tabs.menuTabPackage;

import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.scene.control.Tab;

public class MenuTab extends Tab {

	/** Data Fields */
	private DisplayMenu displayMenu;

	/** C'tor */
	public MenuTab(String tabTitle, TabsPane tabPane) {
		super(tabTitle);
		setClosable(false);
		displayMenu = new DisplayMenu(tabPane);
		setContent(displayMenu);
	}// c'tor

	public void handleTankFuelLevelLow() {
		displayMenu.createAlertAffectOnbtnReFuel();
	}

}// MenuTab
