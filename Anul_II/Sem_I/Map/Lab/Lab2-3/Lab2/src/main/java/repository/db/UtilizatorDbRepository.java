package repository.db;

import domain.Utilizator;
import domain.validators.Validator;
import repository.Repository;

/**
 * database repo for users
 */
public class UtilizatorDbRepository implements Repository<Long, Utilizator> {

    private final Validator<Utilizator> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * @param validator the validation strategy for users
     * @param url database url
     * @param user database user
     * @param password the password
     */
    public UtilizatorDbRepository(Validator<Utilizator> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Utilizator findOne(Long id) {
        throw new UnsupportedOperationException("findOne nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Iterable<Utilizator> findAll() {
        throw new UnsupportedOperationException("findAll nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Utilizator save(Utilizator entity) {
        throw new UnsupportedOperationException("save nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Utilizator delete(Long id) {
        throw new UnsupportedOperationException("delete nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Utilizator update(Utilizator entity) {
        throw new UnsupportedOperationException("update nu este implementat inca (laboratorul 4)");
    }
}
