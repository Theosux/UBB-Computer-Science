#pragma once
#include "domain.h"
#include "validator.h"
#include <vector>
#include <string>

class RepoMelodii {
private:
	std::vector<Melodie> melodii;
	std::string numeFisier;

	//fct private pt lucrul cu file
	void loadFromFile();
	void saveToFile();

public:
	RepoMelodii(const std::string& numeFisier);

	//returneaza toate melodiile
	std::vector<Melodie> getAll();

	//cauta melodie dupa id
	Melodie getById(int id);

	//adauga
	void adauga(const Melodie& m);

	//sterge
	void sterge(int id);

	//modifica (inloc melodia cu acelasi id)
	void modifica(const Melodie& m);
};