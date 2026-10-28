from p1functionsdict import prim, filtrare_prim, istoric_lista, undo


def _creeaza_numar_dict(r, i):
    return {"re": r, "im": i}

def stergere_numar_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei stergere_numar.
    """
    
    poz = 3
    lista_numere.pop(poz)
    return lista_numere

def stergere_interval_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei stergere_interval.
    """
    
    start = 2
    end = 4
    del lista_numere[start:end + 1]
    return lista_numere

def inlocuire_numar_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei inlocuire_numar_test.
    """
    

    numar_vechi = _creeaza_numar_dict(3, 4)
    numar_nou = _creeaza_numar_dict(0, 0)
    for i in range(len(lista_numere)):
        if lista_numere[i] == numar_vechi:
            lista_numere[i] = numar_nou
    return lista_numere

def parte_imaginara_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei parte_imaginara.
    """
    l = []
    start = 2
    end = 4
    for i in range(start, end + 1):
        l.append(lista_numere[i]["im"])
    return l

def modul_mic_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei modul_mic.
    """
    l = []
    for numar in lista_numere:
        modul = (numar["re"]**2 + numar["im"]**2)**0.5
        if modul < 10:
            l.append(_creeaza_numar_dict(numar["re"], numar["im"]))
    return l

def modul_egal_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei modul_egal.
    """
    l = []
    for numar in lista_numere:
        modul = (numar["re"]**2 + numar["im"]**2)**0.5
        if abs(modul - 10) < 1e-9:
            l.append(_creeaza_numar_dict(numar["re"], numar["im"]))
    return l

def suma_numere_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei suma_numere.
    """
    
    start = 2
    end = 4
    suma_r = 0
    suma_i = 0
    for i in range(start, end + 1):
        suma_r += lista_numere[i]["re"]
        suma_i += lista_numere[i]["im"]
    if suma_i >= 0:
        return(f"{suma_r}+{suma_i}i")
    else:
        return(f"{suma_r}{suma_i}i")

def produs_numere_test(lista_numere):
    
    """
    Functie test corespunzatoare functiei produs_numere.
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
        return(f"{produs_real}+{produs_imaginar}i")
    else:
        return(f"{produs_real}{produs_imaginar}i")

def modulx_test(lista_numere, x, option):

    """
    Functie test corespunzatoare functiei produs_numere.
    """

    l = []
    if option == '<':
        l = [numar for numar in lista_numere if (numar["re"]**2 + numar["im"]**2)**0.5 >= x]
    elif option == '>':
        l = [numar for numar in lista_numere if (numar["re"]**2 + numar["im"]**2)**0.5 <= x]
    elif option == '=':
        l = [numar for numar in lista_numere if not (numar["re"]**2 + numar["im"]**2)**0.5 == x]
    return l

def undo_test(lista_initiala):
    """
    Functie test pentru a verifica functionalitatea undo.
    Testeaza salvarea starii, o modificare si restaurarea starii anterioare (Starea B).
    """
    
    istoric_local = []
    l_test = lista_initiala.copy()
    

    istoric_lista(l_test, istoric_local) 
    
    l_test.pop(1) 
    

    istoric_lista(l_test, istoric_local) 

    l_test.append(_creeaza_numar_dict(99, 99))
    
    undo(l_test, istoric_local)
    
    return l_test



def teste():
    l = [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), 
        _creeaza_numar_dict(5, 12), _creeaza_numar_dict(1, 1), _creeaza_numar_dict(7, 24), 
        _creeaza_numar_dict(9, 12), _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    istoric = []
    istoric_lista(l, istoric)
    # 1. stergere_numar_test (Sterge elementul de la index 3: [5, 12])
    assert stergere_numar_test(l.copy()) == [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), 
        _creeaza_numar_dict(1, 1), _creeaza_numar_dict(7, 24), _creeaza_numar_dict(9, 12), 
        _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    
    # 2. stergere_interval_test (Sterge elementele de la index 2 la 4: [0, 10], [5, 12], [1, 1])
    assert stergere_interval_test(l.copy()) == [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(6, 8), 
        _creeaza_numar_dict(7, 24), _creeaza_numar_dict(9, 12), 
        _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    
    # 3. inlocuire_numar_test (Înlocuiește [3, 4] cu [0, 0])
    assert inlocuire_numar_test(l.copy()) == [
        _creeaza_numar_dict(0, 0), _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), 
        _creeaza_numar_dict(5, 12), _creeaza_numar_dict(1, 1), _creeaza_numar_dict(7, 24), 
        _creeaza_numar_dict(9, 12), _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    
    # 4. parte_imaginara_test (De la index 2 la 4: [0, 10], [5, 12], [1, 1] -> 10, 12, 1)
    assert parte_imaginara_test(l.copy()) == [10, 12, 1] 
    
    # 5. modul_mic_test (Modul < 10: [3, 4] (modul 5), [1, 1] (modul 1.41), [-3, -4] (modul 5))
    assert modul_mic_test(l.copy()) == [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(1, 1), _creeaza_numar_dict(-3, -4)
    ] 
    
    # 6. modul_egal_test (Modul = 10: [6, 8], [0, 10])
    assert modul_egal_test(l.copy()) == [
        _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10)
    ]
    
    # 7. suma_numere_test (De la index 2 la 4: [0, 10] + [5, 12] + [1, 1] = 6 + 23i)
    assert suma_numere_test(l.copy()) == "6+23i"
    
    # 8. produs_numere_test (Produsul tuturor numerelor din listă)
    assert produs_numere_test(l.copy()) == "288037500+53737500i"
    
    # 9. Teste prim
    assert prim(7) == True
    assert prim(10) == False
    
    # 10. filtrare_prim
    assert filtrare_prim(l.copy()) == [
        _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), _creeaza_numar_dict(1, 1), 
        _creeaza_numar_dict(9, 12), _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    # 11. modulx
    assert modulx_test(l.copy(), 10, '>') == [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), 
        _creeaza_numar_dict(1, 1), _creeaza_numar_dict(-3, -4)
    ]
    # Filtrare < 5
    assert modulx_test(l.copy(), 5, '<') == [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), 
        _creeaza_numar_dict(5, 12), _creeaza_numar_dict(7, 24), _creeaza_numar_dict(9, 12), 
        _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    # Filtrare > 5 
    assert modulx_test(l.copy(), 5, '>') == [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(1, 1), _creeaza_numar_dict(-3, -4)
    ]
    # Filtrare = 5
    assert modulx_test(l.copy(), 5, '=') == [
        _creeaza_numar_dict(6, 8), _creeaza_numar_dict(0, 10), _creeaza_numar_dict(5, 12), 
        _creeaza_numar_dict(1, 1), _creeaza_numar_dict(7, 24), _creeaza_numar_dict(9, 12), 
        _creeaza_numar_dict(8, 15)
    ]
    # 12. Undo 
    # Lista initiala, minus elementul de la index 1: [6, 8]
    l_dupa_undo = [
        _creeaza_numar_dict(3, 4), _creeaza_numar_dict(0, 10), 
        _creeaza_numar_dict(5, 12), _creeaza_numar_dict(1, 1), _creeaza_numar_dict(7, 24), 
        _creeaza_numar_dict(9, 12), _creeaza_numar_dict(8, 15), _creeaza_numar_dict(-3, -4)
    ]
    
    assert undo_test(l.copy()) == l_dupa_undo