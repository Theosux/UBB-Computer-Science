package repository;

/**
 * Unchecked exceptions for persistence errors (corrupt files, unreadable ones)
 */
public class RepositoryException extends RuntimeException {

    /**
     * @param message the description of the error
     */
    public RepositoryException(String message) {
        super(message);
    }

    /**
     * @param message the description of the error
     * @param cause the original exception
     */
    public RepositoryException(String message, Throwable cause) {
        super(message, cause);
    }
}
