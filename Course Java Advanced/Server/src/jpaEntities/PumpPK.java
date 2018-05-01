package jpaEntities;

import java.io.Serializable;
import java.lang.String;

/**
 * ID class for entity: Pump
 *
 */ 
public class PumpPK  implements Serializable {   
   
	         
	private int Id;         
	private String Time;
	private static final long serialVersionUID = 1L;

	public PumpPK() {}

	

	public int getId() {
		return this.Id;
	}

	public void setId(int Id) {
		this.Id = Id;
	}
	

	public String getTime() {
		return this.Time;
	}

	public void setTime(String Time) {
		this.Time = Time;
	}
	
   
	/*
	 * @see java.lang.Object#equals(Object)
	 */	
	public boolean equals(Object o) {
		if (o == this) {
			return true;
		}
		if (!(o instanceof PumpPK)) {
			return false;
		}
		PumpPK other = (PumpPK) o;
		return true
			&& getId() == other.getId()
			&& (getTime() == null ? other.getTime() == null : getTime().equals(other.getTime()));
	}
	
	/*	 
	 * @see java.lang.Object#hashCode()
	 */	
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + getId();
		result = prime * result + (getTime() == null ? 0 : getTime().hashCode());
		return result;
	}
   
   
}
