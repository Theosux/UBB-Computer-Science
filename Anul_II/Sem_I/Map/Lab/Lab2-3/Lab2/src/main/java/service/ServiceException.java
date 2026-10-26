package service;

/**
 * unchecked exception thrown when an operation from the service cannot be done
 * Ex: if the user doesn't exist or the friendship already exists
 */
public class ServiceException extends RuntimeException {

    /**
     * @param message the description of the error
     */
    public ServiceException(String message) {
        super(message);
    }
}
