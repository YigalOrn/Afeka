package webService.blClass;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import qClasses.QConnection;
import qClasses.QMessage;
import qClasses.QCode;

public class CarHistory {

	public String getCarHistory(String carId) {

		ExecutorService executor = Executors.newSingleThreadExecutor();

		Future<String> val = executor.submit(new Callable<String>() {

			@Override
			public String call() throws Exception {

				QConnection<QMessage> conn = null;
				QMessage message = null;
				String ans = "Socket Error";

				try {

					conn = new QConnection<QMessage>("localhost", 65000);

					message = new QMessage();
					message.getMessageMap().put("code", QCode.Code.WEBSERVICE);
					message.getMessageMap().put("carId", carId);
					conn.sendData(message);
					message = conn.getData();

					ans = (String) message.getMessageMap().get("webservice");

				} catch (Exception e) {

				} finally {
					if (conn != null)
						conn.closeConnection();
				}

				return ans;

			}

		});

		try {
			return val.get();
		} catch (InterruptedException | ExecutionException e) {
			e.printStackTrace();
			return "Error";
		} finally {
			executor.shutdown();
		}

	}//

}