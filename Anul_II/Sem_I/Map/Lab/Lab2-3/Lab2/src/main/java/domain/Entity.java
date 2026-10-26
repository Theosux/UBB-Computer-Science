package domain;

import java.io.Serializable;
import java.util.Objects;

/**
 * base class for all the entities with an id
 * two entities are equal if they have the same id
 *
 * @param <ID> the type of the id
 */
public class Entity<ID> implements Serializable {

    private ID id;

    /**
     * @return the id of the entity
     */
    public ID getId() {
        return id;
    }

    /**
     * @param id the new id of the entity
     */
    public void setId(ID id) {
        this.id = id;
    }

    /**
     * @param o the object we compare with
     * @return true if o is an entity with the same id, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        // doua entitati sunt egale daca au acelasi id

        if (this == o) return true;
        if (!(o instanceof Entity<?> entity)) return false;
        return Objects.equals(id, entity.id);
    }

    /**
     * @return the hash code of the id
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}


