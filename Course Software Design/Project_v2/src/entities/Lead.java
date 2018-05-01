package entities;

import entities.Client;

import java.io.Serializable;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: Lead
 *
 */
@Entity
public class Lead extends Client implements Serializable {

	public static enum LeadStatus {
		PENDING, APPROVED, DISAPPROVED
	};

	private LeadStatus leadStat;
	// private long specialNumber;//used as pm key

	private static final long serialVersionUID = 1L;

	public Lead() {
		super();
	}

	public LeadStatus getLeadStat() {
		return leadStat;
	}

	public void setLeadStat(LeadStatus leadStat) {
		this.leadStat = leadStat;
	}

	@Override
	public String toString() {
		return super.toString();
	}

}
