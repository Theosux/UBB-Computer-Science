package repository;

import domain.Entity;
import domain.validators.ValidationException;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

/**
 * The CRUD operations of the repo, interface
 *
 * @param <ID> the id type of the entity
 * @param <E> the type of the entity saved in the repo
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * @param id entity that must be returned, not null
     * @return the entity with that id, null if it doesn't exist
     * @throws IllegalArgumentException if id is null
     */
    E findOne(ID id);

    /**
     * @return all the entities
     */
    Iterable<E> findAll();

    /**
     * @param entity the entity that must be saved, not null
     * @return null if the entity was saved, otherwise, the entity (it already exists)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the data cannot be persisted
     */
    E save(E entity);

    /**
     * @param id entity that must be deleted, not null
     * @return the deleted entity, null if there is no entity with that id
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if the data cannot be persisted
     */
    E delete(ID id);

    /**
     * @param entity the entity with the new data, not null
     * @return null if the entity was updated, otherwise, the entity (if it doesn't exist)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the data cannot be persisted
     */
    E update(E entity);

    /**
     * Default method: every repo gets it without changes
     *
     * @param filter the search criterion (a predicate: entity to boolean), not null
     * @return a new list with the entities that satisfy the criterion
     * @throws IllegalArgumentException if filter is null
     */
    default List<E> findAll(Predicate<E> filter) {
        // * cautarea primeste criteriul ca parametru, deci nu mai adaugam metode
        if (filter == null)
            throw new IllegalArgumentException("criteriul nu poate fi null!");
        // * filter pastreaza entitatile care respecta criteriul, collect le strange intr-o lista noua
        return stream()
                .filter(filter)
                .collect(Collectors.toList());
    }

    /**
     * Default method: every repo gets it without changes
     * Iterable has no stream() method, so the stream is built from the spliterator of findAll()
     *
     * @return a new sequential stream over all the entities
     */
    default Stream<E> stream() {
        // * StreamSupport scris o singura data
        return StreamSupport.stream(findAll().spliterator(), false);
    }
}
