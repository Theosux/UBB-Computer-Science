#include "teste.h"
#include "domain.h"
#include "validator.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <iostream>
#include <fstream>

void testeDomain() {
    // constructor, gettere
    Locatar l{ 12, "Ion Popescu", 55, "Decomandat" };
    assert(l.getApartament() == 12);
    assert(l.getNumeProprietar() == "Ion Popescu");
    assert(l.getSuprafata() == 55);
    assert(l.getTipApartament() == "Decomandat");

    // settere
    l.setNumeProprietar("Maria Popescu");
    l.setSuprafata(60);
    l.setTipApartament("Semidecomandat");

    assert(l.getNumeProprietar() == "Maria Popescu");
    assert(l.getSuprafata() == 60);
    assert(l.getTipApartament() == "Semidecomandat");

    Locatar l_gol;
    assert(l_gol.getApartament() == -1);
    assert(l_gol.getSuprafata() == 0);
    assert(l_gol.getNumeProprietar() == "");
    assert(l_gol.getTipApartament() == "");
}

void testeValidator() {
    ValidatorLocatar valid;
    Locatar l_valid{ 1, "Vasile", 40, "Garsoniera" };

    try {
        valid.valideaza(l_valid);
        assert(true);
    }
    catch (const ValidatorException&) {
        assert(false);
    }

    // locatar invalid
    Locatar l_invalid{ -1, "", -5, "" };
    try {
        valid.valideaza(l_invalid);
        assert(false); // nu se ajunge aici
    }
    catch (const ValidatorException& ex) {
        // s-a aruncat exceptia, mesaje preluate
        std::string mesaje = ex.getErrorMsgs();
        assert(mesaje.find("pozitiv") != std::string::npos);
        assert(mesaje.find("vid") != std::string::npos);
    }
}

