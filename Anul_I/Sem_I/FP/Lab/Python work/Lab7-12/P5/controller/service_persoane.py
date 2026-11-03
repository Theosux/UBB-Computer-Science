import random
import string
from domain.persoana import Persoana
from repository.exceptions import DuplicateIDException
from utilities.sorts import Sorter

class ServicePersoane:
    def __init__(self, repo_persoane, repo_evenimente):
        self._repo_persoane = repo_persoane
        self._repo_evenimente = repo_evenimente

    def get_all(self):
        return self._repo_persoane.get_all()

    def adauga_persoana(self, personID, nume, adresa):
        persoana = Persoana(personID, nume, adresa)
        try:
            self._repo_persoane.store(persoana)
        except DuplicateIDException as e:
            raise ValueError(str(e))

    def adauga_persoana_random(self):
        while True:
            id_nou = str(random.randint(100, 999))
            if self._repo_persoane.find(id_nou) is None:
                break
        
        nume = ''.join(random.choices(string.ascii_lowercase, k=6))
        strazi = ["Memorandumului", "Dorobantilor", "Horea", "Piezisa", "Republicii"]
        adresa = f"Str. {random.choice(strazi)} nr. {random.randint(1, 100)}"

        self.adauga_persoana(id_nou, nume, adresa)
        return id_nou, nume, adresa

    def sterge_persoana(self, personID):
        persoana = self._repo_persoane.find(personID)
        if persoana is None:
            raise ValueError(f"Persoana cu ID {personID} nu a fost găsită.")

        toate_evenimentele = self._repo_evenimente.get_all()
        for eveniment in toate_evenimentele:
            if personID in eveniment.participanti:
                eveniment.participanti.remove(personID)
                self._repo_evenimente.update(eveniment.ID, eveniment)

        self._repo_persoane.delete(personID)

    def modifica_persoana(self, personID, nume_nou, adresa_noua):
        persoana = self._repo_persoane.find(personID)
        if persoana is None:
            raise ValueError(f"Persoana cu ID {personID} nu a fost găsită.")
        
        persoana.nume = nume_nou
        persoana.adresa = adresa_noua
        self._repo_persoane.update(personID, persoana)

    def cauta_persoane(self, sir_cautare):
        """
        Complexitatea nu este constanta:
        Caz favorabil: θ(1) - daca sirul de cautare sau lista de persoana sunt vide, returneaza imediat toate persoanele, respectiv o lista vida.
        Caz defavorabil/mediu: θ(n) - algoritmul parcurge toate persoanele pentru a verifica daca sirul de cautare este substring al numelui fiecarei persoane.
        Complexitate generala timp: θ(n)
        """
        toate_persoanele = self._repo_persoane.get_all()
        if not sir_cautare:
            return toate_persoanele

        rezultat = []
        sir_lower = sir_cautare.lower()
        for persoana in toate_persoanele:
            if sir_lower in persoana.nume.lower():
                rezultat.append(persoana)
        return rezultat
    
    def cauta_persoane_recursive(self, sir_cautare, lista_persoane=None):
            if lista_persoane is None:
                lista_persoane = self._repo_persoane.get_all()
            
            if not sir_cautare:
                return lista_persoane
                
            if not lista_persoane:
                return []
                
            sir_lower = sir_cautare.lower()
            persoana_curenta = lista_persoane[0]
            restul_persoanelor = lista_persoane[1:]
            
            rezultate_rest = self.cauta_persoane_recursive(sir_cautare, restul_persoanelor)
            
            if sir_lower in persoana_curenta.nume.lower():
                return [persoana_curenta] + rezultate_rest
            return rezultate_rest
