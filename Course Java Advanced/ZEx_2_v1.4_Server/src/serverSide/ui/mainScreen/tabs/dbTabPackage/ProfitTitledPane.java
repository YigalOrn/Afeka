package serverSide.ui.mainScreen.tabs.dbTabPackage;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import javafx.application.Platform;
import javafx.scene.control.Label;
import javafx.scene.control.TitledPane;
import javafx.scene.layout.Pane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class ProfitTitledPane extends TitledPane {

	/***/
	private Label lbData;
	private Font myFont = Font.font("Consolas", FontWeight.BOLD, 20);
	private Pane pane;

	/***/
	public ProfitTitledPane() {
		setText("Profits");
		init();
	}// c'tor

	private void init() {
		lbData = new Label();
		lbData.setFont(myFont);
		lbData.setText("Profits:\n" + "Total profits - 0");
		pane = new Pane(lbData);
		lbData.setLayoutX(10);
		lbData.setLayoutY(10);
		setContent(pane);
	}

	public void setData(HashMap<String, Object> hashMap) {
		Platform.runLater(new Runnable() {
			@Override
			public void run() {

				// ----
				if (hashMap.containsKey("rs") && hashMap.get("rs") != null) {

					ResultSet rs = (ResultSet) hashMap.get("rs");

					try {

						while (rs.next()) {
							lbData.setText("Profits:\n"
									+ "Total profits - "
									+ (rs.getString("TotProfit") == null ? "0"
											: rs.getString("TotProfit")) + "\n");
						}// while

						rs.getStatement().close();
						rs.close();

					} catch (SQLException e) {
						e.printStackTrace();
					}

				} else if (hashMap.containsKey("list")
						&& hashMap.get("list") != null) {

					List<jpaEntities.Profits> list = (List<jpaEntities.Profits>) hashMap
							.get("list");

					Iterator<jpaEntities.Profits> it = list.iterator();

					while (it.hasNext()) {

						jpaEntities.Profits pr = it.next();

						lbData.setText("Profits:\n" + "Total profits - "
								+ pr.getProfit() + "\n");

					}// while

				}

				// ----

			}// run

		});
	}

}//
