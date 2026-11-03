import json
from domain.persoana import Persoana
from repository.repo_persoane import PersoanaRepository

class PersoanaJSONRepository(PersoanaRepository):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename
        self._load_from_file()

    def _load_from_file(self):
        try:
            with open(self._filename, "r") as f:
                data = json.load(f)
                for p_dict in data:
                    persoana = Persoana(p_dict["personID"], p_dict["nume"], p_dict["adresa"])
                    self._persoane[persoana.personID] = persoana
        except (IOError, ValueError):
            pass

    def _save_to_file(self):
        lista_dict = []
        for p in self._persoane.values():
            lista_dict.append({
                "personID": p.personID,
                "nume": p.nume,
                "adresa": p.adresa
            })
            
        with open(self._filename, "w") as f:
            json.dump(lista_dict, f, indent=4)

    def store(self, persoana):
        super().store(persoana)
        self._save_to_file()

    def update(self, personID, persoana_actualizata):
        super().update(personID, persoana_actualizata)
        self._save_to_file()

    def delete(self, personID):
        super().delete(personID)
        self._save_to_file()