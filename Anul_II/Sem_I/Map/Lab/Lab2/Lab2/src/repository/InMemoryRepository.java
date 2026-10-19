package repository;

import domain.Entity;
import domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;

// HashMap e implementarea, Map e interfata

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    // Repo care pastreaza entitatile in memorie, in hashmap
    // cheia e id - ul entitatea e valoarea

    private final Validator<E> validator;
    private final Map<ID, E> entities = new HashMap<>();

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
    }

    @Override
    public E findOne(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id-ul nu poate fi null!");
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

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

    @Override
    public E delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id-ul nu poate fi null!");
        return entities.remove(id);
    }

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
