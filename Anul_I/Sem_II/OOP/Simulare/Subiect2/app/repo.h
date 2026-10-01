#pragma once
#include "domain.h"
#include "validator.h"
#include <vector>
#include <string>

class RepoMasini {
private:
	std::vector<Masina> masini;
	std::string numeFisier;

	//fct pt lucru cu fisierul
	void loadFromFile();
	void saveToFile();
public:
	RepoMasini(const std::string& numeFisier);

	std::vector<Masina> getAll();
	void adauga(const Masina& m);
	void sterge(int id);
	void inchiriaza(int id);
};