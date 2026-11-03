class Eveniment:
    def __init__(self, ID, data, timp, descriere):
        self.ID = ID
        self.data = data
        self.timp = timp
        self.descriere = descriere
        self.participanti = [] 

    def __str__(self):
        return f"ID: {self.ID} | Data: {self.data} | Timp: {self.timp} | Descriere: {self.descriere}"

    def __eq__(self, other):
        if not isinstance(other, Eveniment):
            return False
        return self.ID == other.ID