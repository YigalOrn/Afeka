package app.financialmanager.dao;

import java.util.List;

import javax.persistence.EntityManager;

import app.auth.interfaces.FinancialManagerAuthDAOService;
import entities.FinancialManager;
import entities.UserFinancialManager;
import utility.entitymanager.DAOEntityManager;

public class FinancialManagerAuthDAO implements FinancialManagerAuthDAOService {

	@Override
	public String getPassworHashByUserName(String userName) {

		EntityManager em = DAOEntityManager.getEntityMamager();

		List<UserFinancialManager> userList = em.createNamedQuery("findPasswordHashByFinancialManagerUserName")
				.setParameter("givenUserName", userName).getResultList();

		for (UserFinancialManager u : userList) {
			return u.getPassword();
		}
		return null;

	}

	@Override
	public FinancialManager getEntityByFinancialManagerUserName(String userName) {

		EntityManager em = DAOEntityManager.getEntityMamager();

		List<UserFinancialManager> userList = em.createNamedQuery("findPasswordHashByFinancialManagerUserName")
				.setParameter("givenUserName", userName).getResultList();

		for (UserFinancialManager u : userList) {
			return u.getFinancialManager();
		}
		return null;
	}

}
