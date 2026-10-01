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

void RepoMasini::inchiriaza(int id) {
	bool gasit = false;
	for (auto& m : masini) {
		if (m.getId() == id) {
			if (m.isDisponibila() == false) {
				throw RepoException("Masina este deja inchiriata!");
			}
			m.setDisponibila(false);
			gasit = true;
			break;
		}
	}
	if (!gasit) {
		throw RepoException("Nu exista nicio masina cu acest id!");
	}
	saveToFile();
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
		std::string idStr, marca, model, pretZiStr, dispStr;

		// citim pana la virg
		std::getline(ss, idStr, ',');
		std::getline(ss, marca, ',');
		std::getline(ss, model, ',');
		std::getline(ss, pretZiStr, ',');
		std::getline(ss, dispStr, ',');

		//conversii
		int id = std::stoi(idStr);
		double pretZi = std::stod(pretZiStr);
		bool disp = (dispStr == "True");

		Masina m{ id, marca, model, pretZi, disp };
		masini.push_back(m); // adaugam in vector
	}
	in.close();
}

void RepoMasini::saveToFile() {
	std::ofstream out(numeFisier);
	if (!out.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul pt scriere!");
	}
	for (const auto& m : masini) {
		// bool - text
		std::string dispStr = m.isDisponibila() ? "True" : "False";

		out << m.getId() << ","
			<< m.getMarca() << "," << m.getModel() << "," << m.getPretZi() << "," << dispStr << "\n";
	}
	out.close();
}

void RepoMasini::adauga(const Masina& m) {
	for (const auto& masinaExistenta : masini) {
		if (masinaExistenta.getId() == m.getId()) {
			throw RepoException("Exista deja o masina cu acest Id!");
		}
	}
	masini.push_back(m);
	saveToFile();
}

void RepoMasini::sterge(int id) {
	for (auto it = masini.begin(); it != masini.end(); it++) {
		if (it->getId() == id) {
			masini.erase(it);
			saveToFile();
			return;
		}
	}
	throw RepoException("Nu exista nicio masina cu acest Id!");
}