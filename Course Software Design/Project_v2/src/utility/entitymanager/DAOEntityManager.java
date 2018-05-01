package utility.entitymanager;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

public class DAOEntityManager {

	private static DAOEntityManager daoEntityManager = new DAOEntityManager();
	private EntityManagerFactory emf;
	private String persistenceUnitName = "Project_v2";

	private DAOEntityManager() {
		emf = Persistence.createEntityManagerFactory(persistenceUnitName);
	}

	public static EntityManager getEntityMamager() {
		return daoEntityManager.emf.createEntityManager();
	}
}