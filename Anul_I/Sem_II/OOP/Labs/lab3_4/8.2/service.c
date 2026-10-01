#include "service.h"
#include "validator.h"
#include "domain.h"
#include <string.h>

void init_service(Service* s, Repo* r) {
    s->repo = r;
}

int adauga_produs(Service* s, int id, const char* tip, const char* prod, const char* model, int pret, int cant) {
    Produs p = create(id, tip, prod, model, pret, cant);
    if (!validator(p)) {
        destroy_produs(&p);
        return 0;
    }
    return adauga_repo(s->repo, p);
}

int actualizeaza_produs(Service* s, int id, int pret, int cant) {
    if (pret < 0 || cant < 0) return 0;
    return update(s->repo, id, pret, cant);
}

int sterge_produs(Service* s, int id) {
    return stergere(s->repo, id);
}

Repo filtreaza_producator(Service* s, const char* producator) {
    Repo rezultat;
    init_repo(&rezultat);
    for (int i = 0; i < s->repo->l; i++) {
        if (strcmp(s->repo->e[i].producator, producator) == 0) {
            adauga_repo(&rezultat, copy_produs(&s->repo->e[i]));
        }
    }
    return rezultat;
}

Repo filtreaza_pret(Service* s, int pret_max) {
    Repo rezultat;
    init_repo(&rezultat);
    for (int i = 0; i < s->repo->l; i++) {
        if (s->repo->e[i].pret <= pret_max) {
            adauga_repo(&rezultat, copy_produs(&s->repo->e[i]));
        }
    }
    return rezultat;
}

Repo filtreaza_cantitate(Service* s, int cantitate_max) {
    Repo rezultat;
    init_repo(&rezultat);
    for (int i = 0; i < s->repo->l; i++) {
        if (s->repo->e[i].cantitate <= cantitate_max) {
            adauga_repo(&rezultat, copy_produs(&s->repo->e[i]));
        }
    }
    return rezultat;
}

int cmpPretCresc(Produs* p1, Produs* p2) {
    return p1->pret - p2->pret;
}

int cmpPretDescresc(Produs* p1, Produs* p2) {
    return p2->pret - p1->pret;
}

Repo sortare_noua(Service* s, FunctieComparare cmpF) {
    Repo rezultat;
    init_repo(&rezultat);

    for (int i = 0; i < s->repo->l; i++) {
        adauga_repo(&rezultat, copy_produs(&s->repo->e[i]));
    }
    for (int i = 0; i < rezultat.l - 1; i++) {
        for (int j = i + 1; j < rezultat.l; j++) {
            if (cmpF(&rezultat.e[i], &rezultat.e[j]) > 0) {
                Produs aux = rezultat.e[i];
                rezultat.e[i] = rezultat.e[j];
                rezultat.e[j] = aux;
            }
        }
    }

    return rezultat;
}

Repo sorteaza_pret_cresc(Service* s) {
    return sortare_noua(s, cmpPretCresc);
}

Repo sorteaza_pret_desc(Service* s) {
    return sortare_noua(s, cmpPretDescresc);

}
/*

Repo sorteaza_pret(Service* s, int descrescator) {
    Repo rezultat;
    init_repo(&rezultat);

    for (int i = 0; i < s->repo->l; i++) {
        adauga_repo(&rezultat, copy_produs(&s->repo->e[i]));
    }

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
*/