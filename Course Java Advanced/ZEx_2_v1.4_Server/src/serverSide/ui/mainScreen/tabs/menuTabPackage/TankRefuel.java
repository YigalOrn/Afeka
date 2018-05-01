/*
 * 
 * http://docs.oracle.com/javase/8/javafx/visual-effects-tutorial/basics.htm#CIHHAACG
 * 
 * */

package serverSide.ui.mainScreen.tabs.menuTabPackage;


import serverSide.ui.mainScreen.tabsPane.TabsPane;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.layout.Pane;

public class TankRefuel extends Pane {

	/** Data fields */
	private ProgressBar pb;
	private ProgressIndicator pi;
	private Label lbPercent;

	private TabsPane tabPane;
	private Task<Void> task;

	/** C'tor */
	public TankRefuel(TabsPane tabPane) {
		registerListener(tabPane);
		init();
		getChildren().addAll(pb, pi, lbPercent);
	}// c'tor

	private void init() {

		// -----
		pb = new ProgressBar();
		pb.setVisible(false);
		pb.setPrefSize(500, 30);
		pb.setLayoutX(180);
		pb.setLayoutY(100);
		// -----

		// -----
		pi = new ProgressIndicator();
		pi.setPrefSize(200, 200);
		pi.setLayoutX(300);
		pi.setLayoutY(100);
		// -----

		// -----
		lbPercent = new Label("");
		lbPercent.setLayoutX(160);
		lbPercent.setLayoutY(100);
		// -----

	}//

	public void activate() {
		pi.setProgress(-5.0f);
		if (task == null || task.isDone()) {
			task = new Task<Void>() {
				@Override
				public Void call() {
					long max = 0;
					fireTankRefuel();// Call once
					try {
						do {
							Thread.sleep(200);
							max = fireGetTankRefuelTime();
							
							if(max == -1)
								break;
							
						} while (max == 0);
					} catch (InterruptedException ex) {
						ex.printStackTrace();
					}
					pi.setVisible(false);
					try {
						for (int i = 1; i <= max; i++) {
							// See link in FX runner code
							if (isCancelled()) {
								break;
							}
							Thread.sleep(10);// Speed control
							updateProgress(i, max);
							// lbPercent.setText("" + ((i / max) * 100));
							if (i == 1)
								pb.setVisible(true);
						}
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					Platform.runLater(new Runnable() {
						@Override
						public void run() {
							setIndicatorFinish();
						}
					});
					fireTankLockRelease();
					return null;
				}
			};
			pb.progressProperty().bind(task.progressProperty());
			Thread thr = new Thread(task);
			thr.start();
		}// if
	}

	public void setIndicatorFinish() {
		pb.setVisible(false);
		lbPercent.setText("");
		pi.setVisible(true);
		pi.setProgress(1.0f);
		// pi.progressProperty().bind(pb.progressProperty());
	}

	// -------------------------------------------------
	public void registerListener(TabsPane tabPane) {
		this.tabPane = tabPane;
	}

	private void fireTankRefuel() {
		tabPane.requestTankRefuel();
	}

	private long fireGetTankRefuelTime() {
		return tabPane.requestTankRefuelTime();
	}

	private void fireTankLockRelease() {
		tabPane.requestTankLockRelease();
	}
	// -------------------------------------------------

}//
