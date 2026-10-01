#pragma once
#include "repo.h"
#include "validator.h"
#include <vector>

class ServiceStudent {
private:
	RepoStudent& repo;
	std::vector<std::vector<Student>> istoric;		//stack
	std::vector<std::vector<Student>> istoricUndo;	//istoric la ce se da undo
public:
	//constructorul primeste direct repo
	ServiceStudent(RepoStudent& repo) : repo{ repo } {}

	//functia de undo care se foloseste de stack
	void undo();


	//functia de redo care se foloseste de undo
	void redo();

	//toti studentii
	std::vector<Student> getAll();

	//stergere
	void stergereStudent(int nrMatricol);

	//toti studentii sortati dupa varsta
	std::vector<Student> getAllSortatiVarsta();

	//intinerire
	void intinerire();

	//imbatranire
	void imbatranire();
};