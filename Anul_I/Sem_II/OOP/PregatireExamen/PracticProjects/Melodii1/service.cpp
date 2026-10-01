#include "service.h"
#include <algorithm>

std::vector<Melodie> ServiceMelodii::getAll() {
	return repo.getAll();
}

std::vector<Melodie> ServiceMelodii::getAllSortateRank() {
	std::vector<Melodie> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Melodie& a, const Melodie& b) {
		return a.getRank() < b.getRank();
		});
	return copie;
}

void ServiceMelodii::adaugaMelodie(int id, const std::string& titlu, const std::string& artist, int rank) {
	Melodie m{ id, titlu, artist, rank };
	ValidatorMelodie val;
	val.valideaza(m);
	repo.adauga(m);
}

void ServiceMelodii::modificaMelodie(int id, const std::string& titluNou, int rankNou) {
	//luam melodia veche ca sa pastram artistul
	Melodie veche = repo.getById(id);
	Melodie noua{ id, titluNou, veche.getArtist(), rankNou };

	ValidatorMelodie val;
	val.valideaza(noua);
	repo.modifica(noua);
}

void ServiceMelodii::stergeMelodie(int id) {
	//gasim melodia (ca sa i stim artistul)
	Melodie m = repo.getById(id);

	//numaram cate melodii are artistu ei
	int nrArtist = 0;
	for (const auto& alta : repo.getAll()) {
		if (alta.getArtist() == m.getArtist()) {
			nrArtist++;
		}
	}
	if (nrArtist <= 1) {
		throw ValidException("Nu se poate sterge: este ultima melodie a artistului!");
	}
	repo.sterge(id);
}

int ServiceMelodii::numarMelodiiCuRank(int rank) {
	int nr = 0;
	for (const auto& m : repo.getAll()) {
		if (m.getRank() == rank) {
			nr++;
		}
	}
	return nr;
}