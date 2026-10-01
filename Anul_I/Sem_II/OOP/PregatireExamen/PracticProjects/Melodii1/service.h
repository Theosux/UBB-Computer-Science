#pragma once
#include "repo.h"
#include "validator.h"
#include <vector>

class ServiceMelodii {
private:
	RepoMelodii& repo;
public:
	//constructorul primeste direct repo-ul
	ServiceMelodii(RepoMelodii& repo) : repo{ repo } {}

	//toate melodiile
	std::vector<Melodie> getAll();

	//toate melodiile sortate crescator dupa rank (pentru tabel)
	std::vector<Melodie> getAllSortateRank();

	//adaugare
	void adaugaMelodie(int id, const std::string& titlu, const std::string& artist, int rank);

	//modifica titlul si rankul melodiei cu id ul dat
	void modificaMelodie(int id, const std::string& titluNou, int rankNou);

	//stergere; daca e ultima-> exceptie
	void stergeMelodie(int id);

	//cate melodii au un anumit rank
	int numarMelodiiCuRank(int rank);
};