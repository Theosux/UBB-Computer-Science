package domain;

import java.util.ArrayList;
import java.util.List;

/**
 * A user of the network, identified by a long id
 * Every user has a list of friends
 */
public class Utilizator extends Entity<Long> {

    private String firstName;
    private String lastName;
    private final List<Utilizator> friends = new ArrayList<>();

    /**
     * Creates a user without friends; the id is set with setId
     *
     * @param firstName the first name
     * @param lastName the second one
     */
    public Utilizator(String firstName, String lastName) {

        this.firstName = firstName;
        this.lastName = lastName;
    }

    /**
     * @return the first name
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * @param firstName is the new name
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * @return the second name
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * @param lastName the second name is the new name
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     * @return the list of friends
     */
    public List<Utilizator> getFriends() {
        return friends;
    }

    /**
     * @return the user as text
     */
    @Override
    public String toString() {
        return getId() + ". " + firstName + " " + lastName;
    }
}
