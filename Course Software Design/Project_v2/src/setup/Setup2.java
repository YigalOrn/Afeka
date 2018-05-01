package setup;

import stockexchange.client.StockCommandType;
import stockexchange.client.StockExchangeClient;
import stockexchange.client.StockExchangeClientFactory;
import stockexchange.client.StockExchangeCommand;

public class Setup2 {

	public static void main(String[] args) throws Exception {

		StockExchangeClient stockExchangeClient = StockExchangeClientFactory.getClient();
		/*
		 * StockExchangeCommand( StockCommandType type, String invokerId,
		 * String,stockId, double minPrice, double maxPrice, int amount )
		 */

		stockExchangeClient
				.sendCommand(new StockExchangeCommand(StockCommandType.ASK, "client1", "GOOG", 15.0, 15.0, 20));

		stockExchangeClient
				.sendCommand(new StockExchangeCommand(StockCommandType.ASK, "client2", "FB", 500.5, 1000, 10));

		stockExchangeClient
				.sendCommand(new StockExchangeCommand(StockCommandType.ASK, "client1", "GOOG", 5.12, 15.0, 30));

		stockExchangeClient
				.sendCommand(new StockExchangeCommand(StockCommandType.ASK, "client3", "IBM", 65.45, 70.9, 12));

		stockExchangeClient
				.sendCommand(new StockExchangeCommand(StockCommandType.ASK, "client2", "ORCL", 90.5, 1500, 1));

		stockExchangeClient.close();

	}
}
