#include "repo.h"
#include <string.h>
#include <stdlib.h>

void init_repo(Repo* r) {
    r->capacitate = 2;
    r->l = 0;
    r->e = malloc(r->capacitate * sizeof(Produs));
}

void destroy_repo(Repo* r) {

    for (int i = 0; i < r->l; i++) {
        destroy_produs(&r->e[i]);
    }

    free(r->e);
    r->e = NULL;
    r->l = 0;
    r->capacitate = 0;
}

void resize(Repo* r) {
    int cap = 2 * r->capacitate;
    Produs* nrEl = malloc(cap * sizeof(Produs));

    for (int i = 0; i < r->l; i++) {
        nrEl[i] = r->e[i];
    }   
    free(r->e);

    r->e = nrEl;

    r->capacitate = cap;
}

int cauta_repo(Repo* r, int id) {
    for (int i = 0; i < r->l; i++) {
        if (r->e[i].id == id) return i;
    }
    return -1;
}

int adauga_repo(Repo* r, Produs p) {
    int index = cauta_repo(r, p.id);
    if (index != -1) {
        if (strcmp(r->e[index].tip, p.tip) == 0 && strcmp(r->e[index].producator, p.producator) == 0 && strcmp(r->e[index].model, p.model) == 0 && r->e[index].pret == p.pret) {
            r->e[index].cantitate += p.cantitate;
            destroy_produs(&p);
            return 2;
        }
        destroy_produs(&p);
        return 3;
    }
    if (r->l == r->capacitate) {
        resize(r);
    }
    r->e[r->l++] = p;
    return 1;
}

int update(Repo* r, int id, int pret_nou, int cantitate_nou) {
    int index = cauta_repo(r, id);
    if (index == -1) return 0;
    r->e[index].pret = pret_nou;
    r->e[index].cantitate = cantitate_nou;
    return 1;
}

int stergere(Repo* r, int id) {
    int index = cauta_repo(r, id);
    if (index == -1) return 0;

    destroy_produs(&r->e[index]);

    for (int i = index; i < r->l - 1; i++) {
        r->e[i] = r->e[i + 1];
    }
    r->l--;
    return 1;
}