from p1UIprints import print_adaugare_ui


def get_ui_choice():

    """
    Obtine optiunea ui-ului.
    input: -
    output: choice - int
    """

    while True:
        try:
            choice = int(input("Alegeti optiunea ui: "))
            return choice
        except ValueError:
                print("Introduceti un numar!")
                continue


def creare_numar():

    """
    Creeaza un numar complex citit de la tastatura.
    input: -
    output: tuplu (parte reala, parte imaginara)
    """

    while True:
        negativ = False
        numar = input("Introduceti numarul: ").replace(" ", "")
        try:
            if numar[0] == "-":
                numar = numar[1:]
                negativ = True
            if "+" in numar[1:]:
                semn = "+"
            elif "-" in numar[1:]:
                semn = "-"
            else: 
                raise ValueError("Format invalid(lipsa semn)")
            numar_complex = numar.split(semn)
            if numar_complex[1] in ("i", "+i", "-i"):
                numar_complex[1] = "1i"
                
            parte_reala = int(numar_complex[0])
            if negativ:
                parte_reala = -parte_reala
            parte_imaginara = int(numar_complex[1][:-1])
            if semn == "-":
                parte_imaginara = -parte_imaginara
            return {"re": parte_reala, "im": parte_imaginara}
            
        except ValueError:
            print("Format invalid. Reincercati.")


def creare_numar_doi(numar):
    
    """
    Creare numar fara input
    input: -
    output: tuplu (parte reala, parte imaginara)
    """

    while True:
        negativ = False
        numar = numar.replace(" ", "")
        try:
            if numar[0] == "-":
                numar = numar[1:]
                negativ = True
            if "+" in numar[1:]:
                semn = "+"
            elif "-" in numar[1:]:
                semn = "-"
            else: 
                raise ValueError("Format invalid(lipsa semn)")
            numar_complex = numar.split(semn)
            if numar_complex[1] in ("i", "+i", "-i"):
                numar_complex[1] = "1i"
                
            parte_reala = int(numar_complex[0])
            if negativ:
                parte_reala = -parte_reala
            parte_imaginara = int(numar_complex[1][:-1])
            if semn == "-":
                parte_imaginara = -parte_imaginara
            return {"re": parte_reala, "im": parte_imaginara}
            
        except ValueError:
            print("Format invalid. Reincercati.")


def get_sentence():
    """
    Obtine propozitie
    input: -
    output: prompt - string
    """
    prompt = input("Scrie promptul: ")
    return prompt

def parse_prompt(prompt, l, istoric):
    """
    Desparte promptul in functii cunoscute pe care le utilizeaza si le apeleaza
    input: promptul - string, l - lista de dict, istoric - lista de lista de dict
    output:
    """
    subprompt = prompt.split(", ")
    i = 0
    while i < len(subprompt):
        if "adauga" in subprompt[i]:
            parts = subprompt[i].split(" ")
            numar = parts[1]
            numar = creare_numar_doi(numar)
            istoric_lista(l, istoric)
            adaugare_numar_doi(l, numar)
        elif "sterge" in subprompt[i]:
            parts = subprompt[i].split(" ")
            numar = parts[1]
            numar = creare_numar_doi(numar)
            istoric_lista(l, istoric)
            sterge_ui2(l, numar)
        elif "undo" in subprompt[i]:
            undo(l, istoric)

        elif "afisare" in subprompt[i]:
            afisare_numere(l)
        i += 1


def sterge_ui2(l, numar):

    """
    Sterge pt ui2
    """

    l.remove(numar)




def get_option():

    """
    Obtine optiune
    input: -
    output: i - int
    """

    while True:
        try:
            option = int(input("Alege optiunea: "))
            return option
        except ValueError:
            print("Optiune invalida. Introduceti un numar.")
            continue


def get_sub_option():

    """
    Obtine suboptiune
    input: -
    output: i - int
    """
    while True:
        try:
            option = int(input("Alege suboptiunea: "))
            return option
        except ValueError:
            print("Optiune invalida. Introduceti un numar.")
            continue

def get_optiune_adaugare():

    """
    Obtine optiunea pentru functia adaugare_numar
    input: -
    output: i - int
    """

    while True:
        try:
            i = int(input("Alegeti optiunea: "))
            return i
        except ValueError:
            print("Format invalid. Reincercati.")
            continue


