package domain.validators;

/**
 * Validation strategy for an entity  -   we will use @throws
 *
 * @param <T> the type of the entity to validate
 */

// * o singura metoda abstracta = interfata functionala
@FunctionalInterface
public interface Validator<T> {

    /**
     * Checks if the entity is valid
     *
     * @param entity the entity that has to be validated
     * @throws ValidationException if the entity is null or not valid
     */
    void validate(T entity) ;

    /**
     * Composes this validator with another one, first this validator is applied, then the second one
     * Validation stops at first exception
     *
     * @param other the validator applied after this one, not null
     * @return a validator applying both validators, in order
     * @throws IllegalArgumentException if other is null
     */
    default Validator<T> andThen(Validator<T> other) {
        // * metoda default: are implementare, interfata va fi functionala
        if (other == null)
            throw new IllegalArgumentException("validatorul urmator nu poate fi null!");
        // * intoarcem un validator nou, scris ca lambda
        return entity -> {
            validate(entity);
            other.validate(entity);
        };
    }
}
