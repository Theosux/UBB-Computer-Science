#include "service.h"
#include <algorithm>

std::vector<Melodie> ServiceMelodii::getAll() {
	return repo.getAll();
}

void ServiceMelodii::adaugaMelodie(const std::string& titlu, const std::string& artist, const std::string& gen) {
	//testam id uri pornind de la 1
	int id = 1;
	while (true) {
		try {
			repo.getById(id);	//daca gaseste id ul este deja folosit
			id++;
		}
		catch (const RepoException&) {
			break;		//daca nu a gasit dam break si putem continua
		}
	}
	Melodie m{ id, titlu, artist, gen };
	ValidatorMelodie val;
	val.valideaza(m);
	repo.adauga(m);
}

void ServiceMelodii::stergereMelodie(int id) {
	repo.sterge(id);
}

int ServiceMelodii::numarMelodiiArtist(const std::string& artist) {
	int nr = 0;
	for (const auto& m : repo.getAll()) {
		if (m.getArtist() == artist) {
			nr++;
		}
	}
	return nr;
}

int ServiceMelodii::numarMelodiiGen(const std::string& gen) {
	int nr = 0;
	for (const auto& m : repo.getAll()) {
		if (m.getGen() == gen) {
			nr++;
		}
	}
	return nr;
}

std::vector<Melodie> ServiceMelodii::getAllSortateArtist() {
	std::vector<Melodie> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Melodie& a, const Melodie& b) {
		return a.getArtist() < b.getArtist();
		});
	return copie;
}