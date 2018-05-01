package jpaEntities;

import java.io.Serializable;
import java.lang.String;
import javax.persistence.*;

/**
 * Entity implementation class for Entity: CleaningService
 *
 */
@Entity

public class CleaningService implements Serializable {

	   
	@Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	private int Id;
	private double Profit;
	private String Time;
	private String Date;
	private String CarId;
	private static final long serialVersionUID = 1L;

	public CleaningService() {
		super();
	}   
	public int getId() {
		return this.Id;
	}

	public void setId(int Id) {
		this.Id = Id;
	}   
	public double getProfit() {
		return this.Profit;
	}

	public void setProfit(double Profit) {
		this.Profit = Profit;
	}   
	public String getTime() {
		return this.Time;
	}

	public void setTime(String Time) {
		this.Time = Time;
	}   
	public String getDate() {
		return this.Date;
	}

	public void setDate(String Date) {
		this.Date = Date;
	}   
	public String getCarId() {
		return this.CarId;
	}

	public void setCarId(String CarId) {
		this.CarId = CarId;
	}
   
}
