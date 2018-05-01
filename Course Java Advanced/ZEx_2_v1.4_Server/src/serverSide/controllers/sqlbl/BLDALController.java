/*
 * 
 * http://www.objectdb.com/api/java/jpa/Persistence
 * 
 * http://stackoverflow.com/questions/6205171/correct-way-of-making-a-singleton-a-spring-bean
 * 
 * http://stackoverflow.com/questions/15092898/spring-default-behavior-for-lazy-init
 * 
 * http://stackoverflow.com/questions/1088550/spring-how-to-call-a-method-after-bean-initialization-is-complete
 * 
 * http://www.coderanch.com/t/500009/Spring/Creating-Beans-invoking-static-factory
 * 
 * 
 * http://www.studytrails.com/frameworks/spring/spring-injection-factory-method.jsp
 * 
 * http://learningviacode.blogspot.co.il/2012/04/bean-creation-via-factory-method.html
 * 
 * 
 * 
 * 
 * */

package serverSide.controllers.sqlbl;

import java.util.HashMap;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import serverSide.bl.GasStationBL.GasStation;
import serverSide.dal.DalInterface;
import serverSide.events.sqlbl.BL3EventsListener;

public class BLDALController implements BL3EventsListener {

	/** Data fields */
	private DalInterface dbConnection;

	@SuppressWarnings("unused")
	private GasStation gasStation;

	/** C'tor */
	public BLDALController(GasStation gasStation) {

		/*
		 * 
		 * In the PPT there is a way to close resources!
		 */
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(
				"springBeanConfiguration.xml");

		// --------

		
		  dbConnection = (DalInterface) applicationContext
		  .getBean("dbHandlerJDBC");
		 

		  /*
		dbConnection = (DalInterface) applicationContext
				.getBean("dbHandlerJPA");
*/
		  
		  
		// --------

		gasStation.registerBL3Listener(this);

		((ClassPathXmlApplicationContext) applicationContext).close();

	}// c'tor

	@Override
	public void recordPumpActivity(String carId, int pumpNum, double amount)
			throws Exception {
		dbConnection.insertPumpActivity(carId, pumpNum, amount);
	}

	@Override
	public void recordCleanActivity(String carId, double profit)
			throws Exception {
		dbConnection.insertCleaningActivity(carId, profit);
	}

	@Override
	public HashMap<String, Object> submitQueryFormDbTab(String sql,
			String jpaSql) throws Exception {

		return dbConnection.submitSqlString(sql, jpaSql);
	}

	@Override
	public void closeDbConnection() throws Exception {
		dbConnection.closeConnection();
	}

	@Override
	public HashMap<String, Object> getTotProfits() throws Exception {
		return dbConnection.getTotProfits();
	}

	@Override
	public String getCarHistory(String carId) throws Exception {
		return dbConnection.getCarHistory(carId);
	}

}
