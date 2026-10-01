#pragma once
#include "domain.h"
#include "validator.h"
#include <vector>
#include <string>

class RepoRochii {
private:
	std::vector<Rochie> rochii;
	std::string numeFisier;

	//fct private folosite pt lucrul cu fisier
	void loadFromFile();
	void saveToFile();
public:
	RepoRochii(const std::string& numeFisier);

	//returneaza toate rochiile
	std::vector<Rochie> getAll();

	//cauta o rochie dupa cod si schimba starea
	void inchiriazaRochie(int cod);
	//adauga
	void adauga(const Rochie& r);
	//sterge
	void sterge(int cod);
};