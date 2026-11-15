package repository.db;

import domain.Prietenie;
import domain.Tuple;
import domain.validators.ValidationException;
import domain.validators.Validator;
import repository.Repository;
import repository.RepositoryException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

/**
 * database repo for friendships, every operation is a query on the table friendships(id1, id2, friends_from)
 * The id of a friendship is the pair (id1, id2), with id1 &lt; id2
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
     * @param id the pair of user ids, not null
     * @return the friendship with that id, null if it doesn't exist
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if the database cannot be accessed
     */
    @Override
    public Prietenie findOne(Tuple<Long, Long> id) {
        if (id == null)
            throw new IllegalArgumentException("id-ul nu poate fi null!");
        // * cheia e formata din doua coloane, deci doi parametri ?
        String sql = "SELECT * FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, id.getLeft());
            ps.setLong(2, id.getRight());
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next())
                    return dinRand(rs);
                return null;
            }
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la findOne: " + e.getMessage(), e);
        }
    }

    /**
     * @return all the friendships
     * @throws RepositoryException if the database cannot be accessed
     */
    @Override
    public Iterable<Prietenie> findAll() {
        List<Prietenie> prietenii = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement("SELECT * FROM friendships ORDER BY id1, id2");
             ResultSet rs = ps.executeQuery()) {
            while (rs.next())
                prietenii.add(dinRand(rs));
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la findAll: " + e.getMessage(), e);
        }
        return prietenii;
    }

    /**
     * @param entity the friendship that must be saved, not null
     * @return null if the friendship was saved, otherwise, the friendship (it already exists)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the database cannot be accessed
     */
    @Override
    public Prietenie save(Prietenie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entitatea nu poate fi null!");
        validator.validate(entity);
        // * ca la curs: daca id-ul exista deja, intoarcem entitatea (contractul Repository), fara INSERT
        if (findOne(entity.getId()) != null)
            return entity;
        String sql = "INSERT INTO friendships (id1, id2, friends_from) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, entity.getIdUtilizator1());
            ps.setLong(2, entity.getIdUtilizator2());
            // * LocalDateTime -> Timestamp (tipul JDBC pentru coloana TIMESTAMP)
            ps.setTimestamp(3, Timestamp.valueOf(entity.getDataPrieteniei()));
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la save: " + e.getMessage(), e);
        }
        return null;
    }

    /**
     * @param id the pair of user ids, not null
     * @return the deleted friendship, null if there is no friendship with that id
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if the database cannot be accessed
     */
    @Override
    public Prietenie delete(Tuple<Long, Long> id) {
        Prietenie gasita = findOne(id);
        if (gasita == null)
            return null;
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement("DELETE FROM friendships WHERE id1 = ? AND id2 = ?")) {
            ps.setLong(1, id.getLeft());
            ps.setLong(2, id.getRight());
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la delete: " + e.getMessage(), e);
        }
        return gasita;
    }

    /**
     * Only the date of a friendship can change, the two ids are the key
     *
     * @param entity the friendship with the new date, not null
     * @return null if the friendship was updated, otherwise, the friendship (if it doesn't exist)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the database cannot be accessed
     */
    @Override
    public Prietenie update(Prietenie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entitatea nu poate fi null!");
        validator.validate(entity);
        String sql = "UPDATE friendships SET friends_from = ? WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setTimestamp(1, Timestamp.valueOf(entity.getDataPrieteniei()));
            ps.setLong(2, entity.getIdUtilizator1());
            ps.setLong(3, entity.getIdUtilizator2());
            int randuri = ps.executeUpdate();
            return randuri == 0 ? entity : null;
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la update: " + e.getMessage(), e);
        }
    }

    /**
     * Creates a friendship from the current row of a query on the table friendships
     *
     * @param rs a ResultSet positioned on a row
     * @return the friendship described by the row
     * @throws SQLException if a column doesn't exist
     */
    private static Prietenie dinRand(ResultSet rs) throws SQLException {
        // * Timestamp -> LocalDateTime, tipul din Prietenie
        return new Prietenie(rs.getLong("id1"), rs.getLong("id2"),
                rs.getTimestamp("friends_from").toLocalDateTime());
    }
}
