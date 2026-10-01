#ifndef SERVICE_H
#define SERVICE_H
#include "repo.h"

typedef struct {
    Repo* repo;
} Service;

void init_service(Service* s, Repo* r);
int adauga_produs(Service* s, int id, const char* tip, const char* prod, const char* model, int pret, int cant);
int actualizeaza_produs(Service* s, int id, int pret, int cant);
int sterge_produs(Service* s, int id);

Repo filtreaza_producator(Service* s, const char* producator);
Repo filtreaza_pret(Service* s, int pret_max);
Repo filtreaza_cantitate(Service* s, int cantitate_max);

Repo sorteaza_pret(Service* s, int descrescator);

#endif