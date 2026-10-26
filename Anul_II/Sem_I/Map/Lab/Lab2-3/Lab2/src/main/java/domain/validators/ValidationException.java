package domain.validators;

/**
 * Unchecked exception thrown when the entity is not valid
 */
public class ValidationException extends RuntimeException {

    /**
     * @param message the description of all the validation errors
     */
    public ValidationException(String message) {
        super(message);
    }
}
