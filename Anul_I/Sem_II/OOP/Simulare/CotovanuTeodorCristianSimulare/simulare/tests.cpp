#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {
	Masina m{ 1, "Toyota", "electrica", 300 };
	assert(m.getCod() == 1);
	assert(m.getDenumire() == "Toyota");
	assert(m.getTip() == "electrica");
	assert(m.getNecesarApa() == 300);
}

void testRepo() {
	// pregatim un fisier
	std::ofstream out("test_masina.txt");
	out << "1,Audi,sport,200\n";
	out << "2,Bmw,SUV,300\n";
	out.close();

	// init repo cu fila de test
	RepoMasini repo{ "test_masina.txt" };
	assert(repo.getAll().size() == 2);
}

void testService() {
	//fisier de test
	std::ofstream out("test_masina.txt");
	out << "1,M1,A,5\n";
	out << "2,M2,B,3\n";
	out << "3,M3,C,4\n";
	out << "4,M4,C,1\n";
	out << "5,M5,D,2\n";
	out.close();

	RepoMasini repo{ "test_masina.txt" };
	ServiceMasini srv{ repo };

	//test get all
	assert(srv.getAll().size() == 5);

	//test sortare tip
	auto sortateTip = srv.sortareTip();
	assert(sortateTip.at(0).getTip() == "A");
	assert(sortateTip.at(1).getTip() == "B");
	assert(sortateTip.at(2).getTip() == "C");
	assert(sortateTip.at(3).getTip() == "C");
	assert(sortateTip.at(4).getTip() == "D");

	//test filtrare apa
	auto filtrateApa = srv.filtrareApa(5);
	assert(filtrateApa.size() == 1);
}

void testAll() {
	testDomain();
	std::cout << "Teste domain trecute\n";
	testRepo();
	std::cout << "Teste repo trecute\n";
	testService();
	std::cout << "Teste service trecute\n";
	std::cout << "\nToate testele trecute\n";
}