package domain.validators;

/**
 * Validation strategy for an entity  -   we will use @throws
 *
 * @param <T> the type of the entity to validate
 */
public interface Validator<T> {

    /**
     * Checks if the entity is valid
     *
     * @param entity the entity that has to be validated
     * @throws ValidationException if the entity is null or not valid
     */
    void validate(T entity) ;
}
