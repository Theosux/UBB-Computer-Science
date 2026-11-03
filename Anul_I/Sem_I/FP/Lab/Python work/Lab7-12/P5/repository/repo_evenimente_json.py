import json
from domain.eveniment import Eveniment
from repository.repo_evenimente import EvenimentRepository

class EvenimentJSONRepository(EvenimentRepository):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename
        self._load_from_file()

    def _load_from_file(self):
        try:
            with open(self._filename, "r") as f:
                data = json.load(f)
                for ev_dict in data:
                    ev = Eveniment(ev_dict["ID"], ev_dict["data"], ev_dict["timp"], ev_dict["descriere"])
                    ev.participanti = ev_dict["participanti"]
                    self._evenimente[ev.ID] = ev
        except (IOError, ValueError):
            pass

    def _save_to_file(self):
        lista_dict = []
        for ev in self._evenimente.values():
            lista_dict.append({
                "ID": ev.ID,
                "data": ev.data,
                "timp": ev.timp,
                "descriere": ev.descriere,
                "participanti": ev.participanti 
            })

        with open(self._filename, "w") as f:
            json.dump(lista_dict, f, indent=4)

    def store(self, eveniment):
        super().store(eveniment)
        self._save_to_file()

    def update(self, ID, eveniment_actualizat):
        super().update(ID, eveniment_actualizat)
        self._save_to_file()

    def delete(self, ID):
        super().delete(ID)
        self._save_to_file()