package app.financialmanager.dao;

import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;

import app.financialmanager.interfaces.daoservices.FinancialManagerDAOService;
import entities.FinancialManager;
import entities.Investor;
import entities.Lead;
import entities.Lead.LeadStatus;
import utility.entitymanager.DAOEntityManager;

public class FinancialManagerDAO implements FinancialManagerDAOService {

	@Override
	public void persistFinancialManager(FinancialManager financialManager) {
		EntityManager em = DAOEntityManager.getEntityMamager();
		EntityTransaction etx = em.getTransaction();
		try {
			etx.begin();
			em.merge(financialManager);
			etx.commit();
		} catch (Exception e) {
			em.getTransaction().rollback();
			e.printStackTrace();
		}
	}

	@Override
	public void persistInvestor(Investor investor) {
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
	public void persistLead(Lead lead) {
		EntityManager em = DAOEntityManager.getEntityMamager();
		EntityTransaction etx = em.getTransaction();
		try {
			etx.begin();
			em.merge(lead);
			etx.commit();
		} catch (Exception e) {
			em.getTransaction().rollback();
			e.printStackTrace();
		}
	}

	@Override
	public List<Lead> getLeadsList() {
		EntityManager em = DAOEntityManager.getEntityMamager();
		return em.createQuery("SELECT lead FROM Lead lead WHERE lead.leadStat = :stat")
				.setParameter("stat", LeadStatus.PENDING).getResultList();
	}

	@Override
	public List<Investor> getInvestorsList() {
		EntityManager em = DAOEntityManager.getEntityMamager();
		return em.createQuery("SELECT investor FROM Investor investor").getResultList();
	}

}
