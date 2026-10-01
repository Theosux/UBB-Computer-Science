#include "service.h"
#include "validator.h"
#include <string.h>

void init_service(Service* s, Repo* r) {
    s->repo = r;
}

int adauga_produs(Service* s, int id, const char* tip, const char* prod, const char* model, int pret, int cant) {
    /*
    Adauga un produs in memorie cu datele primite
    param:
        id - int (id-ul unic al produsului)
        tip - char (tipul produsului)
        prod - char (producatorul produsului)
        model - char (modelul produsului)
        pret - int (pretul produsului)
        cant - int (cantitatea stocului disponibil)
    return: apeleaza functia adauga din repo
    */
    Produs p = create(id, tip, prod, model, pret, cant);
    if (!validator(p)) return 0;
    return adauga_repo(s->repo, p);
}

int actualizeaza_produs(Service* s, int id, int pret, int cant) {
    /*
    Actualizeaza un produs din memorie identificat cu id-ul cu date noi
    param:
        id - int
        pret - int
        cant - int
    return:
        0 - daca pretul sau cantitatea sunt mai mici ca 0
        apeleaza functia update din repo
    */
    if (pret < 0 || cant < 0) return 0;
    return update(s->repo, id, pret, cant);
}

int sterge_produs(Service* s, int id) {
    /*
    Sterge un produs din memorie identificat cu id-ul
    param:
        id - int
    return:
        apelul functiei din repo
    */
    return stergere(s->repo, id);
}

Repo filtreaza_producator(Service* s, const char* producator) {
    /*
    Filtreaza lista produselor dupa producator
    param:
        producator - char
    return:
        rezultat - lista filtrata
    */
    Repo rezultat;
    init_repo(&rezultat);
    for (int i = 0; i < s->repo->l; i++) {
        if (strcmp(s->repo->e[i].producator, producator) == 0) {
            adauga_repo(&rezultat, s->repo->e[i]);
        }
    }
    return rezultat;
}

Repo filtreaza_pret(Service* s, int pret_max) {
    /*
    Filtreaza lista produselor dupa pret maxim
    param:
        pret_max - int
    return:
        rezultat - lista filtrata
    */
    Repo rezultat;
    init_repo(&rezultat);
    for (int i = 0; i < s->repo->l; i++) {
        if (s->repo->e[i].pret <= pret_max) {
            adauga_repo(&rezultat, s->repo->e[i]);
        }
    }
    return rezultat;
}

Repo filtreaza_cantitate(Service* s, int cantitate_max) {
    /*
    Filtreaza lista produselor dupa pret maxim
    param:
        pret_max - int
    return:
        rezultat - lista filtrata
    */
    Repo rezultat;
    init_repo(&rezultat);
    for (int i = 0; i < s->repo->l; i++) {
        if (s->repo->e[i].cantitate <= cantitate_max) {
            adauga_repo(&rezultat, s->repo->e[i]);
        }
    }
    return rezultat;
}

Repo sorteaza_pret(Service* s, int descrescator) {
    /*
    Sorteaza lista produselor dupa pret, crescator sau descrescator
    param:
        descrescator - int (modul in care sortam)
    return:
        rezultat - lista filtrata
    */
    Repo rezultat = *(s->repo);
    for (int i = 0; i < rezultat.l - 1; i++) {
        for (int j = i + 1; j < rezultat.l; j++) {
            int conditie = descrescator ? (rezultat.e[i].pret < rezultat.e[j].pret)
                : (rezultat.e[i].pret > rezultat.e[j].pret);
            if (conditie) {
                Produs aux = rezultat.e[i];
                rezultat.e[i] = rezultat.e[j];
                rezultat.e[j] = aux;
            }
        }
    }
    return rezultat;
}