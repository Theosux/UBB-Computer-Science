#pragma once
#include "domain.h"
#include <vector>
#include <string>

class RepoMasini {
private:
	std::vector<Masina> masini;
	std::string numeFisier;

	//fct pt lucru cu fila
	void loadFromFile();
public:
	RepoMasini(const std::string& numeFisier);

	std::vector<Masina> getAll();
};