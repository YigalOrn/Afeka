package qClasses;

import java.io.Serializable;
import java.util.HashMap;

public class QMessage implements Serializable {

	/** Data fields */
	private static final long serialVersionUID = 1L;
	private HashMap<String, Object> messageMap;

	/** C'tor */
	public QMessage() {
		messageMap = new HashMap<>();
	}// c'tor

	public HashMap<String, Object> getMessageMap() {
		return messageMap;
	}

}//
