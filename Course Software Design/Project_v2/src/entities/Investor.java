package entities;

import entities.Client;
import entities.Command.CommandType;

import java.io.Serializable;
import java.util.Map;
import java.util.Set;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Investor
 *
 */
@Entity
public class Investor extends Client implements Serializable {

	public static enum InvestorStatus {
		ACTIVE, CLOSED
	}

	private InvestorStatus investorStat;
	private String LastFeeCharge;// should be init with join date
	@OneToOne(cascade=CascadeType.ALL)
	private Portfolio portfolio;

	private static final long serialVersionUID = 1L;

	public Investor() {
		super();
	}

	public Investor(String firstName, String lastName, String address, Gender gender, String dob, BankName bankName,
			String bankAccount, String intensionsDeclaration, String josDate, InvestorStatus investorStat,
			Portfolio portfolio) {
		super();
		setFirstName(firstName);
		setLastName(lastName);
		setAddress(address);
		setGender(gender);
		setDob(dob);
		setBankName(bankName);
		setBankAccount(bankAccount);
		setIntensionsDeclaration(intensionsDeclaration);
		setJosDate(josDate);
		setInvestorStat(investorStat);
		setPortfolio(portfolio);
		setLastFeeCharge(josDate);
	}

	public Portfolio getPortfolio() {
		return portfolio;
	}

	public void setPortfolio(Portfolio portfolio) {
		this.portfolio = portfolio;
	}

	public InvestorStatus getInvestorStat() {
		return investorStat;
	}

	public void setInvestorStat(InvestorStatus investorStat) {
		this.investorStat = investorStat;
	}

	public String getLastFeeCharge() {
		return LastFeeCharge;
	}

	public void setLastFeeCharge(String lastFeeCharge) {
		LastFeeCharge = lastFeeCharge;
	}

	public boolean checkCommandAgainstAssets(Command command) {

		if (command.getType() == CommandType.ASK) {
			int currAmount = portfolio.checkAssetsByStockId(command.getStockId());
			if (currAmount >= command.getAmount()) {
				return true;
			} else {
				return false;
			}
		} else {
			return true;
		}
	}

	public void addCommand(Command command) {
		portfolio.addCommand(command);
	}

	public Set<Command> getCommands() {
		return portfolio.getCommands();
	}

	public Map<String, Integer> getAssets() {
		return portfolio.getAssets();
	}

}
