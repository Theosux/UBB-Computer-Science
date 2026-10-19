package domain.validators;

public interface Validator<T> {
    // strategie de validare pt orice entitate

    void validate(T entity) throws ValidationException;
}
