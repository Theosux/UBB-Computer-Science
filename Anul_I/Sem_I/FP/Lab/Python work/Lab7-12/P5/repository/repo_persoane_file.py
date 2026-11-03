from domain.persoana import Persoana
from repository.repo_persoane import PersoanaRepository

class PersoanaFileRepository(PersoanaRepository):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename
        self._load_from_file()

    def _load_from_file(self):
        try:
            with open(self._filename, "r") as f:
                lines = f.readlines()
                for line in lines:
                    line = line.strip()
                    if line == "":
                        continue
                    # Format:
                    parts = line.split(";")
                    persoana = Persoana(parts[0], parts[1], parts[2])

                    self._persoane[persoana.personID] = persoana
        except IOError:
            pass

    def _save_to_file(self):
        with open(self._filename, "w") as f:
            for persoana in self._persoane.values():
                line = f"{persoana.personID};{persoana.nume};{persoana.adresa}\n"
                f.write(line)

    def store(self, persoana):
        # Reutilizam logica de la memorie
        super().store(persoana)
        self._save_to_file()

    def update(self, personID, persoana_actualizata):
        super().update(personID, persoana_actualizata)
        self._save_to_file()

    def delete(self, personID):
        super().delete(personID)
        self._save_to_file()