from domain.eveniment import Eveniment
from repository.exceptions import DuplicateIDException, NotFoundException

class EvenimentRepository:
    def __init__(self):
        self._evenimente = {}

    def store(self, eveniment):
        if eveniment.ID in self._evenimente:
            raise DuplicateIDException(f"ID-ul {eveniment.ID} exista deja!")
        self._evenimente[eveniment.ID] = eveniment

    def find(self, ID):
        if ID not in self._evenimente:
            return None
        return self._evenimente[ID]

    def update(self, ID, eveniment_actualizat):
        if ID not in self._evenimente:
            raise NotFoundException(f"Evenimentul cu ID {ID} nu a fost gasit.")
        self._evenimente[ID] = eveniment_actualizat

    def delete(self, ID):
        if ID not in self._evenimente:
            raise NotFoundException(f"Evenimentul cu ID {ID} nu a fost gasit.")
        del self._evenimente[ID]

    def get_all(self):
        return list(self._evenimente.values())