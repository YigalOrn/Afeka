package app.financialmanager.controllers;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import app.financialmanager.dao.FinancialManagerDAO;
import app.financialmanager.interfaces.Listeners.FinancialManagerViewEventsListener;
import app.financialmanager.interfaces.daoservices.FinancialManagerDAOService;
import app.financialmanager.views.FinancialManagerView;
import entities.FinancialManager;
import entities.Investor;
import entities.Lead;
import entities.Lead.LeadStatus;
import stockexchange.client.StockExchangeClient;
import stockexchange.client.StockExchangeClientFactory;
import utility.mydateandtime.MyDateTime;

public class FinancialManagerViewController implements FinancialManagerViewEventsListener {

	private final FinancialManagerView financialManagerView;
	private final FinancialManager financialManager;
	private final FinancialManagerDAOService financialManagerDAO = new FinancialManagerDAO();
	private final StockExchangeClient stockExchangeClient = StockExchangeClientFactory.getClient();
	private Lead lastLead = null;

	public FinancialManagerViewController(FinancialManager model, FinancialManagerView view) {
		financialManager = model;
		financialManagerView = view;
		financialManagerView.registerListener(this);
	}

	@Override
	public void executeComposeReport(double feeVal) {
		long diff = -1;
		String lastFeeCharge = null;
		List<Investor> investorsList = financialManagerDAO.getInvestorsList();
		List<Investor> investorsToChargeList = new ArrayList<>();
		for (Investor investor : investorsList) {
			lastFeeCharge = investor.getLastFeeCharge();
			diff = MyDateTime.calcDateYearDiff(MyDateTime.getCurrentDateTime(), lastFeeCharge);
			if (diff > 0) {
				investorsToChargeList.add(investor);
				investor.setLastFeeCharge(MyDateTime.getCurrentDateTime());
				financialManagerDAO.persistInvestor(investor);
			}
		}
		financialManagerView.diaplayChargeReport(investorsToChargeList);
	}

	@Override
	public void executeAdviceSubmited(String subject, String body) {
		financialManager.changeAdvice(subject, body);
		financialManagerDAO.persistFinancialManager(financialManager);
	}

	@Override
	public void executeViewWindowIsClosing() {
		try {
			stockExchangeClient.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void executeGetLeadRequest() {
		List<Lead> leadList = financialManagerDAO.getLeadsList();
		if (!leadList.isEmpty()) {
			financialManagerView.unFreezeLeadAStatusButtons();
			lastLead = leadList.get((new Random()).nextInt(leadList.size()));
			financialManagerView.displayLead(lastLead);
		}
	}

	@Override
	public void executeChangeLeadStatus(LeadStatus leadStatus) {
		lastLead.setLeadStat(leadStatus);
		financialManagerDAO.persistLead(lastLead);
		lastLead = null;
		financialManagerView.freezeLeadButtons();
	}

}
