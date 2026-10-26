package repository.factory;

/**
 * the persistence types the app can use, read from the config (repository.type)
 */
public enum RepositoryType {
    MEMORY,
    FILE,
    DATABASE
}
