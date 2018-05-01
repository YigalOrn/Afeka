/*
 * 
 * Map structure:
 * 
 * to server - --> "code",Code.PUMPCOUNT
 * 
 * from server - "code",Code.PUMPCOUNT --> "pumpcount", int
 * 
 * -----------------------------------------
 * 
 * to server - "code",Code.Data --> ["carId"="carId",
 * "numOfliters"="numOfLiters", "pumpNum"="pumpNum", "wantsCleaning"="true"]
 * 
 * from server - "code",Code.MESSAGE --> ["message", String]
 */

package qClasses;

import java.util.ArrayList;

import qClasses.QMessage;

public interface QCode {

	enum Code {
		DATA, MESSAGE, SLIDERRESET, PUMPCOUNT, CLIENT, SERVLET, WEBSERVICE
	};

	// ---------------
	void createDataMsg(ArrayList<String> formData);

	void readDataMsg(QMessage message);

	void createMessageMsg(String msg);

	void createMessageMsg(String msg, int carId);

	void readMessageMsg(QMessage message);

	void createPumpCountMsg();

	void readPumpCountMsg(QMessage message);

	void readWebServiceMsg(QMessage message);
	
	void createWebServiceMsg(String carId);
	
	// ---------------

}//

