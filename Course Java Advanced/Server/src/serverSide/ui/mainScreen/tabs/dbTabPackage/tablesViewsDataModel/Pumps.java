package serverSide.ui.mainScreen.tabs.dbTabPackage.tablesViewsDataModel;

import javafx.beans.property.SimpleStringProperty;

/*
 * 
 * When you create a table in a JavaFX application, 
 * it is a best practice to implement a class 
 * that defines the data model and provides 
 * methods and fields to further work with the table
 * 
 * 
 * http://docs.oracle.com/javase/8/javafx/user-interface-tutorial/table-view.htm#CJAGAAEE
 * 
 * 
 * */

public class Pumps {

	private SimpleStringProperty pumpNum;
	private SimpleStringProperty profit;
	private SimpleStringProperty date;
	private SimpleStringProperty time;

	public Pumps(String pumpNum, String profit, String time, String date) {

		this.pumpNum = new SimpleStringProperty(pumpNum);
		this.profit = new SimpleStringProperty(profit);
		this.time = new SimpleStringProperty(time);
		this.date = new SimpleStringProperty(date);
	}

	public String getPumpNum() {
		return pumpNum.get();
	}

	public void setPumpNum(SimpleStringProperty pumpNum) {
		this.pumpNum = pumpNum;
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