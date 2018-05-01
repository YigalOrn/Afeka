/*
 * 
 * http://www.objectdb.com/java/jpa/getting/started
 * 
 * http://www.oracle.com/technetwork/articles/vasiliev-jpql-087123.html
 * 
 * http://stackoverflow.com/questions/3449719/how-to-run-an-aggregate-function-like-sum-on-two-columns-in-jpa-and-display-thei
 * 
 * http://www.objectdb.com/java/jpa/query/jpql/structure

 * http://www.objectdb.com/java/jpa/query/jpql/expression
 * 
 * */

package serverSide.dal;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import jpaEntities.CleaningService;
import jpaEntities.Profits;
import jpaEntities.Pump;

public class GasStationDbConnector_JPA extends GasStationDbConnector {

	private static GasStationDbConnector_JPA dbConnector;

	private  EntityManagerFactory emf;
	private  EntityManager em;
	private  String xmlPersistenceUnit = "ZEx_2_v1.4_Server";

	private GasStationDbConnector_JPA() {
		emf = Persistence.createEntityManagerFactory(xmlPersistenceUnit);
		em = emf.createEntityManager();
	}

	public static GasStationDbConnector_JPA getInstance() {
		if (dbConnector == null) {
			dbConnector = new GasStationDbConnector_JPA();
		}
		return dbConnector;
	}//

	@Override
	public void closeConnection() throws Exception {
		em.close();
		emf.close();

	}

	// ------------------DB Updates--------------------------
	@Override
	public synchronized void insertPumpActivity(String carId, int pumpNum,
			double pumpProfit) throws Exception {

		ldt = LocalDateTime.now();

		jpaEntities.Pump p = new Pump();

		p.setCarId(carId);
		p.setId(pumpNum);
		p.setProfit(pumpProfit);
		p.setTime(ldt.toLocalTime().format(dtfTime));
		p.setDate(ldt.toLocalDate().format(dtfDate));

		em.getTransaction().begin();

		try {
			em.persist(p);
			em.getTransaction().commit();
		} catch (Exception e) {
			e.printStackTrace();
			em.getTransaction().rollback();
		}

	}

	@Override
	public synchronized void insertCleaningActivity(String carId, double profit)
			throws Exception {

		ldt = LocalDateTime.now();

		CleaningService cs = new CleaningService();

		cs.setCarId(carId);
		cs.setProfit(profit);
		cs.setTime(ldt.toLocalTime().format(dtfTime));
		cs.setDate(ldt.toLocalDate().format(dtfDate));

		em.getTransaction().begin();

		try {
			em.persist(cs);
			em.getTransaction().commit();
		} catch (Exception e) {
			e.printStackTrace();
			em.getTransaction().rollback();
		}

	}

	// ---------------------------------------------------

	// ------------------DB Queries--------------------------
	@Override
	public synchronized HashMap<String, Object> submitSqlString(String sql,
			String jpaSql) throws Exception {

		HashMap<String, Object> hashMap = new HashMap<>();

		try {

			if (emf.isOpen()) {
				List<?> list = em.createQuery(jpaSql).getResultList();
				hashMap.put("list", list);
			} else {
				hashMap.put("list", null);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}

		return hashMap;
	}

	@Override
	public synchronized HashMap<String, Object> getTotProfits()
			throws Exception {

		HashMap<String, Object> hashMap = new HashMap<>();

		/*
		 * 
		 * make a named query!
		 */
		String s1 = "SELECT SUM(p.Profit) FROM jpaEntities.Pump p";
		String s2 = "SELECT SUM(cs.Profit) FROM jpaEntities.CleaningService cs";

		try {

			if (emf.isOpen()) {

				double d1 = (double) em.createQuery(s1).getResultList().get(0);
				double d2 = (double) em.createQuery(s2).getResultList().get(0);

				jpaEntities.Profits profits = new Profits();

				profits.setProfit(d1 + d2);

				List<jpaEntities.Profits> list = new ArrayList<>();
				list.add(profits);

				hashMap.put("list", list);

			} else {
				hashMap.put("list", null);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}

		return hashMap;
	}

	@Override
	public String getCarHistory(String carId) throws Exception {

		String ans = "";
		double d1 = 0;
		double d2 = 0;

		try {

			d1 = (double) em
					.createQuery(
							"SELECT SUM(p.Profit) FROM jpaEntities.Pump p WHERE p.CarId = '"
									+ carId + "'").getResultList().get(0);
		} catch (NullPointerException e) {

		}

		try {

			d2 = (double) em
					.createQuery(
							"SELECT SUM(cs.Profit) FROM jpaEntities.CleaningService cs WHERE cs.CarId = '"
									+ carId + "'").getResultList().get(0);

		} catch (NullPointerException e) {

		}

		if (d1 == 0 && d2 == 0) {
			ans = "Car is not in db";
		} else {
			ans += "Pump bill: " + d1 + ", Cleaning Service bill: " + d2;
		}

		return ans;

	}
	// ---------------------------------------------------

}//
