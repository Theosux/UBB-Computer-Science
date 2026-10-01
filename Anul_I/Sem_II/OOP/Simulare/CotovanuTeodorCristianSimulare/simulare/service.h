#pragma once
#include "repo.h"
#include <vector>

class ServiceMasini {
private:
	RepoMasini& repo;
public:
	// constructor <- repo
	ServiceMasini(RepoMasini& repo) : repo{ repo } {}

	//apelul functiei din repo
	std::vector<Masina> getAll();

	//returneaza un vector cu elemente de tip Masina sortat alfabetic dupa campul tip(string)
	std::vector<Masina> sortareTip();

	//returneaza un vector cu elemente de tip Masina filtrat dupa campul necesarApa(int)
	std::vector<Masina> filtrareApa(int apa);
};