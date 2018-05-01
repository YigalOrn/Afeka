package serverSide.bl.GasStationExceptions;

@SuppressWarnings("serial")
public class MainFuelStockEmptyException extends Exception {
	public float amount;

	public MainFuelStockEmptyException(float amount) {
		super("Main Fuel Stock is Empty Fueled only:" + amount + " Liters");
		this.amount = amount;
	}
}
