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
		std::string codStr, denumire, tip, necesarApaStr;

		// citim pana la virg
		std::getline(ss, codStr, ',');
		std::getline(ss, denumire, ',');
		std::getline(ss, tip, ',');
		std::getline(ss, necesarApaStr, ',');

		//conversii
		int cod = std::stoi(codStr);
		int necesarApa = std::stoi(necesarApaStr);

		Masina m{ cod, denumire, tip, necesarApa };
		masini.push_back(m); // adaugam in vector
	}
	in.close();
}