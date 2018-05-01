/*
 * http://www.coderanch.com/t/357276/Servlets/java/Servlet-Redirect-time-delay
 * http://crunchify.com/how-to-start-stop-apache-tomcat-server-via-command-line-setup-as-windows-service/
 * http://stackoverflow.com/questions/26061189/how-to-forward-from-servlet-to-another-servlet-located-in-separate-package
 * 
 * */

package servlet_distantClient;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import qClasses.QCode.Code;
import qClasses.QConnection;
import qClasses.QMessage;

@WebServlet(name = "GasStationAddNewCarServlet", displayName = "GasStation Add New Car Servlet", urlPatterns = "/GasStationAddNewCarServlet")
public class GasStationAddNewCarServlet extends HttpServlet {

	private static final long serialVersionUID = 1L;
	private ExecutorService executor;

	@Override
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

	@Override
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		ArrayList<String> param = collectPageParameters(request);
		if (param != null) {

			/*
			 * 
			 * KK PPT, slide 43! , Check on couple of computers simultaneously
			 * to see if sync is needed!!!
			 * 
			 * 
			 * Check parameters here , to give web client a feedback!
			 */

			String[] newParam = param.toArray(new String[0]);

			String val = submitNewParamsToGasStationServer(newParam);

			if (val != null) {
				getServletContext().setAttribute("state", val);
			} else {
				getServletContext().setAttribute("state",

				"Connection problems, try later");
			}

			getServletContext().getRequestDispatcher("/ReturnState").forward(
					request, response);

		} else {

			getServletContext().getRequestDispatcher("/ParametersError")
					.forward(request, response);
		}

	}

	@Override
	public void init() throws ServletException {
		executor = Executors.newCachedThreadPool();
	}

	@Override
	public void destroy() {
		executor.shutdownNow();
	}

	private ArrayList<String> collectPageParameters(HttpServletRequest request) {

		ArrayList<String> param = new ArrayList<>(4);

		String carIdStr = request.getParameter("carId");
		if (carIdStr.isEmpty()) {
			return null;
		} else {
			param.add(0, carIdStr);
		}
		String wantsCleaningStr = request.getParameter("wantsCleaning");
		if (wantsCleaningStr != null) {
			param.add(1, "true");
		} else {
			param.add(1, "");
		}

		String numOfLitersStr = request.getParameter("numOfLiters");
		param.add(2, numOfLitersStr);

		String pumpNumStr = request.getParameter("pumpNum");
		param.add(3, pumpNumStr);

		return param;
	}

	private String submitNewParamsToGasStationServer(String[] param) {

		Future<String> val = executor.submit(new Callable<String>() {

			@Override
			public String call() throws Exception {

				QConnection<QMessage> conn = null;
				QMessage message = null;

				try {
					conn = new QConnection<QMessage>("localhost", 65000);

					message = new QMessage();

					message.getMessageMap().put("code", Code.DATA);
					message.getMessageMap().put("subcode", Code.SERVLET);
					message.getMessageMap().put("data", param);

					conn.sendData(message);

					message = conn.getData();

				} catch (Exception e) {

				} finally {
					if (conn != null)
						conn.closeConnection();
				}

				return (String) message.getMessageMap().get("message");
			}
		});

		try {
			return val.get();
		} catch (InterruptedException | ExecutionException e) {
			e.printStackTrace();
			return "Problems executig thread";
		}

	}

}//
