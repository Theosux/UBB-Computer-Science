#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {
	Melodie m{ 1, "Bohemian Rhapsody", "Queen", 9 };
	assert(m.getId() == 1);
	assert(m.getTitlu() == "Bohemian Rhapsody");
	assert(m.getArtist() == "Queen");
	assert(m.getRank() == 9);
}

void testRepo() {
	//pregatim un fisier de test
	std::ofstream out("test_melodii.txt");
	out << "1,Titlu1,Artist A,5\n";
	out << "2,Titlu2,Artist B,3\n";
	out.close();

	RepoMelodii repo{ "test_melodii.txt" };
	assert(repo.getAll().size() == 2);

	//adaugare
	Melodie m3{ 3, "Titlu3", "Artist A", 7 };
	repo.adauga(m3);
	assert(repo.getAll().size() == 3);

	//id duplicat
	try {
		repo.adauga(Melodie{ 3, "X", "Y", 1 });
		assert(false);
	}
	catch (const RepoException&) {}

	//getById
	assert(repo.getById(2).getArtist() == "Artist B");
	try {
		repo.getById(99);
		assert(false);
	}
	catch (const RepoException&) {}

	//modificare
	repo.modifica(Melodie{ 2, "Titlu2 nou", "Artist B", 8 });
	assert(repo.getById(2).getTitlu() == "Titlu2 nou");
	assert(repo.getById(2).getRank() == 8);

	//stergere
	repo.sterge(1);
	assert(repo.getAll().size() == 2);
	try {
		repo.sterge(123);
		assert(false);
	}
	catch (const RepoException&) {}
}

void testService() {
	std::ofstream out("test_melodii.txt");
	out << "1,M1,Queen,5\n";
	out << "2,M2,Queen,2\n";
	out << "3,M3,ABBA,8\n";
	out << "4,M4,Beatles,2\n";
	out.close();

	RepoMelodii repo{ "test_melodii.txt" };
	ServiceMelodii srv{ repo };

	assert(srv.getAll().size() == 4);

	//sortare dupa rank
	auto sortate = srv.getAllSortateRank();
	assert(sortate.at(0).getRank() == 2);
	assert(sortate.at(1).getRank() == 2);
	assert(sortate.at(2).getRank() == 5);
	assert(sortate.at(3).getRank() == 8);

	//numar melodii cu un anumit rank
	assert(srv.numarMelodiiCuRank(2) == 2);
	assert(srv.numarMelodiiCuRank(5) == 1);
	assert(srv.numarMelodiiCuRank(0) == 0);

	//adaugare + validare
	srv.adaugaMelodie(5, "M5", "U2", 4);
	assert(srv.getAll().size() == 5);
	try {
		srv.adaugaMelodie(6, "", "X", 3);	// titlu gol
		assert(false);
	}
	catch (const ValidException&) {}
	try {
		srv.adaugaMelodie(7, "M7", "X", 15);	// rank invalid
		assert(false);
	}
	catch (const ValidException&) {}

	//modificare (artistul ramane neschimbat)
	srv.modificaMelodie(3, "M3 nou", 10);
	assert(repo.getById(3).getTitlu() == "M3 nou");
	assert(repo.getById(3).getRank() == 10);
	assert(repo.getById(3).getArtist() == "ABBA");

	//ABBA are o singura melodie -> nu se poate sterge
	try {
		srv.stergeMelodie(3);
		assert(false);
	}
	catch (const ValidException&) {}

	//Queen are 2 melodii -> se poate sterge una
	srv.stergeMelodie(1);
	assert(srv.getAll().size() == 4);
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