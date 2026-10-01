#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {
	Student s{ 1, "Rares", 19, "mate" };
	assert(s.getNrMatricol() == 1);
	assert(s.getNume() == "Rares");
	assert(s.getVarsta() == 19);
	assert(s.getFacultate() == "mate");
}

void testRepo() {
	//fisier test
	std::ofstream out("test_studenti.txt");
	out << "1,Teodor Cotovanu,20,mate\n";
	out << "2,Teodora,21,info\n";
	out.close();

	RepoStudent repo{ "test_studenti.txt" };
	assert(repo.getAll().size() == 2);

	//stergere
	repo.sterge(1);
	assert(repo.getAll().size() == 1);
	try {
		repo.sterge(123);
		assert(false);
	}
	catch(const RepoException&) {}

	repo.imbatranire();
	assert(repo.getAll().at(0).getVarsta() == 22);
	repo.intinerire();
	assert(repo.getAll().at(0).getVarsta() == 21);

	//setall
	std::vector<Student> studentiNoi;
	studentiNoi.push_back(Student{ 1, "Teo", 20, "info" });
	studentiNoi.push_back(Student{ 2, "Bianca", 22, "mate" });
	repo.setAll(studentiNoi);
	assert(repo.getAll().size() == 2);
	assert(repo.getAll().at(0).getNrMatricol() == 1);
	assert(repo.getAll().at(1).getNrMatricol() == 2);
}

void testService() {
	std::ofstream out("test_studenti.txt");
	out << "1,Teodor Cotovanu,19,mate\n";
	out << "2,Teodora,21,info\n";
	out << "4,NumeA,20,ai\n";
	out << "6,NumeC,22,mate\n";
	out << "11,Exemplu,31,mate-info\n";
	out.close();

	RepoStudent repo{ "test_studenti.txt" };
	ServiceStudent srv{ repo };

	assert(srv.getAll().size() == 5);

	//sortare dupa varsta
	auto sortate = srv.getAllSortatiVarsta();
	assert(sortate.at(0).getNrMatricol() == 1);
	assert(sortate.at(1).getNrMatricol() == 4);
	assert(sortate.at(2).getNrMatricol() == 2);
	assert(sortate.at(3).getNrMatricol() == 6);
	assert(sortate.at(4).getNrMatricol() == 11);

	//intinerire
	srv.intinerire();
	assert(srv.getAll().at(0).getVarsta() == 18);
	assert(srv.getAll().at(1).getVarsta() == 20);
	assert(srv.getAll().at(2).getVarsta() == 19);
	assert(srv.getAll().at(3).getVarsta() == 21);
	assert(srv.getAll().at(4).getVarsta() == 30);

	//imbatranire
	srv.imbatranire();
	assert(srv.getAll().at(0).getVarsta() == 19);
	assert(srv.getAll().at(1).getVarsta() == 21);
	assert(srv.getAll().at(2).getVarsta() == 20);
	assert(srv.getAll().at(3).getVarsta() == 22);
	assert(srv.getAll().at(4).getVarsta() == 31);

	//stergere
	srv.stergereStudent(1);
	assert(srv.getAll().size() == 4);

	//undo
	srv.stergereStudent(2);
	assert(srv.getAll().size() == 3);
	srv.undo();
	assert(srv.getAll().size() == 4);

	//redo
	srv.stergereStudent(2);
	srv.undo();
	srv.redo();
	assert(srv.getAll().size() == 3);
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