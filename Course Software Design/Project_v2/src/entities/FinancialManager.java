package entities;

import java.io.Serializable;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: FinancialManager
 *
 */
@Entity
public class FinancialManager extends Person implements Serializable {

	@OneToOne(cascade=CascadeType.ALL)
	private Advice advice;

	private static final long serialVersionUID = 1L;

	public FinancialManager() {
		super();
	}

	public FinancialManager(String firstName, String lastName, String address, Gender gender, String dob,
			Advice advice) {
		super();
		setFirstName(firstName);
		setLastName(lastName);
		setAddress(address);
		setGender(gender);
		setDob(dob);
		setAdvice(advice);
	}

	public Advice getAdvice() {
		return advice;
	}

	public void setAdvice(Advice advice) {
		this.advice = advice;
	}

	public void changeAdvice(String subject, String body) {
		advice.setSubject(subject);
		advice.setBody(body);
	}
}
