package repository;

import domain.Utilizator;
import domain.validators.Validator;

/**
 * Repo in memory for users; the id of a new user is generated here (the biggest id + 1)
 */
public class UtilizatorInMemoryRepository extends InMemoryRepository<Long, Utilizator> {

    /**
     * @param validator the validation strategy for users
     */
    public UtilizatorInMemoryRepository(Validator<Utilizator> validator) {
        super(validator);
    }

    /**
     * @return the biggest id + 1, 1 if there are no users
     */
    @Override
    protected Long genereazaId() {
        // * urmatorulId din service, mutat aici: stocarea genereaza id-ul
        return stream()
                .map(Utilizator::getId)
                .reduce(0L, Long::max) + 1;
    }
}
