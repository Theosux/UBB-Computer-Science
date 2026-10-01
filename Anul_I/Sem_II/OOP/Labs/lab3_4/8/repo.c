#include "repo.h"

void init_repo(Repo* r) {
    r->l = 0;
}

int cauta_repo(Repo* r, int id) {
    /*
    Cauta un produs cu id-ul dat in memorie
    param: id - int
    return: indexul obiectului in lista, sau -1 daca nu il gaseste
    */
    for (int i = 0; i < r->l; i++) {
        if (r->e[i].id == id) return i;
    }
    return -1;
}

int adauga_repo(Repo* r, Produs p) {
    /*
    Adauga un produs in memorie sau ii creste cantitatea
    param: p - produsul de tip struct
    return: 1 - pt un produs adaugat, 2 - pt un produs existent la care crestem cantitatea
    */
    int index = cauta_repo(r, p.id);
    if (index != -1) {
        r->e[index].cantitate += p.cantitate;
        return 2;
    }
    if (r->l >= 100) return 0;
    r->e[r->l++] = p;
    return 1;
}

int update(Repo* r, int id, int pret_nou, int cantitate_nou) {
    /*
    Actualizam un produs din memorie
    param:
        id - int
        pret_nou - int
        cantitate_nou - int
    return: 0, daca produsul nu a fost gasit; 1, altfel
    */
    int index = cauta_repo(r, id);
    if (index == -1) return 0;
    r->e[index].pret = pret_nou;
    r->e[index].cantitate = cantitate_nou;
    return 1;
}

int stergere(Repo* r, int id) {
    /*
    Stergem un produs din memorie
    param:
        id - int
    return: 0, daca produsul nu a fost gasit; 1, altfel
    */
    int index = cauta_repo(r, id);
    if (index == -1) return 0;
    for (int i = index; i < r->l - 1; i++) {
        r->e[i] = r->e[i + 1];
    }
    r->l--;
    return 1;
}