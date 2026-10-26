package repository;

import domain.Entity;
import domain.validators.ValidationException;
import domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;

// HashMap e implementarea, Map e interfata

/**
 * Repo that keeps the entities in memory, in a hashmap
 * Every key is checked by the validator before it is saved or updated
 *
 * @param <ID> the type of the id of the entities
 * @param <E> the type of the saved entities
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {

    private final Validator<E> validator;
    private final Map<ID, E> entities = new HashMap<>();

    /**
     *
     * @param validator the validation strategy for the entities
     */
    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
    }

    /**
     * @param id entity that must be returned, not null
     * @return the entity with that id, null if it doesn't exist
     * @throws IllegalArgumentException if id is null
     */
    @Override
    public E findOne(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id-ul nu poate fi null!");
        return entities.get(id);
    }

    /**
     * @return all the entities
     */
    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    /**
     * @param entity the entity that must be saved, not null
     * @return null if the entity was saved, otherwise, the entity (it already exists)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the data cannot be persisted
     */
    @Override
    public E save(E entity) {
        // return null = succes

        if (entity == null)
            throw new IllegalArgumentException("entitatea nu poate fi null!");
        validator.validate(entity);
        if (entities.containsKey(entity.getId()))
            return entity;
        entities.put(entity.getId(), entity);
        return null;
    }

    /**
     * @param id entity that must be deleted, not null
     * @return the deleted entity, null if there is no entity with that id
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if the data cannot be persisted
     */
    @Override
    public E delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id-ul nu poate fi null!");
        return entities.remove(id);
    }

    /**
     * @param entity the entity with the new data, not null
     * @return null if the entity was updated, otherwise, the entity (if it doesn't exist)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the data cannot be persisted
     */
    @Override
    public E update(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entitatea nu poate fi null!");
        validator.validate(entity);
        if (!entities.containsKey(entity.getId()))
            return entity;
        entities.put(entity.getId(), entity);
        return null;
    }
}
