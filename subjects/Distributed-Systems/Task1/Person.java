import java.io.Serializable;

public class Person implements Serializable { 
	private String name;
	private String place;
	private int year;
	public Person(String aName, String aPlace, int aYear) {
		name = aName;
		place = aPlace;
		year = aYear;
	}
	// followed by methods for accessing the instance
	// variables
}
 