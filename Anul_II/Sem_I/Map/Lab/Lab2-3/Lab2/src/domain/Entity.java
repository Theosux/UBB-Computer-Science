package domain;

import java.io.Serializable;
import java.util.Objects;

public class Entity<ID> implements Serializable {
    // clasa de baza pt toate entitatile cu id

    private ID id;

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        // doua entitati sunt egale daca au acelasi id

        if (this == o) return true;
        if (!(o instanceof Entity<?> entity)) return false;
        return Objects.equals(id, entity.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}


