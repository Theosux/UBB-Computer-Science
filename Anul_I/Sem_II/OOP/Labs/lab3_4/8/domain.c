#include "domain.h"
#include <string.h>

Produs create(int id, const char* tip, const char* producator, const char* model, int pret, int cantitate) {
    Produs p;
    p.id = id;

    strncpy_s(p.tip, 100, tip, 99);
    p.tip[99] = '\0';

    strncpy_s(p.producator, 100, producator, 99);
    p.producator[99] = '\0';

    strncpy_s(p.model, 100, model, 99);
    p.model[99] = '\0';

    p.pret = pret;
    p.cantitate = cantitate;

    return p;
}