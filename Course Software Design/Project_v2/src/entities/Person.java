package entities;

import java.io.Serializable;
import java.lang.String;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Person
 *
 */
@Entity
@Inheritance(strategy = InheritanceType.TABLE_PER_CLASS)
public class Person implements Serializable {

	public static enum Gender {
		MALE, FEMALE
	}

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private int pm_key;
	private String firstName;
	private String lastName;
	private String address;
	private Gender gender;
	private String dob;

	private static final long serialVersionUID = 1L;

	public Person() {
		super();
	}

	public int getPm_key() {
		return pm_key;
	}

	public void setPm_key(int pm_key) {
		this.pm_key = pm_key;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public Gender getGender() {
		return gender;
	}

	public void setGender(Gender gender) {
		this.gender = gender;
	}

	public String getDob() {
		return dob;
	}

	public void setDob(String dob) {
		this.dob = dob;
	}

	@Override
	public String toString() {
		return String.format("First name:%s\nLast name:%s\ndob:%s\ngender:%s", getFirstName(), getLastName(), getDob(),
				(getGender() == Gender.MALE ? "Male" : "Female"));
	}

}