void testeRepo() {
    LocatarRepo repo;

    Locatar l1{ 1, "Popescu", 50, "Decomandat" };
    repo.adauga(l1);

    const std::vector<Locatar>& locatari = repo.getAll();
    assert(locatari.size() == 1);
    assert(locatari.at(0).getNumeProprietar() == "Popescu");

    try {
        Locatar l2{ 1, "Ionescu", 60, "Semidecomandat" };
        repo.adauga(l2);
        assert(false);                  // Nu se ajunge pt ca se arunca exceptie
    }
    catch (const RepoException& ex) {
        assert(ex.getMesaj() == "Exista deja un locatar in acest ap");
    }
    // Test stergere
    repo.sterge(1);
    assert(repo.getAll().size() == 0);
    try {
        repo.sterge(99); // Nu exista ap 99
        assert(false);
    }
    catch (const RepoException& ex) {
        assert(ex.getMesaj() == "Nu exista locatar in acest apartament");
    }

    // Test modificare
    Locatar l3{ 2, "Andrei", 70, "Garsoniera" };
    repo.adauga(l3);
    Locatar l3_modificat{ 2, "Andrei_Modificat", 80, "Decomandat" };
    repo.modifica(l3_modificat);
    assert(repo.getAll().at(0).getNumeProprietar() == "Andrei_Modificat");
    assert(repo.getAll().at(0).getSuprafata() == 80);

    try {
        Locatar inexistent{ 99, "Nimeni", 10, "Garsoniera" };
        repo.modifica(inexistent);
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
}

void testeService() {
    LocatarRepo repo;
    ValidatorLocatar val;
    LocatarService srv{ repo, val };

    srv.adaugaLocatar(1, "Ana", 45, "Garsoniera");
    assert(srv.getAllLocatari().size() == 1);

    try {
        srv.adaugaLocatar(-1, "Ana", 45, "Garsoniera");
        assert(false);
    }
    catch (const ValidatorException&) {
        assert(true);
    }

    try {
        srv.adaugaLocatar(1, "Bogdan", 60, "Decomandat");
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    // stergere
    try {
        srv.stergeLocatar(67);
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    srv.stergeLocatar(1);
    assert(srv.getAllLocatari().size() == 0);
    try {
        srv.stergeLocatar(1);
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }

    // modificare
    srv.adaugaLocatar(2, "Mihai", 50, "Garsoniera");
    srv.modificaLocatar(2, "Mihai_Updated", 100, "Decomandat");
    assert(srv.getAllLocatari().at(0).getSuprafata() == 100);

    // modificare invalida
    try {
        srv.modificaLocatar(2, "Mihai", -10, "Decomandat");
        assert(false);
    }
    catch (const ValidatorException&) {
        assert(true);
    }

    LocatarRepo repo2;
    ValidatorLocatar val2;
    LocatarService srv2{ repo2, val2 };

    srv2.adaugaLocatar(1, "Zebra", 60, "Decomandat");
    srv2.adaugaLocatar(2, "Ana", 40, "Garsoniera");
    srv2.adaugaLocatar(3, "Barbu", 40, "Decomandat");

    // cautare
    assert(srv2.cautaApartament(2).getNumeProprietar() == "Ana");
    try {
        srv2.cautaApartament(99);
        assert(false);
    }
    catch (const RepoException& ex) {
        assert(ex.getMesaj() == "Nu exista locatar in acest apartament");
    }

    // filtrare
    assert(srv2.filtreazaDupaTip("Decomandat").size() == 2);
    assert(srv2.filtreazaDupaSuprafata(40).size() == 2);
    assert(srv2.filtreazaDupaSuprafata(100).size() == 0); // Nu gaseste nimic

    /*
    auto sortNume = srv2.sorteazaDupaNume();
    const auto& l1_sort = sortNume.at(0);
    const auto& l2_sort = sortNume.at(2);
    assert(l1_sort.getNumeProprietar() == "Ana");
    assert(l2_sort.getNumeProprietar() == "Zebra");

    // sortare suprafata
    auto sortSuprafata = srv2.sorteazaDupaSuprafata();
    const auto& l1_supr = sortSuprafata.at(0);
    const auto& l2_supr = sortSuprafata.at(2);
    assert(l1_supr.getSuprafata() == 40);
    assert(l2_supr.getSuprafata() == 60);

    // sortare tip suprafata
    auto sortMixt = srv2.sorteazaDupaTipSiSuprafata();
    const auto& l1_mixt = sortMixt.at(0);
    const auto& l2_mixt = sortMixt.at(1);
    const auto& l3_mixt = sortMixt.at(2);
    assert(l1_mixt.getNumeProprietar() == "Barbu");
    assert(l2_mixt.getNumeProprietar() == "Zebra");
    assert(l3_mixt.getNumeProprietar() == "Ana");
    */
    // sortare nume
    auto sortNume = srv2.sorteazaDupaNume();
    Locatar l1_nume = sortNume.at(0); // Facem copie
    Locatar l2_nume = sortNume.at(2);
    assert(l1_nume.getNumeProprietar() == "Ana");
    assert(l2_nume.getNumeProprietar() == "Zebra");

    // sortare suprafata
    auto sortSuprafata = srv2.sorteazaDupaSuprafata();
    Locatar l1_supr = sortSuprafata.at(0);
    Locatar l2_supr = sortSuprafata.at(2);
    assert(l1_supr.getSuprafata() == 40);
    assert(l2_supr.getSuprafata() == 60);

    // sortare tip suprafata
    auto sortMixt = srv2.sorteazaDupaTipSiSuprafata();
    Locatar l1_mixt = sortMixt.at(0);
    Locatar l2_mixt = sortMixt.at(1);
    Locatar l3_mixt = sortMixt.at(2);
    assert(l1_mixt.getNumeProprietar() == "Barbu");
    assert(l2_mixt.getNumeProprietar() == "Zebra");
    assert(l3_mixt.getNumeProprietar() == "Ana");

}
void testeListaNotificare() {
    LocatarRepo repo;
    ValidatorLocatar val;
    LocatarService srv{ repo, val };

    srv.adaugaLocatar(1, "Ana", 40, "Garsoniera");
    srv.adaugaLocatar(2, "Bogdan", 55, "Decomandat");

    // Test Adauga si Goleste
    srv.adaugaInListaNotificare(1);
    assert(srv.getListaNotificare().size() == 1);
    srv.golesteListaNotificare();
    assert(srv.getListaNotificare().size() == 0);

    // Test apartament invalid
    try {
        srv.adaugaInListaNotificare(99);
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }

    // Test Genereaza
    srv.genereazaListaNotificare(5);
    assert(srv.getListaNotificare().size() == 5);

    // Test Export HTML si CSV 
    srv.exportaListaNotificare("test_export.csv");
    srv.exportaListaNotificare("test_export.html");

    try {
        srv.exportaListaNotificare("Q:/folder_inexistent/test.csv");
    }
    catch (const RepoException&) {
        assert(true);
    }
}

void testeRepoFile() {
    // cream un fisier de test (trunc pt golire)
    std::ofstream out("test_repo.txt", std::ios::trunc);
    out.close();

    // adaugare si salvare
    LocatarRepoFile repo{ "test_repo.txt" };
    repo.adauga(Locatar{ 1, "Ion", 50, "Decomandat" });
    repo.adauga(Locatar{ 2, "Vasile", 60, "Garsoniera" });

    // citire(un nou repo care citeste)
    LocatarRepoFile repo2{ "test_repo.txt" };
    auto locatari = repo2.getAll();
    assert(locatari.size() == 2);
    assert(locatari.at(0).getNumeProprietar() == "Ion");

    // stergere
    repo2.sterge(1);
    assert(repo2.getAll().size() == 1);

    // modificare
    repo2.modifica(Locatar{ 2, "Vasile_Modificat", 100, "Semidecomandat" });

    const LocatarRepoFile repo3{ "test_repo.txt" };
    assert(repo3.getAll().size() == 1);
    assert(repo3.getAll().at(0).getSuprafata() == 100);
    assert(repo3.getAll().at(0).getNumeProprietar() == "Vasile_Modificat");

    // fisier invalid
    try {
        LocatarRepoFile repoBad{ "Z:/folder_inexistent_123/test.txt" };
        repoBad.adauga(Locatar{ 1, "Nimeni", 10, "nimic" });
        assert(false); // nu se ajunge
    }
    catch (const RepoException& ex) {
        assert(ex.getMesaj() == "Eroare deschidere fisier!");
    }
}

void testeUndo() {
    LocatarRepo repo;
    ValidatorLocatar val;
    LocatarService srv{ repo, val };

    // nu exista actiuni
    try {
        srv.undo();
        assert(false);
    }
    catch (const RepoException& ex) {
        assert(ex.getMesaj() == "Nu mai exista actiuni pt undo.");
    }

    // undo adaugare
    srv.adaugaLocatar(1, "Teo", 50, "Decomandat");
    assert(srv.getAllLocatari().size() == 1);
    srv.undo();
    assert(srv.getAllLocatari().size() == 0); // S-a sters

    // undo stergere
    srv.adaugaLocatar(1, "Teo", 50, "Decomandat");
    srv.stergeLocatar(1);
    assert(srv.getAllLocatari().size() == 0);
    srv.undo(); // re-adauga
    assert(srv.getAllLocatari().size() == 1);
    assert(srv.getAllLocatari().at(0).getNumeProprietar() == "Teo");

    // undo modificare
    srv.modificaLocatar(1, "Bianca", 100, "Garsoniera");
    assert(srv.getAllLocatari().at(0).getNumeProprietar() == "Bianca");
    srv.undo(); // re-pune "Teo"
    assert(srv.getAllLocatari().at(0).getNumeProprietar() == "Teo");
    assert(srv.getAllLocatari().at(0).getSuprafata() == 50);
}

void testeRaport() {
    LocatarRepo repo;
    ValidatorLocatar val;
    LocatarService srv{ repo, val };

    auto raportGol = srv.getRaportTipuri();
    assert(raportGol.size() == 0);

    srv.adaugaLocatar(1, "A", 50, "Decomandat");
    srv.adaugaLocatar(2, "B", 50, "Decomandat"); // 2 Decomandate
    srv.adaugaLocatar(3, "C", 50, "Garsoniera"); // 1 Garsoniera

    // generam
    auto raport = srv.getRaportTipuri();

    // 2 chei (decomandat si garsoniera)
    assert(raport.size() == 2);

    assert(raport.at("Decomandat").getCount() == 2);
    assert(raport.at("Decomandat").getTip() == "Decomandat");

    assert(raport.at("Garsoniera").getCount() == 1);
    assert(raport.at("Garsoniera").getTip() == "Garsoniera");
}

void ruleazaToateTestele() {
    std::cout << "Teste: \n\n";
    testeDomain();
    std::cout << "Teste domain trecute\n";
    testeValidator();
    std::cout << "Teste validator trecute\n";
    testeRepo();
    std::cout << "Teste repo trecute\n";
    testeService();
    std::cout << "Teste service trecute\n";
    testeListaNotificare();
    std::cout << "Teste notificare trecute\n";
    testeRepoFile();
    std::cout << "Teste repo fila trecute\n";
    testeUndo();
    std::cout << "Teste undo trecute\n";
    testeRaport();
    std::cout << "Teste raport trecute\n";
}