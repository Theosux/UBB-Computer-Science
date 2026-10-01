#pragma once
#include "domain.h"
#include "validator.h"
#include <vector>
#include <string>

class RepoStudent {
private:
	std::vector<Student> studenti;
	std::string numeFisier;

	//fct private pt lucrul cu fisiere
	void loadFromFile();
	void saveToFile();
public:
	RepoStudent(const std::string& numeFisier);

	//functie de refresh pt undo
	void setAll(const std::vector<Student>& studentiNoi);

	//returneaza toti studentii
	std::vector<Student> getAll();

	//sterge
	void sterge(int nrMatricol);

	//imbatranire
	void imbatranire();

	//intinerire
	void intinerire();
};