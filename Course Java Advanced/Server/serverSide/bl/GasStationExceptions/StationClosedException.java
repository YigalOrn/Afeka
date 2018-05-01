package serverSide.bl.GasStationExceptions;

@SuppressWarnings("serial")
public class StationClosedException extends Exception {
	 public StationClosedException() {
	        super("The Station is Closed");
	    }
}
