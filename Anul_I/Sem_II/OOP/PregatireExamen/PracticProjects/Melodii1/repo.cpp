#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>

RepoMelodii::RepoMelodii(const std::string& numeFisier) : numeFisier{ numeFisier } {
	loadFromFile();			//citim datele la pornire
}

std::vector<Melodie> RepoMelodii::getAll() {
	return melodii;
}

Melodie RepoMelodii::getById(int id) {
	for (const auto& m : melodii) {
		if (m.getId() == id) {
			return m;
		}
	}
	throw RepoException("Nu exista nicio melodie cu acest id!");
}

void RepoMelodii::loadFromFile() {
	std::ifstream in(numeFisier);
	if (!in.is_open()) {
		std::cerr << "eroare: fisierul " << numeFisier << " nu exista!\n";
		return;
	}
	std::string linie;
	while (std::getline(in, linie)) {
		if (linie.empty()) continue;

		std::stringstream ss(linie);
		std::string idStr, titlu, artist, rankStr;

		//citim pana la virgula
		std::getline(ss, idStr, ',');
		std::getline(ss, titlu, ',');
		std::getline(ss, artist, ',');
		std::getline(ss, rankStr, ',');

		//conversii Str
		int id = std::stoi(idStr);
		int rank = std::stoi(rankStr);

		Melodie m{ id, titlu, artist, rank };
		melodii.push_back(m);
	}
	in.close();
}

void RepoMelodii::saveToFile() {
	std::ofstream out(numeFisier);
	if (!out.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul pt scriere!");
	}
	for (const auto& m : melodii) {
		out << m.getId() << "," << m.getTitlu() << "," << m.getArtist() << "," << m.getRank() << "\n";
	}
	out.close();
}

void RepoMelodii::adauga(const Melodie& m) {
	//verificam id unic
	for (const auto& existenta : melodii) {
		if (existenta.getId() == m.getId()) {
			throw RepoException("Exista deja o melodie cu acest id!");
		}
	}
	melodii.push_back(m);
	saveToFile();
}

void RepoMelodii::sterge(int id) {
	for (auto it = melodii.begin(); it != melodii.end(); it++) {
		if (it->getId() == id) {
			melodii.erase(it);
			saveToFile();
			return;
		}
	}
	throw RepoException("Nu exista nicio melodie cu acest id pt stergere!");
}

void RepoMelodii::modifica(const Melodie& melodieNoua) {
	for (auto& m : melodii) {
		if (m.getId() == melodieNoua.getId()) {
			m = melodieNoua;		// inlocuim toata melodia
			saveToFile();
			return;
		}
	}
	throw RepoException("Nu exista nicio melodie cu acest id pentru modificare!");
}