package serverSide.ui.mainScreen.tabs.dbTabPackage.tableViews;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import jpaEntities.Pump;
import serverSide.ui.mainScreen.tabs.dbTabPackage.DisplayUnit;
import serverSide.ui.mainScreen.tabs.dbTabPackage.tablesViewsDataModel.Pumps;

public class TablePump extends DisplayUnit {

	/** Data fields */
	private TableView<Pumps> tableView;
	private TableColumn<Pumps, String> pumpNumCol;
	private TableColumn<Pumps, String> profitCol;
	private TableColumn<Pumps, String> timeCol;
	private TableColumn<Pumps, String> dateCol;

	private final ObservableList<Pumps> data = FXCollections
			.observableArrayList();

	public TablePump() {
		super("Pumps");
		init();
	}

	private void init() {

		tableView = new TableView<>();
		tableView.setEditable(false);

		// ----
		pumpNumCol = new TableColumn<>("PumpNum");
		profitCol = new TableColumn<>("Profit");
		timeCol = new TableColumn<>("Time");
		dateCol = new TableColumn<>("Date");
		// ----

		/*
		 * 
		 * The next step is to associate the data with the table columns. You
		 * can do this through the properties defined for each data element
		 */
		pumpNumCol.setCellValueFactory(new PropertyValueFactory<>("pumpNum"));
		profitCol.setCellValueFactory(new PropertyValueFactory<>("profit"));
		timeCol.setCellValueFactory(new PropertyValueFactory<>("time"));
		dateCol.setCellValueFactory(new PropertyValueFactory<>("date"));
		tableView.getColumns().addAll(pumpNumCol, profitCol, timeCol, dateCol);
	}

	public void setRows(HashMap<String, Object> hashMap) {

		Platform.runLater(new Runnable() {
			@Override
			public void run() {

				// ----
				if (hashMap.containsKey("rs") && hashMap.get("rs") != null) {

					ResultSet rs = (ResultSet) hashMap.get("rs");

					data.clear();

					try {

						while (rs.next()) {
							data.add(new Pumps(rs.getString("Id"), rs
									.getString("Profit"), rs.getString("Time"),
									rs.getString("Date")));
						}// while

						tableView.setItems(data);
						scrollPane.setContent(tableView);

						rs.getStatement().close();
						rs.close();

					} catch (SQLException e) {
						e.printStackTrace();
					}

				} else if (hashMap.containsKey("list")
						&& hashMap.get("list") != null) {

					data.clear();

					List<jpaEntities.Pump> list = (List<Pump>) hashMap
							.get("list");

					Iterator<jpaEntities.Pump> it = list.iterator();

					while (it.hasNext()) {

						jpaEntities.Pump p = it.next();

						data.add(new Pumps("" + p.getId(), "" + p.getProfit(),
								p.getTime(), p.getDate()));

					}// while

					tableView.setItems(data);
					scrollPane.setContent(tableView);

				}

				// ----

			}// run

		});

	}//

}//