def get_poz_adaugare():

    """
    Obtine pozitia pentru functia adaugare_numar
    input: -
    output: poz - int
    """

    while True:
        try:
            poz = int(input("Introduceti pozitia: "))
            return poz
        except ValueError:
            print("Format invalid. Reincercati.")
            continue


def adaugare_numar(lista_numere):

    """
    Adauga un numar complex la sfarsitul listei sau pe o pozitie data.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """

    print_adaugare_ui() #printeaza comenzile de adaugare
    i = get_optiune_adaugare()
    if i == 1:
        numar = creare_numar()
        lista_numere.append(numar)
    elif i == 2:
        poz = get_poz_adaugare()
        numar = creare_numar()
        lista_numere.insert(poz, numar)


def adaugare_numar_doi(lista_numere, numar):

    """
    Adaugare numar pt ui 2
    """

    lista_numere.append(numar)


def afisare_numere(lista_numere):
    
    """
    Afiseaza toate numerele complexe din lista.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """
    if lista_numere == []:
        print("Nu exista nimic de afisat")
        return 0
    for numar in lista_numere:
        if numar["im"] >= 0:
            print(f"{numar['re']}+{numar['im']}i")
        else:
            print(f"{numar['re']}{numar['im']}i")


def get_poz_interval():

    """
    Obtine pozitiile pentru un interval
    input: -
    output: start, end - int 
    """

    while True:
        try:
            start = int(input("Introduceti pozitia de start: "))
            end = int(input("Introduceti pozitia de sfarsit: "))
            return start, end
        except ValueError:
            print("Format invalid. Reincercati.")
            continue


def get_poz_stergere():

    """
    Obtine pozitia pentru stergerea unui nr complex din lista
    input: -
    output: poz - int 
    """

    while True:
        try:
            poz = int(input("Introduceti pozitia numarului de sters: "))
            return poz
        except ValueError:
            print("Format invalid. Reincercati.")
            continue


def stergere_numar(lista_numere):

    """
    Sterge un numar complex de pe o pozitie data.
    input: lista_numere - lista de numere complexe
    output: -
    """
    
    poz = get_poz_stergere()
    lista_numere.pop(poz)


def stergere_interval(lista_numere):

    """
    Sterge un interval de numere complexe din lista.
    input: lista_numere - lista de numere complexe
    output: -
    """
    
    start, end = get_poz_interval()
    del lista_numere[start:end + 1]


def inlocuire_numar(lista_numere):
    
    """
    Inlocuieste toate aparitiile unui numar complex cu altul.
    input: lista_numere - lista de numere complexe
    output: -
    """
    
    numar_vechi = creare_numar()
    numar_nou = creare_numar()
    for i in range(len(lista_numere)):
        if lista_numere[i] == numar_vechi:
            lista_numere[i] = numar_nou


def parte_imaginara(lista_numere):
    
    """
    Afiseaza partea imaginara a numerelor complexe dintr-un interval dat.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """
    
    start, end = get_poz_interval()
    for i in range(start, end + 1):
        print(f"{lista_numere[i]['im']}")


def modul_mic(lista_numere):
    
    """
    Afiseaza numerele complexe al caror modul este mai mic decat 10.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """
    
    for numar in lista_numere:
        modul = (numar["re"]**2 + numar["im"]**2)**0.5
        if modul < 10:
            if numar["im"] >= 0:
                print(f"{numar['re']}+{numar['im']}i")
            else:
                print(f"{numar['re']}{numar['im']}i")


def modul_egal(lista_numere):
    
    """
    Afiseaza numerele complexe al caror modul este egal cu 10.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """
    
    for numar in lista_numere:
        modul = (numar["re"]**2 + numar["im"]**2)**0.5
        if modul == 10:
            if numar["im"] >= 0:
                print(f"{numar['re']}+{numar['im']}i")
            else:
                print(f"{numar['re']}{numar['im']}i")


def suma_numere(lista_numere):
    
    """
    Calculeaza si afiseaza suma numerelor complexe dintr-un interval dat.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """
    
    start, end = get_poz_interval()
    suma_r = 0
    suma_i = 0
    for i in range(start, end + 1):
        suma_r += lista_numere[i]["re"]
        suma_i += lista_numere[i]["im"]
    if suma_i >= 0:
        print(f"Suma numerelor din interval este: {suma_r}+{suma_i}i")
    else:
        print(f"Suma numerelor din interval este: {suma_r}{suma_i}i")
        

