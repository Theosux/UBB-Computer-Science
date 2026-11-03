from domain.eveniment import Eveniment
from repository.repo_evenimente import EvenimentRepository

class EvenimentFileRepository(EvenimentRepository):
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
                    ev = Eveniment(parts[0], parts[1], parts[2], parts[3])
                    
                    # Gestionare participanti
                    if len(parts) > 4 and parts[4].strip() != "":
                        participanti_ids = parts[4].split(",")
                        ev.participanti = participanti_ids
                    
                    self._evenimente[ev.ID] = ev
        except IOError:
            pass

    def _save_to_file(self):
        with open(self._filename, "w") as f:
            for ev in self._evenimente.values():
                participanti_str = ",".join(ev.participanti)
                line = f"{ev.ID};{ev.data};{ev.timp};{ev.descriere};{participanti_str}\n"
                f.write(line)

    def store(self, eveniment):
        super().store(eveniment)
        self._save_to_file()

    def update(self, ID, eveniment_actualizat):
        super().update(ID, eveniment_actualizat)
        self._save_to_file()

    def delete(self, ID):
        super().delete(ID)
        self._save_to_file()