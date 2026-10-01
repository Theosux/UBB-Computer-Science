#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "domain.h"

typedef struct {
    Produs e[100];
    int l;
} Repo;

void init_repo(Repo* r);
int cauta_repo(Repo* r, int id);
int adauga_repo(Repo* r, Produs p);
int update(Repo* r, int id, int pret_nou, int cantitate_nou);
int stergere(Repo* r, int id);

#endif