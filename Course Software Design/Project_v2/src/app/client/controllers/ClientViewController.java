package app.client.controllers;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Set;

import javax.swing.JOptionPane;
import javax.swing.table.DefaultTableModel;

import app.InvesmentHouseDetails;
import app.client.dao.InvestorDAO;
import app.client.interfaces.Listeners.ClientViewEventsListener;
import app.client.interfaces.daoservices.InvestorDAOService;
import app.client.views.ClientView;
import entities.Advice;
import entities.Command;
import entities.Investor;
import entities.Command.CommandStatus;
import entities.Command.CommandType;
import stockexchange.client.Stock;
import stockexchange.client.StockCommandType;
import stockexchange.client.StockExchangeClient;
import stockexchange.client.StockExchangeClientFactory;
import stockexchange.client.StockExchangeCommand;
import stockexchange.client.StockExchangeTransaction;
import utility.mydateandtime.MyDateTime;

public class ClientViewController implements ClientViewEventsListener {

	private final ClientView clientView;
	private final Investor investor;
	private final InvestorDAOService investorDAO;
	private final StockExchangeClient stockExchangeClient;

	public ClientViewController(Investor model, ClientView view) {
		investor = model;
		clientView = view;
		clientView.registerListener(this);

		investorDAO = new InvestorDAO();
		stockExchangeClient = StockExchangeClientFactory.getClient();
	}

	@Override
	public synchronized void executeCommand(String stockId, int amount, double limitPrice, String type) {

		clientView.freezeCommandForm();
		clientView.showCommandProgressBar();

		String dateTime = MyDateTime.getCurrentDateTime();
		Stock stock = stockExchangeClient.getQuote(stockId);
		String stat = null;
		Long commandId = null;

		if (stock != null) {

			Command command = new Command(-1, stock.getName(), stockId, amount, limitPrice,
					(type.equalsIgnoreCase("ASK") ? CommandType.ASK : CommandType.BID), CommandStatus.COMMITTED, null,
					dateTime);

			if (investor.checkCommandAgainstAssets(command)) {

				switch (type) {
				case "ASK":
					commandId = stockExchangeClient.sendCommand(new StockExchangeCommand(StockCommandType.ASK,
							InvesmentHouseDetails.INVESTMENTHOUSEID, stockId, limitPrice, Double.MAX_VALUE, amount));
					break;
				case "BID":
					commandId = stockExchangeClient.sendCommand(new StockExchangeCommand(StockCommandType.BID,
							InvesmentHouseDetails.INVESTMENTHOUSEID, stockId, 0, limitPrice, amount));
					break;
				}
				command.setCommandId(commandId.longValue());
				investor.addCommand(command);

				investorDAO.persistIvestor(investor);

				clientView.clearCommandForm();
				stat = "command commited";

			} else {
				stat = "you dont have this shares: type or amount";
			}
		} else {
			stat = "no such stock id";
		}
		clientView.unFreezeCommandForm();
		clientView.hideCommandProgressBar();
		clientView.showCommandStat(stat);
	}

	@Override
	public synchronized void executeViewWindowIsClosing() {
		try {
			stockExchangeClient.close();
			JOptionPane.showMessageDialog(null, "# You Made A Furtune Today #");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public synchronized void executeReportRequest() {

		checkCommandsUpdates();
		double portfolioValue = calcPortfolioCurrValue();
		clientView.refreshReport(investor.getCommands(), portfolioValue);
	}

	@Override
	public void executeAdviceRequest() {
		Advice advice = investorDAO.getAdvice();
		clientView.setAdvice(advice);
	}

	@Override
	public synchronized void executeTickersUpdateRequest(DefaultTableModel tickersModel) {

		String arrowUp = "\u2191";
		String arrowDown = "\u2193";
		boolean found = false;

		List<Stock> freshTickers = new ArrayList<Stock>();
		List<Stock> newTickers = new ArrayList<Stock>();

		Calendar cal = Calendar.getInstance();
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");

		stockExchangeClient.getStocksId().stream().map(id -> stockExchangeClient.getQuote(id))
				.forEach(s -> freshTickers.add(s));

		for (Stock freshStock : freshTickers) {
			for (int i = 0; i < tickersModel.getRowCount(); i++) {
				if (((String) tickersModel.getValueAt(i, 0)).equalsIgnoreCase(freshStock.getId())) {

					double oldQuote;
					double newQuote = freshStock.getQuote();

					try {
						String s = ((String) tickersModel.getValueAt(i, 2)).split(" ")[0];
						oldQuote = Double.parseDouble(s.trim());
					} catch (ClassCastException e) {
						oldQuote = (double) tickersModel.getValueAt(i, 2);
					}

					if (oldQuote > newQuote) {
						tickersModel.setValueAt(arrowDown, i, 3);
					} else if (oldQuote < newQuote) {
						tickersModel.setValueAt(arrowUp, i, 3);
					}

					tickersModel.setValueAt(newQuote, i, 2);
					tickersModel.setValueAt(sdf.format(cal.getTime()), i, 4);
					found = true;
					break;
				}
			}
			if (!found)
				newTickers.add(freshStock);
			found = false;
		}

		for (Stock freshStock : newTickers) {
			// Adds to the end of model!
			tickersModel.addRow(new Object[] { freshStock.getId(), freshStock.getName(), freshStock.getQuote(), "",
					sdf.format(cal.getTime()) });
		}
	}

	@Override
	public void executeTransactionsrequestForCommand(long cid) {

		List<StockExchangeTransaction> l = stockExchangeClient.getTransactionsForCommand(cid);
		if (l != null)
			clientView.setTransactionsForCommand(l);
	}

	private void checkCommandsUpdates() {

		int amount;
		int total;
		double averagePrice;

		Set<Command> commandsSet = investor.getCommands();
		Map<String, Integer> assets = investor.getAssets();

		for (Command command : commandsSet) {

			if (command.getCommandStatus() == Command.CommandStatus.COMMITTED) {

				List<StockExchangeTransaction> stListForCommand = stockExchangeClient
						.getTransactionsForCommand(command.getCommandId());

				if (!stListForCommand.isEmpty()) {

					amount = command.getAmount();
					total = 0;
					averagePrice = 0;

					for (StockExchangeTransaction st : stListForCommand) {
						total += st.getActualAmount();
						averagePrice += st.getActualPrice();
					}

					if (total == amount) {
						command.setCommandStatus(CommandStatus.PERFORMED);
						averagePrice /= stListForCommand.size();
						averagePrice = ((int) (averagePrice * 1000)) / 1000.0;
						command.setAveragePrice(averagePrice);

						Integer temp;
						int tot;
						if (command.getType() == Command.CommandType.BID) {

							if (assets.containsKey(command.getStockId())) {
								temp = assets.get(command.getStockId());
								tot = temp.intValue() + amount;
								assets.put(command.getStockId(), new Integer(tot));
							} else {
								assets.put(command.getStockId(), new Integer(amount));
							}
						} else {

							temp = assets.get(command.getStockId());
							tot = temp.intValue() - amount;
							assets.put(command.getStockId(), new Integer(tot));
						}
						investorDAO.persistIvestor(investor);
					}
				}
			}
		}
	}

	private double calcPortfolioCurrValue() {

		Map<String, Integer> assets = investor.getAssets();
		double profit = 0;
		for (String key : assets.keySet()) {
			profit += (assets.get(key).intValue() * stockExchangeClient.getQuote(key).getQuote());
		}
		return profit;
	}

}
