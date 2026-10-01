#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {
	Masina m{ 1, "Toyota", "Suv", 10 };
	assert(m.getId() == 1);
	assert(m.getMarca() == "Toyota");
	assert(m.getModel() == "Suv");
	assert(m.getAn() == 10);
}

void testRepo() {
	// pregatim un fisier
	std::ofstream out("test_masina.txt");
	out << "1,Audi,Sedan,2\n";
	out << "2,Bmw,SUV,3\n";
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

	//test sortare an
	auto sortateAn = srv.sortareAn();
	assert(sortateAn.at(0).getAn() == 1);
	assert(sortateAn.at(1).getAn() == 2);
	assert(sortateAn.at(2).getAn() == 3);
	assert(sortateAn.at(3).getAn() == 4);
	assert(sortateAn.at(4).getAn() == 5);

	//test filtrare marca
	auto filtrateMarca = srv.filtrareMarca("M1");
	assert(filtrateMarca.size() == 1);

}

void testAll() {
	testDomain();
	std::cout << "Teste Domain trecute!\n";
	testRepo();
	std::cout << "Teste Repo trecute!\n";
	testService();
	std::cout << "Teste Service trecute!\n";
	std::cout << "\nToate Testele au trecut!\n";
}