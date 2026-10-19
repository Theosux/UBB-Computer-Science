package service;

public class ServiceException extends RuntimeException {
    // exceptie aruncata cand o operatie din service nu se poate face

    public ServiceException(String message) {
        super(message);
    }
}
