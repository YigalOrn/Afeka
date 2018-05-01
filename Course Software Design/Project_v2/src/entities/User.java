package entities;

import java.io.Serializable;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: User
 *
 */
@Entity
@Inheritance(strategy = InheritanceType.TABLE_PER_CLASS)
public abstract class User implements Serializable {

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private int pm_key;
	private String username;
	private String password;

	private static final long serialVersionUID = 1L;

	public User() {
		super();
	}

	public int getPm_key() {
		return this.pm_key;
	}

	public void setPm_key(int pm_key) {
		this.pm_key = pm_key;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}
}
