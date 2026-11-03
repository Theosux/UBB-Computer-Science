from domain.persoana import Persoana
from repository.exceptions import DuplicateIDException, NotFoundException

class PersoanaRepository:
    def __init__(self):
        self._persoane = {}

    def store(self, persoana):
        if persoana.personID in self._persoane:
            raise DuplicateIDException(f"ID-ul {persoana.personID} exista deja!")
        self._persoane[persoana.personID] = persoana

    def find(self, personID):
        if personID not in self._persoane:
            return None
        return self._persoane[personID]

    def update(self, personID, persoana_actualizata):
        if personID not in self._persoane:
            raise NotFoundException(f"Persoana cu ID {personID} nu a fost gasita.")
        self._persoane[personID] = persoana_actualizata

    def delete(self, personID):
        if personID not in self._persoane:
            raise NotFoundException(f"Persoana cu ID {personID} nu a fost gasita.")
        del self._persoane[personID]

    def get_all(self):
        return list(self._persoane.values())