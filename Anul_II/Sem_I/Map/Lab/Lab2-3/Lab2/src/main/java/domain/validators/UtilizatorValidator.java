package domain.validators;

import domain.Utilizator;

/**
 * Validator for users: the id must be positive and the names must start with a capital letter
 */
public class UtilizatorValidator implements Validator<Utilizator> {

    /**
     *
     * @param u the user that has to be validated
     * @throws ValidationException if the user is null, the id is not positive, or a name is empty or doesn't start with a capital letter
     */
    @Override
    public void validate(Utilizator u) {

        if (u == null)
            throw new ValidationException("Utilizatorul nu poate fi null!");

        StringBuilder errors = new StringBuilder();
        if (u.getId() == null || u.getId() <= 0)
            errors.append("id invalid; ");
        if (!esteNumeValid(u.getFirstName()))
            errors.append("prenume invalid; ");
        if (!esteNumeValid(u.getLastName()))
            errors.append("nume invalid; ");

        if (!errors.isEmpty())
            throw new ValidationException(errors.toString().trim());
    }

    private static boolean esteNumeValid(String s) {
        return s != null && !s.isBlank() && Character.isUpperCase(s.charAt(0));
    }
}
