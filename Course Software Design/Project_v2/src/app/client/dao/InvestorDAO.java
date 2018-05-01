package app.client.dao;

import java.util.List;
import java.util.Random;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;

import app.client.interfaces.daoservices.InvestorDAOService;
import entities.Advice;
import entities.Investor;
import utility.entitymanager.DAOEntityManager;

public class InvestorDAO implements InvestorDAOService {

	@Override
	public void persistIvestor(Investor investor) {

		EntityManager em = DAOEntityManager.getEntityMamager();
		EntityTransaction etx = em.getTransaction();
		try {
			etx.begin();
			em.merge(investor);
			etx.commit();
		} catch (Exception e) {
			em.getTransaction().rollback();
			e.printStackTrace();
		}
	}

	@Override
	public Advice getAdvice() {
		EntityManager em = DAOEntityManager.getEntityMamager();
		Advice advice = null;
		List<Advice> l = em.createQuery("SELECT advice FROM Advice advice").getResultList();

		if (!l.isEmpty())
			advice = l.get((new Random()).nextInt(l.size()));
		EntityTransaction etx = em.getTransaction();
		try {
			etx.begin();
			em.refresh(advice);
			etx.commit();
		} catch (Exception e) {
			em.getTransaction().rollback();
			e.printStackTrace();
		}
		return advice;
	}
}
