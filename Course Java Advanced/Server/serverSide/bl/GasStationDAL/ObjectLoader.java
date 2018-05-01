package serverSide.bl.GasStationDAL;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import serverSide.bl.GasStationBL.Car;
import serverSide.bl.GasStationBL.FuelStock;
import serverSide.bl.GasStationBL.GasStation;
import serverSide.bl.GasStationBL.WashService;

public class ObjectLoader {

	public static ArrayList<GasStation> loadObject(File XmlFile) {

		ArrayList<GasStation> gasStations = new ArrayList<>();

		try {
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(XmlFile);
			NodeList gasStationsNodes = doc.getElementsByTagName("GasStation");

			for (int i = 0; i < gasStationsNodes.getLength(); i++) {
				int numOfPumps = Integer.parseInt(gasStationsNodes.item(i)
						.getAttributes().getNamedItem("numOfPumps")
						.getNodeValue());
				float pricePerLiter = Float.parseFloat(gasStationsNodes.item(i)
						.getAttributes().getNamedItem("pricePerLiter")
						.getNodeValue());

				GasStation newGs = new GasStation(numOfPumps, pricePerLiter);
				gasStations.add(newGs);

				NodeList gsValues = gasStationsNodes.item(i).getChildNodes();
				for (int j = 0; i < gsValues.getLength()
						&& gsValues.item(j) != null; j++) {
					Node currentNode = gsValues.item(j);
					String curNodeName = currentNode.getNodeName();
					if (curNodeName == "MainFuelPool") {
						float maxCapacity = Float.parseFloat(currentNode
								.getAttributes().getNamedItem("maxCapacity")
								.getNodeValue());
						float currentCapacity = Float
								.parseFloat(currentNode.getAttributes()
										.getNamedItem("currentCapacity")
										.getNodeValue());
						FuelStock newFs = new FuelStock(maxCapacity,
								currentCapacity);
						newGs.setFuelStock(newFs);

					}
					if (curNodeName == "CleaningService") {
						int numOfTeams = Integer.parseInt(currentNode
								.getAttributes().getNamedItem("numOfTeams")
								.getNodeValue());
						float price = Float.parseFloat(currentNode
								.getAttributes().getNamedItem("price")
								.getNodeValue());
						int secondsPerAutoClean = Integer.parseInt(currentNode
								.getAttributes()
								.getNamedItem("secondsPerAutoClean")
								.getNodeValue());
						WashService newWs = new WashService(numOfTeams, price,
								secondsPerAutoClean);
						newGs.setWashService(newWs);
					}
					if (curNodeName == "Cars") {
						NodeList cars = currentNode.getChildNodes();
						for (int k = 0; i < cars.getLength()
								&& cars.item(k) != null; k++) {
							if (cars.item(k).getNodeName() == "Car") {
								Node curCar = cars.item(k);
								int id = Integer.parseInt(curCar
										.getAttributes().getNamedItem("id")
										.getNodeValue());
								boolean wantCleaning;
								try {
									wantCleaning = Boolean.parseBoolean(curCar
											.getAttributes()
											.getNamedItem("wantCleaning")
											.getNodeValue());
								} catch (Exception e) {
									wantCleaning = false;
								}
								Car newCar = new Car(id, wantCleaning);

								NodeList wantsFuel = curCar.getChildNodes();
								for (int l = 0; l < wantsFuel.getLength()
										&& wantsFuel.item(l) != null; l++) {
									Node wantsFuelInfo = wantsFuel.item(l);
									if (wantsFuelInfo.getNodeName() == "WantsFuel") {
										float WantFuelNumOfLiters = Float
												.parseFloat(wantsFuelInfo
														.getAttributes()
														.getNamedItem(
																"numOfLiters")
														.getNodeValue());
										int WantFuelPumpNum = Integer
												.parseInt(wantsFuelInfo
														.getAttributes()
														.getNamedItem("pumpNum")
														.getNodeValue());
										newCar.WantsFuel(WantFuelNumOfLiters,
												WantFuelPumpNum);
									}
								}

								newGs.addToHoldList(newCar);

							}
						}
					}

				}

			}

		} catch (IOException | ParserConfigurationException | SAXException e) {
			e.printStackTrace();
		}
		return gasStations;

	}

}
