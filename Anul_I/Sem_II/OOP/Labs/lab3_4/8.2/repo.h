#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "domain.h"

typedef struct {
    Produs* e;
    int l;
    int capacitate; // *.2 capacitatea alocata max in memorie la acest moment
} Repo;

void init_repo(Repo* r);

int cauta_repo(Repo* r, int id);
/*
Cauta un produs cu id-ul dat in memorie
param: id - int
return: indexul obiectului in lista, sau -1 daca nu il gaseste
*/

int adauga_repo(Repo* r, Produs p);
/*
Adauga un produs in memorie sau ii creste cantitatea
param: p - produsul de tip struct
return: 1 - pt un produs adaugat, 2 - pt un produs existent la care crestem cantitatea
*/

int update(Repo* r, int id, int pret_nou, int cantitate_nou);
/*
Actualizam un produs din memorie
param:
    id - int
    pret_nou - int
    cantitate_nou - int
return: 0, daca produsul nu a fost gasit; 1, altfel
*/

int stergere(Repo* r, int id);
/*
Stergem un produs din memorie
param:
    id - int
return: 0, daca produsul nu a fost gasit; 1, altfel
*/

void destroy_repo(Repo* r);
/*
Dealoca memoria din repo
param: -
*/

#endif