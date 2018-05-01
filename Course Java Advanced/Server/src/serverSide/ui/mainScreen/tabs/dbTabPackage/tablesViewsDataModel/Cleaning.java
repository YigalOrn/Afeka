package serverSide.ui.mainScreen.tabs.dbTabPackage.tablesViewsDataModel;

import javafx.beans.property.SimpleStringProperty;

public class Cleaning {

	private SimpleStringProperty id;
	private SimpleStringProperty profit;
	private SimpleStringProperty date;
	private SimpleStringProperty time;

	public Cleaning(String id, String profit, String time, String date) {

		this.id = new SimpleStringProperty(id);
		this.profit = new SimpleStringProperty(profit);
		this.time = new SimpleStringProperty(time);
		this.date = new SimpleStringProperty(date);
	}

	public String getId() {
		return id.get();
	}

	public void setId(SimpleStringProperty id) {
		this.id = id;
	}

	public String getProfit() {
		return profit.get();
	}

	public void setProfit(SimpleStringProperty profit) {
		this.profit = profit;
	}

	public String getDate() {
		return date.get();
	}

	public void setDate(SimpleStringProperty date) {
		this.date = date;
	}

	public String getTime() {
		return time.get();
	}

	public void setTime(SimpleStringProperty time) {
		this.time = time;
	}

}