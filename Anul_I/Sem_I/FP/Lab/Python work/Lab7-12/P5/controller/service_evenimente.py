import random
import string
from domain.eveniment import Eveniment
from repository.exceptions import DuplicateIDException, NotFoundException
from utilities.sorts import Sorter

class ServiceEvenimente:
    def __init__(self, repo_persoane, repo_evenimente):
        self._repo_persoane = repo_persoane
        self._repo_evenimente = repo_evenimente

    def get_all(self):
        return self._repo_evenimente.get_all()

    def adauga_eveniment(self, ID, data, timp, descriere):
        eveniment = Eveniment(ID, data, timp, descriere)
        try:
            self._repo_evenimente.store(eveniment)
        except DuplicateIDException as e:
            raise ValueError(str(e))

    def adauga_eveniment_random(self):
        while True:
            id_nou = str(random.randint(100, 999))
            if self._repo_evenimente.find(id_nou) is None:
                break
        
        zi = random.randint(1, 28)
        luna = random.randint(1, 12)
        an = random.randint(2024, 2026)
        data = f"{zi:02d}.{luna:02d}.{an}"
        
        ora = random.randint(8, 22)
        minut = random.choice(["00", "15", "30", "45"])
        timp = f"{ora:02d}:{minut}"
        
        tipuri = ["Conferinta", "Workshop", "Examen", "Sedinta", "Teambuilding"]
        descriere = f"{random.choice(tipuri)} - { ''.join(random.choices(string.ascii_uppercase, k=3)) }"

        self.adauga_eveniment(id_nou, data, timp, descriere)
        return id_nou, data, timp, descriere

    def sterge_eveniment(self, ID):
        try:
            self._repo_evenimente.delete(ID)
        except NotFoundException:
             raise ValueError(f"Evenimentul cu ID {ID} nu a fost găsit.")

    def modifica_eveniment(self, ID, data_noua, timp_nou, descriere_noua):
        eveniment = self._repo_evenimente.find(ID)
        if eveniment is None:
            raise ValueError(f"Evenimentul cu ID {ID} nu a fost găsit.")
            
        eveniment.data = data_noua
        eveniment.timp = timp_nou
        eveniment.descriere = descriere_noua
        self._repo_evenimente.update(ID, eveniment)

    def inscrie_persoana(self, id_persoana, id_eveniment):
        persoana = self._repo_persoane.find(id_persoana)
        eveniment = self._repo_evenimente.find(id_eveniment)

        if persoana is None:
            raise ValueError(f"Nu exista persoana cu ID-ul {id_persoana}.")
        if eveniment is None:
            raise ValueError(f"Nu exista evenimentul cu ID-ul {id_eveniment}.")

        if id_persoana in eveniment.participanti:
            raise ValueError("Persoana este deja inscrisa la acest eveniment!")

        eveniment.participanti.append(id_persoana)
        self._repo_evenimente.update(id_eveniment, eveniment)

    def cauta_evenimente(self, sir_cautare):
        toate_evenimentele = self._repo_evenimente.get_all()
        if not sir_cautare:
            return toate_evenimentele

        rezultat = []
        sir_lower = sir_cautare.lower()
        for eveniment in toate_evenimentele:
            if (sir_lower in eveniment.descriere.lower() or 
                sir_lower in eveniment.data.lower() or 
                sir_lower in eveniment.timp.lower()):
                rezultat.append(eveniment)
        return rezultat
    
    def cauta_evenimente_recursive(self, sir_cautare, lista_ev=None):
        if lista_ev is None:
            lista_ev = self._repo_evenimente.get_all()
            
        if not sir_cautare:
            return lista_ev
            
        if not lista_ev:
            return []
            
        sir_lower = sir_cautare.lower()
        ev = lista_ev[0]
        
        match = (sir_lower in ev.descriere.lower() or 
                 sir_lower in ev.data.lower() or 
                 sir_lower in ev.timp.lower())
        
        rezultate_rest = self.cauta_evenimente_recursive(sir_cautare, lista_ev[1:])
        
        if match:
            return [ev] + rezultate_rest
        return rezultate_rest

    # --- RAPOARTE ---
    
    def raport_evenimente_persoana(self, personID):
        persoana = self._repo_persoane.find(personID)
        if persoana is None:
            raise ValueError("Persoana nu exista.")

        evenimente_participate = []
        toate_evenimentele = self._repo_evenimente.get_all()
        for ev in toate_evenimentele:
            if personID in ev.participanti:
                evenimente_participate.append(ev)

        return Sorter.generic_sort(
            evenimente_participate, 
            key=lambda e: (e.descriere, e.data, e.timp), # !!!!!!! a treia cheie
            algorithm='merge'
        )

    def raport_persoane_active(self):
        toate_persoanele = self._repo_persoane.get_all()
        toate_evenimentele = self._repo_evenimente.get_all()
        
        contor_participari = {p.personID: 0 for p in toate_persoanele}
        for ev in toate_evenimentele:
            for pid in ev.participanti:
                if pid in contor_participari:
                    contor_participari[pid] += 1

        rezultat = []
        for p in toate_persoanele:
            count = contor_participari[p.personID]
            if count > 0:
                rezultat.append( (p.nume, count) )
            
        return Sorter.generic_sort(
            rezultat, 
            key=lambda x: x[1], 
            reverse=True, 
            algorithm='bingo'
        )

    def raport_persoane_inactiv(self):
        toate_persoanele = self._repo_persoane.get_all()
        toate_evenimentele = self._repo_evenimente.get_all()
        
        contor_participari = {p.personID: 0 for p in toate_persoanele}

        for ev in toate_evenimentele:
            for pid in ev.participanti:
                if pid in contor_participari:
                    contor_participari[pid] += 1

        rezultat = []
        for p in toate_persoanele:
            count = contor_participari[p.personID]
            rezultat.append( (p.nume, count) )
            
        return Sorter.generic_sort(
            rezultat, 
            key=lambda x: x[1], 
            algorithm='merge'
        )

    def raport_top_20_evenimente(self):
        toate_evenimentele = self._repo_evenimente.get_all()
        lista_procesata = []
        for ev in toate_evenimentele:
            nr_participanti = len(ev.participanti)
            lista_procesata.append( (ev.descriere, nr_participanti) )
            
        lista_sortata = Sorter.generic_sort(
            lista_procesata, 
            key=lambda x: x[1], 
            reverse=True, 
            algorithm='bingo'
        )
        
        nr_total = len(lista_sortata)
        if nr_total == 0:
            return []
        limit = int(0.2 * nr_total) + 1
        return lista_sortata[:limit]