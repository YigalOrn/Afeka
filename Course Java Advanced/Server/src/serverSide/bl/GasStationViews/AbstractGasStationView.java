package serverSide.bl.GasStationViews;

import serverSide.bl.GasStationEvents.GasStationEventsListener;


public interface AbstractGasStationView {

	void registerListener(GasStationEventsListener uiEventListener);
	void getException(Exception e);

}
