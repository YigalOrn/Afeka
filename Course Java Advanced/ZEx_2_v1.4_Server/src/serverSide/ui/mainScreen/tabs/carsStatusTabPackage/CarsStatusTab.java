package serverSide.ui.mainScreen.tabs.carsStatusTabPackage;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

import serverSide.bl.GasStationBL.Car;
import javafx.scene.control.Tab;
import javafx.scene.image.Image;

public class CarsStatusTab extends Tab {

	/** Data Fields */

	/*
	 * 
	 * 
	 * */
	private DisplayPane dispPane;
	/*
	 * 
	 * */
	private HashMap<Integer, DisplayCarUnit> trackMap;

	/*
	 * 
	 * 
	 * */
	private static final ArrayList<Image> IMAGESLIST;
	private static int NUMOFIMAGES = 26;

	static {
		IMAGESLIST = new ArrayList<>();
		initImages();
	}

	/** C'tor */
	public CarsStatusTab(String tabTilte) {
		super(tabTilte);
		setClosable(false);
		trackMap = new HashMap<>();
		dispPane = new DisplayPane();
		setContent(dispPane);
	}// c'tor

	/** Class methods */

	private static void initImages() {
		Image img = null;
		for (int i = 0; i < NUMOFIMAGES; i++) {
			img = new Image(
					CarsStatusTab.class
							.getResourceAsStream("vehicles_black_grey/"
									+ (i + 1) + ".png"));
			IMAGESLIST.add(img);
		}// for
		shuffelImages();
	}//

	private static void shuffelImages() {
		Collections.shuffle(IMAGESLIST);
	}// shuffelImages

	private static Image getRandomImage() {
		int k = (int) (Math.random() * IMAGESLIST.size());
		return IMAGESLIST.get(k);
	}

	// --------------------------------------------
	public void handleCarVisualDisplay(Car car) {

		if (!trackMap.containsKey(car.getId())) {
			CarsStatusTab.shuffelImages();
			trackMap.put(car.getId(), new DisplayCarUnit(getRandomImage()));
		}
		DisplayCarUnit disp = trackMap.get(car.getId());

		dispPane.handleCarDisplay(car.getState(), disp);
	}
	// --------------------------------------------

}// MyTab

