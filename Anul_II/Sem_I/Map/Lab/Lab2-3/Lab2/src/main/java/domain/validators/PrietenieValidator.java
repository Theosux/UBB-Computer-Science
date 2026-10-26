package domain.validators;

import domain.Prietenie;

/**
 * Validator for friendships: both ids must be positive and different, and the date must exist
 */
public class PrietenieValidator implements Validator<Prietenie> {

    /**
     * @param p the friendship that has to be validated
     * @throws ValidationException if the friendship is null, an id is not positive, the ids are equal, or the date is missing
     */
    @Override
    public void validate(Prietenie p) {
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
        // * prietenia contine data
        if (p.getDataPrieteniei() == null)
            errors.append("data prieteniei nu exista; ");

        if (!errors.isEmpty())
            throw new ValidationException(errors.toString().trim());
    }
}
