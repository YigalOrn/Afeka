package app.client.dao;

import java.util.List;

import javax.persistence.EntityManager;

import app.auth.interfaces.ClientAuthDAOService;
import entities.Investor;
import entities.UserInvestor;
import utility.entitymanager.DAOEntityManager;

public class ClientAuthDAO implements ClientAuthDAOService {

	@Override
	public String getPassworHashByUserName(String username) {

		EntityManager em = DAOEntityManager.getEntityMamager();

		List<UserInvestor> userList = em.createNamedQuery("findPasswordHashByInvestorUserName")
				.setParameter("givenUserName", username).getResultList();

		for (UserInvestor u : userList) {
			return u.getPassword();
		}
		return null;

	}

	@Override
	public Investor getEntityByInvestorUserName(String username) {
		
		EntityManager em = DAOEntityManager.getEntityMamager();
		
		List<UserInvestor> userList = em.createNamedQuery("findPasswordHashByInvestorUserName")
				.setParameter("givenUserName", username).getResultList();

		for (UserInvestor u : userList) {
			return u.getInvestor();
		}
		return null;
	}

}
