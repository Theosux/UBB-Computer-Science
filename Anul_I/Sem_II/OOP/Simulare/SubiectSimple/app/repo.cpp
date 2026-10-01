#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>

RepoMasini::RepoMasini(const std::string& numeFisier) : numeFisier{ numeFisier } {
	loadFromFile();
}

std::vector<Masina> RepoMasini::getAll() {
	return masini;
}

void RepoMasini::loadFromFile() {
	std::ifstream in(numeFisier);
	if (!in.is_open()) {
		std::cerr << "eroare: Fisierul " << numeFisier << " nu a fost gasit\n";
		return;
	}
	std::string linie;
	while (std::getline(in, linie)) {
		if (linie.empty()) continue;	// sarim peste liniile goale

		std::stringstream ss(linie);
		std::string idStr, marca, model, anStr;

		// citim pana la virg
		std::getline(ss, idStr, ',');
		std::getline(ss, marca, ',');
		std::getline(ss, model, ',');
		std::getline(ss, anStr, ',');

		//conversii
		int id = std::stoi(idStr);
		int an = std::stoi(anStr);

		Masina m{ id, marca, model, an };
		masini.push_back(m); // adaugam in vector
	}
	in.close();
}