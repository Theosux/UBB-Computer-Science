#pragma once
#include "repo.h"
#include "validator.h"
#include <vector>

class ServiceMasini {
private:
	RepoMasini& repo;
public:
	//constructorul primeste direct repoul
	ServiceMasini(RepoMasini& repo) : repo{ repo } {}

	std::vector<Masina> getAll();

	void inchiriazaMasina(int id);
	void adaugaMasina(int id, const std::string& marca, const std::string& model, double pretZi);
	void stergeMasina(int id);

	std::vector<Masina> sortareMarca();
	std::vector<Masina> sortarePret();

	std::vector<Masina> filtrareMarca(const std::string& marca);
};