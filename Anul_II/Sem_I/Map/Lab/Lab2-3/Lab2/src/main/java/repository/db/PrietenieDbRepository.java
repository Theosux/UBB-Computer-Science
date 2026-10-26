package repository.db;

import domain.Prietenie;
import domain.Tuple;
import domain.validators.Validator;
import repository.Repository;

/**
 * database repo for friendships
 */
public class PrietenieDbRepository implements Repository<Tuple<Long, Long>, Prietenie> {

    private final Validator<Prietenie> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * @param validator the validation strategy for friendships
     * @param url database url
     * @param user database user
     * @param password the password
     */
    public PrietenieDbRepository(Validator<Prietenie> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Prietenie findOne(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("findOne nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Iterable<Prietenie> findAll() {
        throw new UnsupportedOperationException("findAll nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Prietenie save(Prietenie entity) {
        throw new UnsupportedOperationException("save nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Prietenie delete(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("delete nu este implementat inca (laboratorul 4)");
    }

    /**
     * @throws UnsupportedOperationException always (not implemented)
     */
    @Override
    public Prietenie update(Prietenie entity) {
        throw new UnsupportedOperationException("update nu este implementat inca (laboratorul 4)");
    }
}