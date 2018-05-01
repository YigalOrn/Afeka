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

import serverSide.ui.mainScreen.tabs.dbTabPackage.DisplayUnit;
import serverSide.ui.mainScreen.tabs.dbTabPackage.tablesViewsDataModel.Cleaning;

public class TableCleaning extends DisplayUnit {

	/** Data fields */
	private TableView<Cleaning> tableView;
	private TableColumn<Cleaning, String> idCol;
	private TableColumn<Cleaning, String> profitCol;
	private TableColumn<Cleaning, String> timeCol;
	private TableColumn<Cleaning, String> dateCol;

	private final ObservableList<Cleaning> data = FXCollections
			.observableArrayList();

	public TableCleaning() {
		super("Cleaning service");
		init();
	}

	private void init() {

		tableView = new TableView<>();
		tableView.setEditable(false);

		// ----
		idCol = new TableColumn<>("Id");
		profitCol = new TableColumn<>("Profit");
		timeCol = new TableColumn<>("Time");
		dateCol = new TableColumn<>("Date");
		// ----

		/*
		 * 
		 * The next step is to associate the data with the table columns. You
		 * can do this through the properties defined for each data element
		 */
		idCol.setCellValueFactory(new PropertyValueFactory<>("id"));
		profitCol.setCellValueFactory(new PropertyValueFactory<>("profit"));
		timeCol.setCellValueFactory(new PropertyValueFactory<>("time"));
		dateCol.setCellValueFactory(new PropertyValueFactory<>("date"));
		tableView.getColumns().addAll(idCol, profitCol, timeCol, dateCol);

	}

	public void setRows(HashMap<String, Object> hashMap) throws SQLException {

		Platform.runLater(new Runnable() {
			@Override
			public void run() {

				// ----
				if (hashMap.containsKey("rs") && hashMap.get("rs") != null) {

					ResultSet rs = (ResultSet) hashMap.get("rs");

					data.clear();

					try {

						while (rs.next()) {
							data.add(new Cleaning(rs.getString("Id"), rs
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

					List<jpaEntities.CleaningService> list = (List<jpaEntities.CleaningService>) hashMap
							.get("list");

					Iterator<jpaEntities.CleaningService> it = list.iterator();

					while (it.hasNext()) {

						jpaEntities.CleaningService cs = it.next();

						data.add(new Cleaning("" + cs.getId(), ""
								+ cs.getProfit(), cs.getTime(), cs.getDate()));

					}// while

					tableView.setItems(data);
					scrollPane.setContent(tableView);

				}

				// ----

			}// run

		});

	}

}//

