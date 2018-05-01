package serverSide.ui.mainScreen.tabs.dbTabPackage;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import javafx.scene.control.DateCell;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Tooltip;
import javafx.util.Callback;
import javafx.util.StringConverter;

public class UIDateChooser extends DatePicker {

	/** Data field */
	private String pattern = "yyyy-MM-dd";
	private static LocalDate ld = LocalDate.now();
	private DateTimeFormatter dtf = DateTimeFormatter.ofPattern(pattern);

	/** Data field */
	public UIDateChooser() {
		super(ld);
		initProperties();
	}// c'tor

	private void initProperties() {

		setEditable(false);
		setPrefWidth(110);
		setShowWeekNumbers(true);

		StringConverter<LocalDate> converter = new StringConverter<LocalDate>() {

			@Override
			public String toString(LocalDate date) {
				if (date != null) {
					return dtf.format(date);
				} else {
					return "";
				}
			}

			@Override
			public LocalDate fromString(String string) {
				if (string != null && !string.isEmpty()) {
					return LocalDate.parse(string, dtf);
				} else {
					return null;
				}
			}
		};

		/*
		 * Common use of the Callback interface in FX, mostly in use with
		 * Lambda. <V, T> : V-argument, T-return type.
		 */
		Callback<DatePicker, DateCell> dayCellFactory = new Callback<DatePicker, DateCell>() {
			@Override
			public DateCell call(final DatePicker datePicker) {
				return new DateCell() {
					@Override
					public void updateItem(LocalDate item, boolean empty) {
						super.updateItem(item, empty);
						if (item.isAfter(ld)) {
							setDisable(true);
							setStyle("-fx-background-color: #E3E31A;");
						}
					}
				};
			}
		};

		ld.format(dtf);

		setDayCellFactory(dayCellFactory);// DateCell dayCellFactory;

		setConverter(converter);
		setPromptText(ld.toString());

		setTooltip(new Tooltip("Open Calendar"));
	}//

	public String getFormattedValue() {
		return this.getValue().format(dtf).toString();
	}

	public void resetDate() {
		super.getEditor().setText(LocalDate.now().format(dtf));
	}

}// UIDateChooser
