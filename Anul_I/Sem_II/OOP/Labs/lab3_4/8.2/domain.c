#include "domain.h"
#include <string.h>
#include <stdlib.h>

Produs create(int id, const char* tip, const char* producator, const char* model, int pret, int cantitate) {
    Produs p;
    p.id = id;

    p.tip = malloc((strlen(tip) + 1) * sizeof(char));
    strcpy_s(p.tip, strlen(tip) + 1, tip);


    p.producator = malloc((strlen(producator) + 1) * sizeof(char));
    strcpy_s(p.producator, strlen(producator) + 1, producator);

    p.model = malloc((strlen(model) + 1) * sizeof(char));
    strcpy_s(p.model, strlen(model) + 1, model);

    p.pret = pret;
    p.cantitate = cantitate;

    return p;
}

void destroy_produs(Produs* p) {
    free(p->tip);
    free(p->producator);
    free(p->model);

    p->tip = NULL;
    p->producator = NULL;
    p->model = NULL;

    p->id = -1;
    p->pret = -1;
    p->cantitate = -1;
    // pt a nu da referinta la memorie invalida
}

Produs copy_produs(Produs* p) {
    return create(p->id, p->tip, p->producator, p->model, p->pret, p->cantitate);
}