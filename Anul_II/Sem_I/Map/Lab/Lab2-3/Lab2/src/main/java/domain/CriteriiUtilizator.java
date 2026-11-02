package domain;

import java.util.function.Predicate;

/**
 * Search criteria for users, used Repository.findAll
 * Every method returns a Predicate, so the criteria can be combined with and, or, negate, Predicate.not
 */
public class CriteriiUtilizator {
    // * clasa utilitara, doar metode statice, nu se creeaza obiecte
    private CriteriiUtilizator() {
    }

    /**
     * @param prefix the beginning of the first name, not null
     * @return a criterion that is true for the users whose first name starts with prefix
     */
    public static Predicate<Utilizator> prenumeleIncepeCu(String prefix) {
        // * lambda retine valoarea lui prefix (closure), chiar daca metoda s-a terminat
        return u -> u.getFirstName().startsWith(prefix);
    }

    /**
     * @param nume the last name
     * @return a criterion that is true for the users with exactly this last name
     */
    public static Predicate<Utilizator> areNumele(String nume) {
        return u -> u.getLastName().equals(nume);
    }

    /**
     * @param n the minimum number of friends
     * @return a criterion that is true for the users with at least n friends
     */
    public static Predicate<Utilizator> areCelPutinPrieteni(int n) {
        return u -> u.getFriends().size() >= n;
    }

    /**
     * Has the form of a Predicate (Utilizator to boolean), so it can be used as CriteriiUtilizator::faraPrieteni
     *
     * @param u the user
     * @return true if the user has no friends
     */
    public static boolean faraPrieteni(Utilizator u) {
        return u.getFriends().isEmpty();
    }
}
