package repository;

import domain.Entity;
import domain.validators.ValidationException;

public interface Repository<ID, E extends Entity<ID>> {
    // interfata pt operatiile crud

    E findOne(ID id);

    Iterable<E> findAll();

    E save(E entity);

    E delete(ID id);

    E update(E entity);
}
