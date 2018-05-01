package clientSide.bl.car.carComplementary;

public interface CarStatus {
	enum carState {
		FUELQUEUE, CLEANQUEUE, REFUELING, AUTOWASH, MANUALWASH, DONE, TEXTONLY
	};
}
