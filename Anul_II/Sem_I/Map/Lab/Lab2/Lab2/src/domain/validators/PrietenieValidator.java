package domain.validators;

import domain.Prietenie;

public class PrietenieValidator implements Validator<Prietenie> {

    @Override
    public void validate(Prietenie p) throws ValidationException {
        if (p == null)
            throw new ValidationException("Prietenia nu poate fi null!");

        Long id1 = p.getIdUtilizator1();
        Long id2 = p.getIdUtilizator2();
        StringBuilder errors = new StringBuilder();
        if (id1 == null || id1 <= 0)
            errors.append("id utilizator 1 invalid; ");
        if (id2 == null || id2 <= 0)
            errors.append("id utilizator 2 invalid; ");
        if (id1 != null && id1.equals(id2))
            errors.append("un utilizator nu poate fi prieten cu el insusi; ");

        if (!errors.isEmpty())
            throw new ValidationException(errors.toString().trim());
    }
}
