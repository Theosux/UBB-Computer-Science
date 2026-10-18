package repository;

import domain.Entity;

import domain.Validator;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final Validator<E> validator;
    private final Map<ID, E> repo = new HashMap<ID, E>();

    public InMemoryRepository(Validator<E> v) {
        this.validator = Objects.requireNonNull(v, "Validator obligatoriu!");
    }

    @Override
    public E findOne(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("id nu poate fi null!");
        }
        return repo.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return repo.values();
    }

    @Override
    public E save(E entity) {
        if(entity == null) {
            throw new IllegalArgumentException("Entity nu poate fi null!");
        }
        validator.validate(entity);
        if(entity.getId() == null) {
            throw new IllegalArgumentException("ID-ul entitatii nu poate fi null!");
        }
        repo.put(entity.getId(), entity);
        return entity;
    }

    @Override
    public E delete(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("ID nu poate fi nulll!");
        }
        return repo.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity nu poate fi null!");
        }
        validator.validate(entity);
        if (entity.getId() == null) {
            throw new IllegalArgumentException("ID-ul entitatii nu poate fi null!");
            ///
        }
    }
}
