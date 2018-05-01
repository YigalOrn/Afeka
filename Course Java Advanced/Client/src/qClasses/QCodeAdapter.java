package qClasses;

import java.util.ArrayList;

import qClasses.QMessage;

public abstract class QCodeAdapter implements QCode {

	public QCodeAdapter() {

	}

	@Override
	public void createDataMsg(ArrayList<String> formData) {
		// TODO Auto-generated method stub

	}

	@Override
	public void readDataMsg(QMessage message) {
		// TODO Auto-generated method stub

	}

	@Override
	public void createMessageMsg(String msg) {
		// TODO Auto-generated method stub

	}

	@Override
	public void createMessageMsg(String msg, int carId) {
		// TODO Auto-generated method stub

	}

	@Override
	public void readMessageMsg(QMessage message) {
		// TODO Auto-generated method stub

	}

	@Override
	public void createPumpCountMsg() {
		// TODO Auto-generated method stub

	}

	@Override
	public void readPumpCountMsg(QMessage message) {
		// TODO Auto-generated method stub

	}

	@Override
	public void readWebServiceMsg(QMessage message) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void createWebServiceMsg(String carId) {
		// TODO Auto-generated method stub
		
	}

}
