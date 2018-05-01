package clientSide.listenersInterFace;

import java.util.ArrayList;

public interface UIEventsListener {

	void submitAddCarForm(ArrayList<String> formData);

	void connectToServer(String ip, String port);

	void disconnectFromServer();
}
