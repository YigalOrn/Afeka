package entities;

import java.io.Serializable;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: User
 *
 */
@Entity
@NamedQueries({
		@NamedQuery(name = "findPasswordHashByFinancialManagerUserName", query = "SELECT u FROM UserFinancialManager u WHERE u.username LIKE :givenUserName"), })
public class UserFinancialManager extends User implements Serializable {

	@OneToOne
	private FinancialManager financialManager;

	private static final long serialVersionUID = 1L;

	public UserFinancialManager() {
		super();
	}

	public UserFinancialManager(String username, String passwordHash, FinancialManager financialManager) {
		super();
		setUsername(username);
		setPassword(passwordHash);
		setFinancialManager(financialManager);
	}
	
	public FinancialManager getFinancialManager() {
		return financialManager;
	}

	public void setFinancialManager(FinancialManager financialManager) {
		this.financialManager = financialManager;
	}
}
