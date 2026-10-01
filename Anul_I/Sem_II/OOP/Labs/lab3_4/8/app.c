#include "repo.h"
#include "service.h"
#include "ui.h"
#include "teste.h" 

void produse_initiale(Service* s) {
    adauga_produs(s, 1, "Laptop", "Asus", "TUF", 4500, 100);
    adauga_produs(s, 2, "Laptop", "Mac", "M1", 6000, 50);
    adauga_produs(s, 3, "Telefon", "Iphone", "15Pro", 4500, 500);
    adauga_produs(s, 4, "Telefon", "Samsung", "A52", 2000, 1000);
    adauga_produs(s, 5, "PC", "PCGarage", "Gaming1", 8000, 100);
    adauga_produs(s, 6, "PC", "PCGarage", "Office", 4500, 50);
}

int main() {
    ruleaza_toate_testele();

    Repo r;
    init_repo(&r);

    Service s;
    init_service(&s, &r);

    produse_initiale(&s);

    ruleaza_ui(&s);

    return 0;
}