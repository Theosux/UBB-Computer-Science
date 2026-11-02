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
import java.util.Map;
import java.util.function.Function;

/**
 * Simple Factory for repositories, the only class that knows the repository classes and picks the persistence type
 * Both repo types are created for the same persistence type
 */
public class RepositoryFactory {
    // singurul loc unde se face new pe repouri(simple factory)

    private final Properties config;
    // * fiecarui tip de persistenta ii corespunde o functie: primeste validatorul, intoarce repo-ul
    private final Map<RepositoryType, Function<Validator<Utilizator>, Repository<Long, Utilizator>>> creatoriUtilizatori;
    private final Map<RepositoryType, Function<Validator<Prietenie>, Repository<Tuple<Long, Long>, Prietenie>>> creatoriPrietenii;

    /**
     * @param config the configuration read from config.properties
     */
    public RepositoryFactory(Properties config) {
        this.config = config;
        // * InMemoryRepository::new = referinta la constructor, inseamna v -> new InMemoryRepository<>(v)
        // * lambda-urile doar descriu cum se creeaza repo-ul; fisierul se citeste abia la apply (lazy)
        this.creatoriUtilizatori = Map.of(
                RepositoryType.MEMORY, InMemoryRepository::new,
                RepositoryType.FILE, v -> new UtilizatorFileRepository(v, getProperty("file.utilizatori")),
                RepositoryType.DATABASE, v -> new UtilizatorDbRepository(v, getProperty("db.url"),
                        getProperty("db.user"), getProperty("db.password")));
        this.creatoriPrietenii = Map.of(
                RepositoryType.MEMORY, InMemoryRepository::new,
                RepositoryType.FILE, v -> new PrietenieFileRepository(v, getProperty("file.prietenii")),
                RepositoryType.DATABASE, v -> new PrietenieDbRepository(v, getProperty("db.url"),
                        getProperty("db.user"), getProperty("db.password")));
    }

    /**
     * @param validator the validation strategy for users
     * @return the users repo for the configured persistence type
     * @throws RepositoryException if a key is missing, repository.type is wrong, or the file cannot be loaded
     */
    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        // * in loc de switch: luam din map functia tipului ales si o aplicam pe validator
        RepositoryType type = getType();
        Function<Validator<Utilizator>, Repository<Long, Utilizator>> creator = creatoriUtilizatori.get(type);
        // * get intoarce null daca tipul e in enum, dar nu are functie in map (rolul default-ului din switch)
        if (creator == null)
            throw new RepositoryException("Tip de persistenta netratat: " + type);
        return creator.apply(validator);
    }

    /**
     * @param validator the validation strategy for friendships
     * @return the friendships repo for the configured persistence type
     * @throws RepositoryException if a key is missing, repository.type is wrong, or the file cannot be loaded
     */
    public Repository<Tuple<Long, Long>, Prietenie> createPrietenieRepository(Validator<Prietenie> validator) {
        // acelasi repository.type ca la utilizatori, deci aceeasi persistenta pt amandoua

        // * la fel ca la utilizatori, cu map-ul pentru prietenii
        RepositoryType type = getType();

        Function<Validator<Prietenie>, Repository<Tuple<Long, Long>, Prietenie>> creator = creatoriPrietenii.get(type);
        if (creator == null)
            throw new RepositoryException("Tip de persistenta netratat: " + type);
        return creator.apply(validator);
    }

    private RepositoryType getType() {
        // textul din config devine enum; valueOf arunca IllegalArgumentException pt o valoare necunoscuta

        String value = getProperty("repository.type");
        try {
            return RepositoryType.valueOf(value);
        } catch (IllegalArgumentException e) {
            throw new RepositoryException("Valoare necunoscuta pentru repository.type: " + value
                    + " (valori posibile: MEMORY, FILE, DATABASE)", e);
        }
    }

    private String getProperty(String key) {
        // cheie lipsa sau goala in config.properties: exceptie cu mesaj clar

        String value = config.getProperty(key);
        if (value == null || value.isBlank())
            throw new RepositoryException("Lipseste cheia " + key + " din config.properties");
        return value.trim();
    }
}
