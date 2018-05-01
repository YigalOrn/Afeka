package entities;

import java.io.Serializable;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: Advice
 *
 */
@Entity
public class Advice implements Serializable {

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private int pm_key;
	private String subject;
	@Column(columnDefinition = "VARCHAR(1337)")
	private String body;

	private static final long serialVersionUID = 1L;

	public Advice() {
		super();
	}

	public Advice(String subject, String body) {
		super();
		setSubject(subject);
		setBody(body);
	}

	public int getPm_key() {
		return this.pm_key;
	}

	public void setPm_key(int pm_key) {
		this.pm_key = pm_key;
	}

	public String getSubject() {
		return subject;
	}

	public void setSubject(String subject) {
		this.subject = subject;
	}

	public String getBody() {
		return body;
	}

	public void setBody(String body) {
		this.body = body;
	}

	@Override
	public String toString() {
		return getSubject() + "\n" + getBody();
	}

}
