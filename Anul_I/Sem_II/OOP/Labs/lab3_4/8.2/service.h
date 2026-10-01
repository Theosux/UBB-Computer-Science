#ifndef SERVICE_H
#define SERVICE_H
#include "repo.h"

typedef struct {
    Repo* repo;
} Service;

typedef int (*FunctieComparare)(Produs* p1, Produs* p2);

void init_service(Service* s, Repo* r);

int adauga_produs(Service* s, int id, const char* tip, const char* prod, const char* model, int pret, int cant);
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

int actualizeaza_produs(Service* s, int id, int pret, int cant);
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

int sterge_produs(Service* s, int id);
/*
Sterge un produs din memorie identificat cu id-ul
param:
    id - int
return:
    apelul functiei din repo
*/


Repo filtreaza_producator(Service* s, const char* producator);
/*
Filtreaza lista produselor dupa producator
param:
    producator - char
return:
    rezultat - lista filtrata
*/

Repo filtreaza_pret(Service* s, int pret_max);
/*
Filtreaza lista produselor dupa pret maxim
param:
    pret_max - int
return:
    rezultat - lista filtrata
*/

Repo filtreaza_cantitate(Service* s, int cantitate_max);
/*
Filtreaza lista produselor dupa pret maxim
param:
    pret_max - int
return:
    rezultat - lista filtrata
*/


Repo sorteaza_nou(Service* s, FunctieComparare cmpF);
/*
*/

Repo sorteaza_pret_cresc(Service* s);
/*
*/

Repo sorteaza_pret_desc(Service* s);
/*
*/

#endif