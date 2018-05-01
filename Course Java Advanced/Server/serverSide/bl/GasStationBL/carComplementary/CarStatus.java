package serverSide.bl.GasStationBL.carComplementary;

public interface CarStatus {
	enum carState {
		FUELQUEUE, CLEANQUEUE, REFUELING, AUTOWASH, MANUALWASH, DONE, TEXTONLY
	};
}