def produs_numere(lista_numere):
    
    """
    Calculeaza si afiseaza produsul numerelor complexe dintr-o lista data.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """
    produs_real = lista_numere[0]["re"]
    produs_imaginar = lista_numere[0]["im"]
    
    for i in range(1, len(lista_numere)):
        c = lista_numere[i]["re"]
        d = lista_numere[i]["im"]
        
        n_produs_real = (produs_real * c) - (produs_imaginar * d)
        n_produs_imaginar = (produs_real * d) + (produs_imaginar * c)
        produs_real, produs_imaginar = n_produs_real, n_produs_imaginar
        
    if produs_imaginar >= 0:
        print(f"{produs_real}+{produs_imaginar}i")
    else:
        print(f"{produs_real}{produs_imaginar}i")


def produs_subsecventa(lista_numere):

    """
    Calculeaza si afiseaza produsul numerelor complexe dintr-o subsecventa data.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: -
    """

    start, end = get_poz_interval()
    produs_numere(lista_numere[start:end + 1])


def list_sort(lista_numere):

    """
    Afiseaza o lista sortata descrescator dupa partea imaginara.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: l - lista sortata (listă de dict-uri)
    """

    lc = lista_numere.copy()
    lc.sort(key=lambda x: x["im"], reverse=True)
    afisare_numere(lc)


def prim(n):
    
    """
    Verifica daca un numar este prim.
    input: n - numar intreg
    output: True/False
    """
    
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True


def filtrare_prim(lista_numere):
    
    """
    Filtreaza numerele complexe a caror parte reala este un numar prim.
    input: lista_numere - lista de numere complexe (dict-uri)
    output: l - lista filtrata (continua sa fie o listă de dict-uri)
    """
    l = []
    l = [numar for numar in lista_numere if not prim(numar["re"])]
    return l


def istoric_lista(lista, istoric):
    
    """
    Salveaza starea curenta a listei in istoric.
    input: lista - lista curenta de numere complexe
            istoric - lista de stari anterioare
    output: -
    """
    
    istoric.append(lista.copy())


def undo(lista, istoric):
    
    """
    Revine la starea anterioara a listei folosind istoric.
    input: lista - lista curenta de numere complexe
            istoric - lista de stari anterioare
    output: -
    """
    
    if istoric:
        lista[:] = istoric.pop()
    else:
        print("Nu exista actiuni de anulat.")


def get_modulx_option():

    """
    Primeste optiunea pentru functionalitatea filtrarii modul
    input: -
    output: option - int
    """

    while True:
        try:
            option = int(input("alege optiunea: "))
            return option
        except ValueError:
            print("Format invalid. Reincercati.")
            continue


def get_modulx_value():

    """
    Primeste valoarea pentru functionalitatea filtrarii modul
    input: -
    output: x - int
    """

    while True:
        try:
            x = int(input("Introduceti x: "))
            return x
        except ValueError:
            print("Format invalid. Reincercati.")
            continue


def option_modifier(option):

    """
    Transforma pe option in semnul de comparare
    input: option - string
    output: option - int
    """

    if option == 1:
        option = '<'
    elif option == 2:
        option = '>'
    elif option == 3:
        option = '='
    return option


def modulx(lista_numere):

    """
    Filtreaza numerele complexe in functie de modul si o conditie data.
    input: lista_numere - lista de numere complexe (dict-uri)
            x - valoarea de comparat
            conditie - conditia de filtrare ('<', '>', '=')
    output: l - lista filtrata (listă de dict-uri)
    """

    l = []
    option = get_modulx_option()
    option = option_modifier(option)
    x = get_modulx_value()
    if option == '<':
        l = [numar for numar in lista_numere if (numar["re"]**2 + numar["im"]**2)**0.5 >= x]
    elif option == '>':
        l = [numar for numar in lista_numere if (numar["re"]**2 + numar["im"]**2)**0.5 <= x]
    elif option == '=':
        l = [numar for numar in lista_numere if not (numar["re"]**2 + numar["im"]**2)**0.5 == x]
    return l