#pragma once
#include "repo.h"
#include "validator.h"
#include <vector>

class ServiceMelodii {
private:
	RepoMelodii& repo;
public:
	//constructorul primeste direct repo
	ServiceMelodii(RepoMelodii& repo) : repo{ repo } {}

	//toate melodiile
	std::vector<Melodie> getAll();

	//adaugare
	void adaugaMelodie(const std::string& titlu, const std::string& artist, const std::string& gen);

	//stergere
	void stergereMelodie(int id);

	//nr melodii acelasi autor
	int numarMelodiiArtist(const std::string& artist);

	//nr melodii acelasi gen
	int numarMelodiiGen(const std::string& gen);

	//toate melodiile sortate dupa artist
	std::vector<Melodie> getAllSortateArtist();
};