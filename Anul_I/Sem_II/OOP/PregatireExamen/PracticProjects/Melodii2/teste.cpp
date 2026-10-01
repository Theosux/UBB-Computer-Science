#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {
	Melodie m{ 1, "Bohemian Rhapsody", "Queen", "rock" };
	assert(m.getId() == 1);
	assert(m.getArtist() == "Queen");
	assert(m.getTitlu() == "Bohemian Rhapsody");
	assert(m.getGen() == "rock");
}

void testRepo() {
	//pregatim fisier test
	std::ofstream out("test_melodii.txt");
	out << "1,Titlu1,Artist1,rock\n";
	out << "2,Titlu2,Artist2,disco\n";
	out.close();

	RepoMelodii repo{ "test_melodii.txt" };
	assert(repo.getAll().size() == 2);

	//adaugare
	Melodie m3{ 3, "Titlu3", "Artist A", "rock"};
	repo.adauga(m3);
	assert(repo.getAll().size() == 3);

	//id duplicat
	try {
		repo.adauga(Melodie{ 3, "X", "Y", "rock"});
		assert(false);
	}
	catch (const RepoException&) {}

	//getById
	assert(repo.getById(2).getArtist() == "Artist2");
	try {
		repo.getById(99);
		assert(false);
	}
	catch (const RepoException&) {}
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
	out << "1,Bohemian Rhapsody,Queen,rock\n";
	out << "3,Hotel California,Eagles,rock\n";
	out << "4,Stayin Alive,Bee Gees,disco\n";
	out << "5,Yesterday,The Beatles,pop\n";
	out << "7,The Sound of Silence,Simon and Garfunkel,folk\n";
	out << "2,Tomorow,The Beatles,pop\n";
	out.close();

	RepoMelodii repo{ "test_melodii.txt" };
	ServiceMelodii srv{ repo };

	assert(srv.getAll().size() == 6);

	//sortare dupa artist
	auto sortate = srv.getAllSortateArtist();
	assert(sortate.at(0).getArtist() == "Bee Gees");
	assert(sortate.at(1).getArtist() == "Eagles");
	assert(sortate.at(2).getArtist() == "Queen");
	assert(sortate.at(3).getArtist() == "Simon and Garfunkel");
	assert(sortate.at(4).getArtist() == "The Beatles");
	assert(sortate.at(5).getArtist() == "The Beatles");

	//nr melodii acelasi artist
	assert(srv.numarMelodiiArtist("Bee Gees") == 1);
	assert(srv.numarMelodiiArtist("The Beatles") == 2);

	//nr melodii acelasi gen
	assert(srv.numarMelodiiGen("rock") == 2);
	assert(srv.numarMelodiiGen("disco") == 1);
	assert(srv.numarMelodiiGen("pop") == 2);
	assert(srv.numarMelodiiGen("folk") == 1);

	//adaugare + validare
	srv.adaugaMelodie("M5", "U2", "rock");
	assert(srv.getAll().size() == 7);
	//assert(repo.getById(6).getTitlu() == "M5");
	try {
		srv.adaugaMelodie("", "X", "rock");	// titlu gol
		assert(false);
	}
	catch (const ValidException&) {}
	try {
		srv.adaugaMelodie("M7", "X", "invalid");	// rank invalid
		assert(false);
	}
	catch (const ValidException&) {}


	//stergere
	srv.stergereMelodie(1);
	assert(srv.getAll().size() == 6);

	//nu gaseste
	try {
		srv.stergereMelodie(99);
		assert(false);
	}
	catch (const RepoException&) {}
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