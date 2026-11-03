class RepositoryException(Exception):
    """Clasa de bază pentru excepțiile din repository."""
    pass

class DuplicateIDException(RepositoryException):
    pass

class NotFoundException(RepositoryException):
    pass