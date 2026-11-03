class Persoana:
    def __init__(self, personID, nume, adresa):
        self.personID = personID
        self.nume = nume
        self.adresa = adresa

    def __str__(self):
        return f"ID: {self.personID}, Nume: {self.nume}, Adresă: {self.adresa}"

    def __eq__(self, other):
        if not isinstance(other, Persoana):
            return False
        return self.personID == other.personID
    
    