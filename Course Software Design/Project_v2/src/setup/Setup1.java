package setup;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import entities.Investor;
import entities.Lead;
import entities.Lead.LeadStatus;
import entities.Person;
import entities.Person.Gender;
import entities.Advice;
import entities.Client;
import entities.FinancialManager;
import entities.Portfolio;
import entities.UserFinancialManager;
import entities.UserInvestor;
import utility.mydateandtime.MyDateTime;

public class Setup1 {

	public static void main(String args[]) {

		EntityManagerFactory emf = Persistence.createEntityManagerFactory("Project_v2");
		EntityManager em = emf.createEntityManager();

		try {
			em.getTransaction().begin();

			createAdminInvestorUser1(em);
			createAdminInvestorUser2(em);
			createAdminFinancialManagerUser(em);
			createLead1(em);
			createLead2(em);
			createLead3(em);

			em.getTransaction().commit();

		} catch (Exception e) {
			em.getTransaction().rollback();
			e.printStackTrace();
		} finally {
			em.close();
		}
		System.out.println("+++++++++++++++++ SETUP DONE +++++++++++++++++");
	}

	public static void createAdminInvestorUser1(EntityManager em) {

		Portfolio portfolio = new Portfolio();
		Investor investor = new Investor("Admin1", "Admin1", "Afeka", Person.Gender.MALE, "01/01/01",
				Client.BankName.DISKONT, "02788936-25", "Safe portfolio, Tech stocks",
				MyDateTime.getCurrentDateTime(), Investor.InvestorStatus.ACTIVE, portfolio);

		String password = "admin";
		String passwordHash = org.apache.commons.codec.digest.DigestUtils.sha256Hex(password);

		UserInvestor userInvestor = new UserInvestor("Admin1", passwordHash, investor);

		em.persist(investor);
		em.persist(userInvestor);
	}

	public static void createAdminInvestorUser2(EntityManager em) {

		Portfolio portfolio = new Portfolio();
		Investor investor = new Investor("Admin2", "Admin2", "Afeka", Person.Gender.MALE, "01/01/01",
				Client.BankName.DISKONT, "02788936-25", "Safe portfolio, Bio stocks",
				MyDateTime.getCurrentDateTime(), Investor.InvestorStatus.ACTIVE, portfolio);

		String password = "admin";
		String passwordHash = org.apache.commons.codec.digest.DigestUtils.sha256Hex(password);

		UserInvestor userInvestor = new UserInvestor("Admin2", passwordHash, investor);

		em.persist(investor);
		em.persist(userInvestor);
	}

	public static void createAdminFinancialManagerUser(EntityManager em) {

		Advice advice = new Advice("Admin", "Admin\nAdmin\nAdmin\nAdmin");
		FinancialManager financialManager = new FinancialManager("Admin", "Admin", "Afeka", Person.Gender.MALE,
				"01/01/01", advice);

		String password = "admin";
		String passwordHash = org.apache.commons.codec.digest.DigestUtils.sha256Hex(password);

		UserFinancialManager userFinancialManager = new UserFinancialManager("Admin", passwordHash, financialManager);

		em.persist(financialManager);
		em.persist(userFinancialManager);
	}

	public static void createLead1(EntityManager em) {

		Lead lead = new Lead();
		lead.setFirstName("Lead");
		lead.setLastName("Lead");
		lead.setAddress("Afeka Leads 000");
		lead.setGender(Gender.MALE);
		lead.setDob("01/01/01");

		lead.setBankName(Client.BankName.LEUMI);
		lead.setBankAccount("00-000000000");
		lead.setJosDate(MyDateTime.getCurrentDateTime());
		lead.setIntensionsDeclaration("Lead\nLad\nLead\nLead");

		lead.setLeadStat(LeadStatus.PENDING);

		em.persist(lead);
	}

	public static void createLead2(EntityManager em) {

		Lead lead = new Lead();
		lead.setFirstName("Lead");
		lead.setLastName("Lead");
		lead.setAddress("Afeka Leads 000");
		lead.setGender(Gender.MALE);
		lead.setDob("01/01/01");

		lead.setBankName(Client.BankName.HAPOALIM);
		lead.setBankAccount("00-000000000");
		lead.setJosDate(MyDateTime.getCurrentDateTime());
		lead.setIntensionsDeclaration("Lead\nLad\nLead\nLead");

		lead.setLeadStat(LeadStatus.PENDING);

		em.persist(lead);
	}

	public static void createLead3(EntityManager em) {

		Lead lead = new Lead();
		lead.setFirstName("Lead");
		lead.setLastName("Lead");
		lead.setAddress("Afeka Leads 000");
		lead.setGender(Gender.MALE);
		lead.setDob("01/01/01");

		lead.setBankName(Client.BankName.HOZAR_HAHAYAL);
		lead.setBankAccount("00-000000000");
		lead.setJosDate(MyDateTime.getCurrentDateTime());
		lead.setIntensionsDeclaration("Lead\nLad\nLead\nLead");

		lead.setLeadStat(LeadStatus.PENDING);

		em.persist(lead);
	}
}
