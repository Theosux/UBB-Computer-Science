package repository.factory;

import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.RepositoryException;
import repository.db.PrietenieDbRepository;
import repository.db.UtilizatorDbRepository;
import repository.file.PrietenieFileRepository;
import repository.file.UtilizatorFileRepository;

import java.util.Properties;

/**
 * Simple Factory for repositories, the only class that knows the repository classes and picks the persistence type
 * Both repo types are created for the same persistence type
 */
public class RepositoryFactory {
    // * singurul loc unde se face new pe repouri(simple factory)

    private final Properties config;

    /**
     * @param config the configuration read from config.properties
     */
    public RepositoryFactory(Properties config) {
        this.config = config;
    }

    /**
     * @param validator the validation strategy for users
     * @return the users repo for the configured persistence type
     * @throws RepositoryException if a key is missing, repository.type is wrong, or the file cannot be loaded
     */
    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        // * switch clasic
        RepositoryType type = getType();
        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UtilizatorFileRepository(validator, getProperty("file.utilizatori"));
            case DATABASE:
                return new UtilizatorDbRepository(validator, getProperty("db.url"),
                        getProperty("db.user"), getProperty("db.password"));
            default:
                throw new RepositoryException("Tip de persistenta netratat: " + type);
        }
    }

    /**
     * @param validator the validation strategy for friendships
     * @return the friendships repo for the configured persistence type
     * @throws RepositoryException if a key is missing, repository.type is wrong, or the file cannot be loaded
     */
    public Repository<Tuple<Long, Long>, Prietenie> createPrietenieRepository(Validator<Prietenie> validator) {
        // * acelasi repository.type ca la utilizatori, deci aceeasi persistenta pt amandoua

        RepositoryType type = getType();
        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new PrietenieFileRepository(validator, getProperty("file.prietenii"));
            case DATABASE:
                return new PrietenieDbRepository(validator, getProperty("db.url"),
                        getProperty("db.user"), getProperty("db.password"));
            default:
                throw new RepositoryException("Tip de persistenta netratat: " + type);
        }
    }

    private RepositoryType getType() {
        // * textul din config devine enum; valueOf arunca IllegalArgumentException pt o valoare necunoscuta

        String value = getProperty("repository.type");
        try {
            return RepositoryType.valueOf(value);
        } catch (IllegalArgumentException e) {
            throw new RepositoryException("Valoare necunoscuta pentru repository.type: " + value
                    + " (valori posibile: MEMORY, FILE, DATABASE)", e);
        }
    }

    private String getProperty(String key) {
        // * cheie lipsa sau goala in config.properties: exceptie cu mesaj clar

        String value = config.getProperty(key);
        if (value == null || value.isBlank())
            throw new RepositoryException("Lipseste cheia " + key + " din config.properties");
        return value.trim();
    }
}
