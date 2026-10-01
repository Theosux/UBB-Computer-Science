#pragma once
#include "repo.h"
#include <vector>

class ServiceMasini {
private:
	RepoMasini& repo;
public:
	// constructor <- repo
	ServiceMasini(RepoMasini& repo) : repo{ repo } {}

	std::vector<Masina> getAll();

	std::vector<Masina> sortareAn();
	std::vector<Masina> filtrareMarca(const std::string& marca);
};