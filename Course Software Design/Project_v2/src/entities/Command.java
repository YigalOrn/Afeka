/*
 * @Temporal(TemporalType.DATE)
	private Date dateAndTime;

 * */

package entities;

import java.io.Serializable;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Command
 *
 */
@Entity
public class Command implements Serializable {

	public static enum CommandType {
		ASK, BID
	}

	public static enum CommandStatus {
		COMMITTED, PERFORMED, CANCELED
	}

	@Id
	private long commandId;
	private String stockName;
	private String stockId;
	private int amount;
	private double limitPrice;
	private CommandType type;
	private CommandStatus commandStatus;
	private Double averagePrice;
	private String dateTime;

	private static final long serialVersionUID = 1L;

	public Command() {
		super();
	}

	public Command(long commandId, String stockName, String stockId, int amount, double limitPrice, CommandType type,
			CommandStatus commandStatus, Double averagePrice, String dateTime) {
		super();

		setCommandId(commandId);
		setStockName(stockName);
		setStockId(stockId);
		setAmount(amount);
		setLimitPrice(limitPrice);
		setType(type);
		setCommandStatus(commandStatus);
		setAveragePrice(averagePrice);
		setDateTime(dateTime);
	}

	public long getCommandId() {
		return commandId;
	}

	public void setCommandId(long commandId) {
		this.commandId = commandId;
	}

	public String getStockName() {
		return stockName;
	}

	public void setStockName(String stockName) {
		this.stockName = stockName;
	}

	public String getStockId() {
		return stockId;
	}

	public void setStockId(String stockId) {
		this.stockId = stockId;
	}

	public int getAmount() {
		return amount;
	}

	public void setAmount(int amount) {
		this.amount = amount;
	}

	public double getLimitPrice() {
		return limitPrice;
	}

	public void setLimitPrice(double limitPrice) {
		this.limitPrice = limitPrice;
	}

	public Double getAveragePrice() {
		return averagePrice;
	}

	public void setAveragePrice(Double averagePrice) {
		this.averagePrice = averagePrice;
	}

	public String getDateTime() {
		return dateTime;
	}

	public void setDateTime(String dateTime) {
		this.dateTime = dateTime;
	}

	public CommandType getType() {
		return type;
	}

	public void setType(CommandType type) {
		this.type = type;
	}

	public CommandStatus getCommandStatus() {
		return commandStatus;
	}

	public void setCommandStatus(CommandStatus commandStatus) {
		this.commandStatus = commandStatus;
	}

	@Override
	public boolean equals(Object obj) {

		if (!(obj instanceof Command)) {
			return false;
		} else {
			Command other = (Command) obj;
			if (this.commandId == other.commandId) {
				return true;
			} else {
				return false;
			}
		}
	}

	@Override
	public String toString() {

		return this.getStockId() + " " + this.getCommandId();
	}
}
