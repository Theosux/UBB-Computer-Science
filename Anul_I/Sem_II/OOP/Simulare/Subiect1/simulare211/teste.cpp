#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {
	// crearea si getterele
	Rochie r{ 1, "Gucci", "M", 1000.0, true };
	assert(r.getCod() == 1);
	assert(r.getDenumire() == "Gucci");
	assert(r.getMarime() == "M");
	assert(r.getPret() == 1000.0);
	assert(r.isDisponibila() == true);

	// setteru
	r.setDisponibila(false);
	assert(r.isDisponibila() == false);
}

void testRepo() {
	// pregatim un fisier
	std::ofstream out("test_rochie.txt");
	out << "1,Rochie Rosie,M,500,True\n";
	out << "2,Rochie Albastra,S,300,False\n";
	out.close();

	// init repo cu fila de test
	RepoRochii repo{ "test_rochie.txt" };
	assert(repo.getAll().size() == 2);

	// test adaugare
	Rochie r1{ 3, "Rochie Neagra", "S", 450, true };
	repo.adauga(r1);
	assert(repo.getAll().size() == 3);

	Rochie r2{ 3, "Rochie x", "M", 550, true };
	try {
		repo.adauga(r2);
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Exista deja o rochie cu acest cod!\n");
	}

	// test inchiriere
	repo.inchiriazaRochie(1);
	assert(repo.getAll().at(0).isDisponibila() == false);
	
	try {
		repo.inchiriazaRochie(2);
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Rochia este deja inchiriata!");
	}

	try {
		repo.inchiriazaRochie(99);
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Nu exista nicio rochie cu acest cod!");
	}

	repo.sterge(1);
	assert(repo.getAll().size() == 2);

	try {
		repo.sterge(999);
		assert(false);
	}
	catch(const RepoException& ex) {
		assert(ex.getMesaj() == "Nu exista nicio rochie cu acest cod pentru a fi stearsa!");
	}

}

void testService() {
	//fisier de test
	std::ofstream out("test_rochie.txt");
	out << "1,R1,L,500,True\n";
	out << "2,R2,S,300,True\n";
	out << "3,R3,M,400,True\n";
	out << "4,R4,XXL,100,True\n";
	out << "5,R5,XL,200,True\n";
	out.close();

	RepoRochii repo{ "test_rochie.txt" };
	ServiceRochii srv{ repo };
	
	//test get all
	assert(srv.getAll().size() == 5);

	//test adaugare
	srv.adaugaRochie(6, "R6", "Z", 800);
	assert(srv.getAll().size() == 6);
	assert(srv.getAll().at(5).getMarime() == "Z");

	try {
		srv.adaugaRochie(10, "Rochie x", "M", -50);
		assert(false);
	}
	catch (const ValidException& ex) {
		assert(ex.getMesaj().find("Pretul nu poate fi negativ!") != std::string::npos);
	}
	try {
		srv.adaugaRochie(10, "", "S", 120);
		assert(false);
	}
	catch (const ValidException& ex) {
		assert(ex.getMesaj().find("Denumirea nu poate fi goala!") != std::string::npos);
	}

	//test sortare pret
	auto sortatePret = srv.sorteazaDupaPret();
	assert(sortatePret.at(0).getPret() == 100); // R4
	assert(sortatePret.at(1).getPret() == 200); // R5
	assert(sortatePret.at(2).getPret() == 300); // R2

	//test sortare dupa marime (S -> M -> L)
	auto sortateMarime = srv.sorteazaDupaMarime();
	assert(sortateMarime.at(0).getMarime() == "S"); // R2
	assert(sortateMarime.at(1).getMarime() == "M"); // R3
	assert(sortateMarime.at(2).getMarime() == "L"); // R1
	assert(sortateMarime.at(3).getMarime() == "XL"); // R5
	assert(sortateMarime.at(4).getMarime() == "XXL"); // R4

	//test inchiriere din service
	srv.inchiriazaRochie(1);
	assert(srv.getAll().at(0).isDisponibila() == false);

	//test stergere
	srv.stergeRochie(3);
	assert(srv.getAll().size() == 5);
}

void testAll() {
	testDomain();
	std::cout << "Teste domain trecute!\n";
	testRepo();
	std::cout << "Teste repo trecute!\n";
	testService();
	std::cout << "Teste service trecute!\n";
	std::cout << "\nToate testele au trecut!\n";
}