package serverSide.events.serverbl;

import serverSide.bl.GasStationBL.Car;

public interface BL2EventsListener {

	void reqeustCloseServer();

	boolean getIsServerOnline();

	void ReportToServerClient(Car car, String msg);

}//
