package repository;

import domain.Entity;
import domain.validators.ValidationException;

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
}
