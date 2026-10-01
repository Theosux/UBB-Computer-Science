#pragma once
#include "domain.h"
#include <vector>
#include <string>

class RepoMasini {
private:
	std::vector<Masina> masini;
	std::string numeFisier;

	//preia toate elementele din fila
	void loadFromFile();

public:
	RepoMasini(const std::string& numeFisier);
	//returneaza vector cu toate elementele de tip Masina
	std::vector<Masina> getAll();
};