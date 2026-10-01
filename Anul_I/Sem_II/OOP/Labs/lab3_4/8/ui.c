#include "ui.h"
#include <stdio.h>

void ui_adauga(Service* s) {
    /*
    Cere de la utilizator datele unui produs care va fi adaugat apoi apeleaza functia din service
    param: -
    return: -
    */
    int id, cant;
    int pret;
    char tip[100], prod[100], model[100];

    printf("ID: "); scanf_s("%d", &id);
    printf("Tip: "); scanf_s("%s", tip, 100);
    printf("Producator: "); scanf_s("%s", prod, 100);
    printf("Model: "); scanf_s("%s", model, 100);
    printf("Pret: "); scanf_s("%d", &pret);
    printf("Cantitate: "); scanf_s("%d", &cant);

    int rez = adauga_produs(s, id, tip, prod, model, pret, cant);
    if (rez == 1) printf("Adaugat.\n");
    else if (rez == 2) printf("Cantitate actualizata.\n");
    else printf("Eroare validare.\n");
}

void ui_actualizeaza(Service* s) {
    /*
    Cere de la utilizator datele unui produs care va fi actualizat apoi apeleaza functia din service
    param: -
    return: -
    */
    int id, pret_nou, cant_noua;
    printf("ID produs de actualizat: ");
    scanf_s("%d", &id);
    printf("Pret nou: ");
    scanf_s("%d", &pret_nou);
    printf("Cantitate noua: ");
    scanf_s("%d", &cant_noua);

    int rez = actualizeaza_produs(s, id, pret_nou, cant_noua);
    if (rez == 1) printf("Produs actualizat.\n");
    else printf("Eroare: Produsul negasit /  date invalide.\n");
}

void ui_sterge(Service* s) {
    /*
    Cere id-ul unui produs care va fi sters si apeleaza functia din service, in cazul in care nu exista acel id, utilizatorul este avertizat
    param: -
    return: -
    */
    int id;
    printf("ID produs de sters: ");
    scanf_s("%d", &id);

    int rez = sterge_produs(s, id);
    if (rez == 1) printf("Produs sters.\n");
    else printf("Eroare: Produs inexistent.\n");
}

void ui_afiseaza(Repo r) {
    /*
    Afiseaza toate produsele existente in memorie
    param: -
    return: -
    */
    if (r.l == 0) {
        printf("Nu exista produse.\n");
        return;
    }
    printf("\nLista produse: \n");
    for (int i = 0; i < r.l; i++) {
        printf("ID: %d | Tip: %s | Prod: %s | Model: %s | Pret: %d | Cant: %d\n",
            r.e[i].id, r.e[i].tip, r.e[i].producator,
            r.e[i].model, r.e[i].pret, r.e[i].cantitate);
    }
    printf("\n");
}

void ui_filtreaza(Service* s) {
    /*
    Filtreaza produsele din memorie dupa un criteriu apelat in service
    param: -
    return: -
    */
    int optiune;
    printf("Alege criteriul de filtrare (1 - Producator, 2 - Pret (max), 3 - Cantitate (max)): ");
    scanf_s("%d", &optiune);

    if (optiune == 1) {
        char prod[100];
        printf("Introdu producator: ");
        scanf_s("%s", prod, 100);
        Repo rez = filtreaza_producator(s, prod);
        ui_afiseaza(rez);
    }
    else if (optiune == 2) {
        int pret_max;
        printf("Introdu pretul maxim: ");
        scanf_s("%d", &pret_max);
        Repo rez = filtreaza_pret(s, pret_max);
        ui_afiseaza(rez);
    }
    else if (optiune == 3) {
        int cant_max;
        printf("Introdu cantitatea maxima: ");
        scanf_s("%d", &cant_max);
        Repo rez = filtreaza_cantitate(s, cant_max);
        ui_afiseaza(rez);
    }
    else {
        printf("Optiune invalida!\n");
    }
}

void ui_sorteaza_pret(Service* s) {
    /*
    Sorteaza produsele din memorie dupa pret, crescator sau descrescator
    param: -
    return: -
    */
    int descrescator;
    printf("(0 - Crescator, 1 - Descrescator): ");
    scanf_s("%d", &descrescator);

    Repo rez = sorteaza_pret(s, descrescator);
    ui_afiseaza(rez);
}

void ruleaza_ui(Service* s) {
    int comanda;
    while (1) {
        printf("1. Adauga produs nou / Actualizeaza stoc\n");
        printf("2. Afiseaza toate produsele\n");
        printf("3. Actualizeaza produs existent (pret, cantitate)\n");
        printf("4. Sterge produs\n");
        printf("5. Filtreaza produse (producator, pret, cantitate)\n");
        printf("6. Afiseaza sortat dupa pret\n");
        printf("0. Iesire\n");
        printf("Cmd: ");
        scanf_s("%d", &comanda);

        if (comanda == 0) {
            printf("Iesire din aplicatie...\n");
            break;
        }
        else if (comanda == 1) {
            ui_adauga(s);
        }
        else if (comanda == 2) {
            ui_afiseaza(*(s->repo));
        }
        else if (comanda == 3) {
            ui_actualizeaza(s);
        }
        else if (comanda == 4) {
            ui_sterge(s);
        }
        else if (comanda == 5) {
            ui_filtreaza(s);
        }
        else if (comanda == 6) {
            ui_sorteaza_pret(s);
        }
        else {
            printf("Introdu o comanda valida!\n");
        }
    }
}