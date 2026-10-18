package domain.validators;

import domain.Utilizator;

public class UtilizatorValidator implements Validator<Utilizator> {

    @Override
    public void validate(Utilizator u) throws ValidationException {
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
