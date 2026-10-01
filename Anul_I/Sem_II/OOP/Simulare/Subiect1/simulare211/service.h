#pragma once
#include "repo.h"
#include "validator.h"
#include <vector>

class ServiceRochii {
private:
	RepoRochii& repo;
public:
	//constructorul primeste direct repo ul
	ServiceRochii(RepoRochii& repo) : repo{ repo } {}

	std::vector<Rochie> getAll();
	
	void inchiriazaRochie(int cod);
	void adaugaRochie(int cod, const std::string& denumire, const std::string& marime, double pret);
	void stergeRochie(int cod);

	// fct de sortare
	std::vector<Rochie> sorteazaDupaMarime();
	std::vector<Rochie> sorteazaDupaPret();
};