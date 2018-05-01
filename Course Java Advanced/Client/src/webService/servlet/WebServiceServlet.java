package webService.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.rmi.RemoteException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import webService.service.CarHistoryStub;

@WebServlet(name = "WebServiceServlet", displayName = "Web Service Servlet", urlPatterns = "/WebServiceServlet")
public class WebServiceServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	@Override
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		response.setContentType("text/html;charset=UTF-8");
		PrintWriter out = response.getWriter();

		try {

			String ans = callCarHistoryWebService(request.getParameter("carId"));

			out.write("<html><head>");
			out.write("<title>Server Context result</title></head>");
			out.write("<body>");

			out.write("<h1><font color =" + "black" + ">" + ans
					+ "</font></h1>");

			out.write("</body></html>");

			response.setHeader(
					"Refresh",
					"10; URL=http://localhost:8080/ZEx_2_v1.4_Client_FXBrowserEmbedded/CarHistoryMenu.html");

		} finally {
			out.close();
		}

	}

	@Override
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

	private String callCarHistoryWebService(String carId) {
		/*
		 * Using a web-service to encapsulate the logic.
		 */

		CarHistoryStub service;
		String ans = "Web Service Error";

		try {
			service = new CarHistoryStub();
			CarHistoryStub.GetCarHistory gh = new CarHistoryStub.GetCarHistory();
			gh.setCarId(carId);

			ans = service.getCarHistory(gh).get_return();

		} catch (RemoteException e) {
			e.printStackTrace();
		}

		return ans;

	}
}