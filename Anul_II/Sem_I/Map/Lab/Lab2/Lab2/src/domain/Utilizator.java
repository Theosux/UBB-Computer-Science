package domain;

import java.util.ArrayList;
import java.util.List;

public class Utilizator extends Entity<Long> {
    // utilizator al retelei identificat prin ID de tip Long

    private String firstName;
    private String lastName;
    private final List<Utilizator> friends = new ArrayList<>();

    public Utilizator(String firstName, String lastName) {
        // instantierea creeaza un utilizator fara prieteni; id-ul se seteaza cu set id din entity, el are firstname si lastname

        this.firstName = firstName;
        this.lastName = lastName;
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

    public List<Utilizator> getFriends() {
        return friends;
    }

    @Override
    public String toString() {
        return getId() + ". " + firstName + " " + lastName;
    }
}
