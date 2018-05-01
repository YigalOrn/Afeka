package servlet_distantClient;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "ParamError", displayName = "Parameters Error", urlPatterns = "/ParamError")
public class ParametersError extends HttpServlet {
	private static final long serialVersionUID = 1L;

	@Override
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		response.setContentType("text/html;charset=UTF-8");

		PrintWriter out = response.getWriter();

		try {

			out.write("<html><head>");
			out.write("<title>Server Context result</title></head>");
			out.write("<body>");

			out.write("<h1><font color ="
					+ "black"
					+ "><b>Some Parameters are missing or incorrect!<br>Please try again<br>You will be transfered in 10 sec...</b></font></h1>");

			out.write("</body></html>");

			response.setHeader(
					"Refresh",
					"10; URL=http://localhost:8080/ZEx_2_v1.4_Client_FXBrowserEmbedded/AddNewCar.html");

		} finally {
			out.close();
		}

	}

	@Override
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
