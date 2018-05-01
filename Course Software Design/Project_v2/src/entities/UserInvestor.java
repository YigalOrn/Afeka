package entities;

import java.io.Serializable;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: User
 *
 */
@Entity
@NamedQueries({
		@NamedQuery(name = "findPasswordHashByInvestorUserName", query = "SELECT u FROM UserInvestor u WHERE u.username LIKE :givenUserName"), })
public class UserInvestor extends User implements Serializable {

	@OneToOne
	private Investor investor;

	private static final long serialVersionUID = 1L;

	public UserInvestor() {
		super();
	}

	public UserInvestor(String username, String passwordHash, Investor investor) {
		super();
		setUsername(username);
		setPassword(passwordHash);
		setInvestor(investor);
	}

	public Investor getInvestor() {
		return investor;
	}

	public void setInvestor(Investor investor) {
		this.investor = investor;
	}
}
