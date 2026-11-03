class Consola:
    def __init__(self, service_persoane, service_evenimente):
        self._srv_pers = service_persoane
        self._srv_ev = service_evenimente
        
        self._comenzi = {
            '1': self._ui_gestiune_persoane,
            '2': self._ui_gestiune_evenimente,
            '3': self._ui_cautari,
            '4': self._ui_inscrieri,
            '5': self._ui_rapoarte,
            '0': self._ui_exit
        }

    def _print_menu(self):
        print("\n--- MENIU PRINCIPAL ---")
        print("1. Gestiune Persoane")
        print("2. Gestiune Evenimente")
        print("3. Căutări (Persoane/Evenimente)")
        print("4. Înscriere la eveniment")
        print("5. Rapoarte")
        print("0. Ieșire")

    # --- FUNCTII AJUTATOARE ---

    def _afiseaza_lista(self, lista, titlu):
        print(f"\n--- {titlu} ---")
        if not lista:
            print("Lista este goală.")
            return
        for obiect in lista:
            print(obiect) 
        print(f"Total înregistrări: {len(lista)}")
        
    def _citeste_persoana(self):
        personID = input("ID Persoană: ")
        nume = input("Nume: ")
        adresa = input("Adresă: ")
        return personID, nume, adresa
        
    def _citeste_eveniment(self):
        ID = input("ID Eveniment: ")
        data = input("Dată (DD.MM.YYYY): ")
        timp = input("Timp (HH:MM): ")
        descriere = input("Descriere: ")
        return ID, data, timp, descriere

    # --- 1. GESTIUNE PERSOANE ---
    
    def _ui_gestiune_persoane(self):
        while True:
            self._print_menu_persoane()
            opt = input("Alegeți opțiunea: ")
            if opt == '1':
                self._ui_adauga_persoana()
            elif opt == '2':
                self._ui_sterge_persoana()
            elif opt == '3':
                self._ui_modifica_persoana()
            elif opt == '4':
                self._afiseaza_lista(self._srv_pers.get_all(), "LISTA PERSOANELOR")
            elif opt == '5':
                self._ui_adauga_persoana_random()
            elif opt == '0':
                break
            else:
                print("Opțiune invalidă.")

    def _print_menu_persoane(self):
        print("\n--- GESTIUNE PERSOANE ---")
        print("1. Adaugă persoană")
        print("2. Șterge persoană")
        print("3. Modifică persoană")
        print("4. Afișează toate persoanele")
        print("5. Generează persoane random") 
        print("0. Back") 

    def _ui_adauga_persoana(self):
        try:
            personID, nume, adresa = self._citeste_persoana()
            self._srv_pers.adauga_persoana(personID, nume, adresa)
            print("Persoana a fost adăugată!")
        except ValueError as e:
            print(f"Eroare: {e}")

    def _ui_adauga_persoana_random(self):
        try:
            str_nr = input("Introduceți numărul de persoane de generat: ")
            nr = int(str_nr)
            
            if nr <= 0:
                print("Numărul trebuie să fie pozitiv.")
                return

            print("Se generează persoanele...")
            for _ in range(nr):
                self._srv_pers.adauga_persoana_random()
            
            print(f"S-au generat {nr} persoane random!")
            
        except ValueError:
            print("Eroare: Trebuie introdus un număr întreg și valid.")
        except Exception as e:
            print(f"Eroare: {e}")

    def _ui_sterge_persoana(self):
        try:
            personID = input("ID Persoană de șters: ")
            self._srv_pers.sterge_persoana(personID)
            print("Persoană a fost ștearsă!")
        except ValueError as e:
            print(f"Eroare: {e}")

    def _ui_modifica_persoana(self):
        try:
            personID = input("ID Persoană de modificat: ")
            nume = input("Nume nou: ")
            adresa = input("Adresă nouă: ")
            self._srv_pers.modifica_persoana(personID, nume, adresa)
            print("Persoana a fost modificată!")
        except ValueError as e:
            print(f"Eroare: {e}")
            
    # --- 2. GESTIUNE EVENIMENTE ---

    def _ui_gestiune_evenimente(self):
        while True:
            self._print_menu_evenimente()
            opt = input("Alegeți opțiunea: ")
            if opt == '1':
                self._ui_adauga_eveniment()
            elif opt == '2':
                self._ui_sterge_eveniment()
            elif opt == '3':
                self._ui_modifica_eveniment()
            elif opt == '4':
                self._afiseaza_lista(self._srv_ev.get_all(), "LISTA EVENIMENTELOR")
            elif opt == '5':
                self._ui_adauga_eveniment_random()
            elif opt == '0':
                break
            else:
                print("Opțiune invalidă.")

    def _print_menu_evenimente(self):
        print("\n--- GESTIUNE EVENIMENTE ---")
        print("1. Adaugă eveniment")
        print("2. Șterge eveniment")
        print("3. Modifică eveniment")
        print("4. Afișează toate evenimentele")
        print("5. Generează evenimente random")
        print("0. Back")

    def _ui_adauga_eveniment(self):
        try:
            ID, data, timp, descriere = self._citeste_eveniment()
            self._srv_ev.adauga_eveniment(ID, data, timp, descriere)
            print("Eveniment adăugat!")
        except ValueError as e:
            print(f"Eroare: {e}")
            
    def _ui_adauga_eveniment_random(self):
        try:
            str_nr = input("Introduceți numărul de evenimente de generat: ")
            nr = int(str_nr)

            if nr <= 0:
                print("Numărul trebuie să fie pozitiv.")
                return

            print("Se generează evenimentele...")
            for _ in range(nr):
                self._srv_ev.adauga_eveniment_random()

            print(f"S-au generat {nr} evenimente random!")

        except ValueError:
            print("Eroare: Trebuie să introduceți un număr întreg valid.")
        except Exception as e:
            print(f"Eroare: {e}")

    def _ui_sterge_eveniment(self):
        try:
            ID = input("ID Eveniment de șters: ")
            self._srv_ev.sterge_eveniment(ID)
            print("Eveniment șters cu succes!")
        except ValueError as e:
            print(f"Eroare: {e}")

    def _ui_modifica_eveniment(self):
        try:
            ID = input("ID Eveniment de modificat: ")
            data = input("Dată NOUĂ (DD.MM.YYYY): ")
            timp = input("Timp NOU (HH:MM): ")
            descriere = input("Descriere NOUĂ: ")
            self._srv_ev.modifica_eveniment(ID, data, timp, descriere)
            print("Eveniment modificat cu succes!")
        except ValueError as e:
            print(f"Eroare: {e}")

    # --- 3. CAUTARI ---

    def _ui_cautari(self):
        print("\n--- CĂUTĂRI ---")
        print("1. Căutare Persoane după șir de caractere")
        print("2. Căutare Evenimente după dată/timp/descriere")
        print("0. Înapoi la meniul principal")
        opt = input("Alegeți opțiunea: ")
        if opt == '1':
            self._ui_cauta_persoana()
        elif opt == '2':
            self._ui_cauta_eveniment()
        elif opt == '0':
            return
        else:
            print("Opțiune invalidă.")

    def _ui_cauta_persoana(self):
        sir = input("Introduceți nume (sau parte din nume) pentru căutare: ")
        print("Alegeti metoda de cautare:")
        print("1. Iterativă")
        print("2. Recursivă")
        opt = input("Alegeți metoda: ")
        if opt == '1':
            rezultate = self._srv_pers.cauta_persoane(sir)
        elif opt == '2':
            rezultate = self._srv_pers.cauta_persoane_recursive(sir)
        else:
            print("Opțiune invalidă.")
            return
        self._afiseaza_lista(rezultate, f"Rezultatele căutării pentru '{sir}'")

    def _ui_cauta_eveniment(self):
        sir = input("Introduceți descriere/data/timp pentru căutare: ")
        print("Alegeti metoda de cautare:")
        print("1. Iterativă")
        print("2. Recursivă")
        opt = input("Alegeți metoda: ")
        if opt == '1':
            rezultate = self._srv_ev.cauta_evenimente(sir)
        elif opt == '2':
            rezultate = self._srv_ev.cauta_evenimente_recursive(sir)
        else:
            print("Opțiune invalidă.")
            return
        self._afiseaza_lista(rezultate, f"Rezultatele căutării pentru '{sir}'")

    # --- 4. INSCRIERI ---

    def _ui_inscrieri(self):
        print("\n--- INSCRIERE PERSOANA LA EVENIMENT ---")
        try:
            id_persoana = input("ID Persoana: ")
            id_eveniment = input("ID Eveniment: ")
            
            self._srv_ev.inscrie_persoana(id_persoana, id_eveniment)
            print("Inscriere realizată cu succes!")
        except ValueError as e:
            print(f"Eroare înscriere: {e}")

    # --- 5. RAPOARTE ---

    def _ui_rapoarte(self):
        while True:
            print("\n--- RAPOARTE ---")
            print("1. Evenimente pentru o persoană")
            print("2. Cele mai active persoane")
            print("3. Top 20% evenimente")
            print("4. Cele mai puțin active persoane")
            print("0. Înapoi")
            
            opt = input("Opțiunea: ")
            
            if opt == '1':
                self._raport_1()
            elif opt == '2':
                self._raport_2()
            elif opt == '3':
                self._raport_3()
            elif opt == '4':
                self._raport_4()
            elif opt == '0':
                break
            else:
                print("Opțiune invalidă.")

    def _raport_1(self):
        id_pers = input("ID Persoană: ")
        try:
            rezultat = self._srv_ev.raport_evenimente_persoana(id_pers)
            self._afiseaza_lista(rezultat, "Evenimentele persoanei")
        except ValueError as e:
            print(f"Eroare: {e}")

    def _raport_2(self):
        rezultat = self._srv_ev.raport_persoane_active()
        print("\n--- CELE MAI ACTIVE PERSOANE ---")
        print(f"{'NUME':<20} | {'NR. EVENIMENTE'}")
        print("-" * 40)
        for nume, count in rezultat:
            print(f"{nume:<20} | {count}")

    def _raport_3(self):
        rezultat = self._srv_ev.raport_top_20_evenimente()
        print("\n--- TOP 20% EVENIMENTE ---")
        print(f"{'DESCRIERE':<20} | {'NR. PARTICIPANȚI'}")
        print("-" * 40)
        for desc, count in rezultat:
            print(f"{desc:<20} | {count}")

    def _raport_4(self):
            try:
                rezultat = self._srv_ev.raport_persoane_inactiv()
                print("\n--- CELE MAI PUȚIN ACTIVE PERSOANE ---")
                print(f"{'NUME':<20} | {'NR. EVENIMENTE'}")
                print("-" * 40)
                for nume, count in rezultat:
                    print(f"{nume:<20} | {count}")
            except Exception as e:
                print(f"Eroare la generarea raportului: {e}")

    def _ui_exit(self):
        print("Aplicația se închide. La revedere!")
        exit(0)

    # --- BUCLA PRINCIPALA ---
    
    def run(self):
        while True:
            self._print_menu()
            cmd = input("Introduceți comanda: ")
            if cmd in self._comenzi:
                self._comenzi[cmd]()
            else:
                print("Comandă invalidă.")
    
    # --- FUNCTII AJUTATOARE ---
def prints():
    print("Alegeți metoda de stocare:")
    print("1. Memorie (nu se salvează la ieșire)")
    print("2. Fișiere Text (.txt)")
    print("3. Fișiere json")
    print("0. Ieșire")