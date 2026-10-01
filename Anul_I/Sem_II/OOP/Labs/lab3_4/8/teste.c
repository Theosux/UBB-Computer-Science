#include "teste.h"
#include "domain.h"
#include "validator.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void test_domain() {
    Produs p = create(1, "Laptop", "Dell", "XPS", 5000, 10);
    assert(p.id == 1);
    assert(strcmp(p.tip, "Laptop") == 0);
    assert(strcmp(p.producator, "Dell") == 0);
    assert(strcmp(p.model, "XPS") == 0);
    assert(p.pret == 5000);
    assert(p.cantitate == 10);
}

void test_validator() {
    Produs p_valid = create(1, "Laptop", "Dell", "XPS", 5000, 10);
    assert(validator(p_valid) == 1);

    Produs p_invalid_id = create(-1, "Laptop", "Dell", "XPS", 5000, 10);
    assert(validator(p_invalid_id) == 0);

    Produs p_invalid_tip = create(1, "", "Dell", "XPS", 5000, 10);
    assert(validator(p_invalid_tip) == 0);

    Produs p_invalid_pret = create(1, "Laptop", "Dell", "XPS", -50, 10);
    assert(validator(p_invalid_pret) == 0);
}

void test_repo() {
    Repo r;
    init_repo(&r);
    assert(r.l == 0);

    Produs p1 = create(1, "Laptop", "Dell", "XPS", 5000, 10);

    // adaugare
    assert(adauga_repo(&r, p1) == 1);
    assert(r.l == 1);

    // actualizare cantitate
    Produs p1_nou = create(1, "Laptop", "Dell", "XPS", 5000, 5);
    assert(adauga_repo(&r, p1_nou) == 2);
    assert(r.e[0].cantitate == 15);

    // cautare
    assert(cauta_repo(&r, 1) == 0);
    assert(cauta_repo(&r, 99) == -1);

    // update
    assert(update(&r, 1, 4500, 20) == 1);
    assert(r.e[0].pret == 4500);
    assert(r.e[0].cantitate == 20);
    assert(update(&r, 99, 100, 100) == 0);

    // stergere
    assert(stergere(&r, 1) == 1);
    assert(r.l == 0);
    assert(stergere(&r, 1) == 0);
}

void test_service() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s, &r);

    // adaugare produs
    assert(adauga_produs(&s, 1, "Telefon", "Samsung", "S23", 4000, 50) == 1);
    assert(adauga_produs(&s, -2, "TV", "LG", "OLED", 5000, 10) == 0);
    assert(s.repo->l == 1);

    // actualizare produs
    assert(actualizeaza_produs(&s, 1, 3500, 40) == 1);
    assert(s.repo->e[0].pret == 3500);

    // Pregatim produse pt filtrare si sortare
    adauga_produs(&s, 2, "Telefon", "Apple", "15", 5000, 10);
    adauga_produs(&s, 3, "Tableta", "Samsung", "TabS9", 3000, 15);

    // filtrare : producator
    Repo rez_filtrare_prod = filtreaza_producator(&s, "Samsung");
    assert(rez_filtrare_prod.l == 2);

    // filtrare : pret
    Repo rez_filtrare_pret = filtreaza_pret(&s, 3500);
    assert(rez_filtrare_pret.l == 2); // produsele de 3000 si 3500

    // filtrare : cantitate
    Repo rez_filtrare_cant = filtreaza_cantitate(&s, 12);
    assert(rez_filtrare_cant.l == 1); // produsul cu 10

    // sortare : cresc
    Repo rez_sortare_cresc = sorteaza_pret(&s, 0);
    assert(rez_sortare_cresc.e[0].pret == 3000);

    // sortare : desc
    Repo rez_sortare_desc = sorteaza_pret(&s, 1);
    assert(rez_sortare_desc.e[0].pret == 5000);

    // stergere
    assert(sterge_produs(&s, 1) == 1);
    assert(s.repo->l == 2);
}

void ruleaza_toate_testele() {
    test_domain();
    test_validator();
    test_repo();
    test_service();
    printf("Teste trecute!\n\n");
}