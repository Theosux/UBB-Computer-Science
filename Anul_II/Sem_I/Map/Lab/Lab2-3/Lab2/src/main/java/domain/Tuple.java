package domain;

import java.util.Objects;

/**
 * Immutable pair of two values, used as the id of the friendships
 *
 * @param <E1> the type of the first value
 * @param <E2> the type of the second value
 */
public class Tuple<E1, E2> {

    private final E1 left;
    private final E2 right;

    /**
     * @param left the first value
     * @param right the second value
     */
    public Tuple(E1 left, E2 right) {
        this.left = left;
        this.right = right;
    }

    /**
     * @return the first value
     */
    public E1 getLeft() {
        return left;
    }

    /**
     * @return the second value
     */
    public E2 getRight() {
        return right;
    }

    /**
     * @param o the object we compare with
     * @return true if o is a tuple with the same values, in the same order
     */
    @Override
    public boolean equals(Object o) {
        // doua perechi sunt egale daca au aceleasi elemente, in aceeasi ordine

        if (this == o) return true;
        if (!(o instanceof Tuple<?, ?> tuple)) return false;
        return Objects.equals(left, tuple.left) && Objects.equals(right, tuple.right);
    }

    /**
     * @return the hash code from both values
     */
    @Override
    public int hashCode() {
        return Objects.hash(left, right);
    }

    /**
     * @return the tuple as text
     */
    @Override
    public String toString() {
        return "(" + left + ", " + right + ")";
    }
}
