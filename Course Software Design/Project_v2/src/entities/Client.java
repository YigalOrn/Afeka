package entities;

import entities.Person;
import java.io.Serializable;
import java.lang.String;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Client
 *
 */
@Entity
public abstract class Client extends Person implements Serializable {

	public static enum BankName {
		LEUMI, HAPOALIM, HOZAR_HAHAYAL, DISKONT, BEN_LEUMI
	}

	private BankName bankName;
	private String bankAccount;
	private String intentionsDeclaration;
	private String josDate;// join or submission date;

	private static final long serialVersionUID = 1L;

	public Client() {
		super();
	}

	public BankName getBankName() {
		return bankName;
	}

	public void setBankName(BankName bankName) {
		this.bankName = bankName;
	}

	public String getBankAccount() {
		return bankAccount;
	}

	public void setBankAccount(String bankAccount) {
		this.bankAccount = bankAccount;
	}

	public String getIntensionsDeclaration() {
		return intentionsDeclaration;
	}

	public void setIntensionsDeclaration(String intensionsDeclaration) {
		this.intentionsDeclaration = intensionsDeclaration;
	}

	public String getJosDate() {
		return josDate;
	}

	public void setJosDate(String josDate) {
		this.josDate = josDate;
	}

	@Override
	public String toString() {
		return super.toString() + "\n" + String.format("Bank name:%s\nBank account:%s\nDate:%s\nDeclaration:\n%s",
				getBankName(), getBankAccount(), getJosDate(), getIntensionsDeclaration());
	}

}
