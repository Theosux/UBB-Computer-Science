#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>

RepoRochii::RepoRochii(const std::string& numeFisier) : numeFisier{ numeFisier } {
	loadFromFile();		// citim imediat datele atunci cand pornim
}

std::vector<Rochie> RepoRochii::getAll() {
	return rochii;
}

void RepoRochii::inchiriazaRochie(int cod) {
	bool gasit = false;
	for (auto& r : rochii) {
		if (r.getCod() == cod) {
			if (r.isDisponibila() == false) {
				throw RepoException("Rochia este deja inchiriata!");
			}
			r.setDisponibila(false);
			gasit = true;
			break;
		}
	}
	if (!gasit) {
		throw RepoException("Nu exista nicio rochie cu acest cod!");
	}
	saveToFile();
}

void RepoRochii::loadFromFile() {
	std::ifstream in(numeFisier);
	if (!in.is_open()) {
		std::cerr << "eroare: Fisierul " << numeFisier << " nu a fost gasit\n";
		return;
	}
	std::string linie;
	while (std::getline(in, linie)) {
		if (linie.empty()) continue;	// sarim peste liniile goale

		std::stringstream ss(linie);
		std::string codStr, denumire, marime, pretStr, dispStr;

		// citim pana la virg
		std::getline(ss, codStr, ',');
		std::getline(ss, denumire, ',');
		std::getline(ss, marime, ',');
		std::getline(ss, pretStr, ',');
		std::getline(ss, dispStr, ',');

		//conversii
		int cod = std::stoi(codStr);
		double pret = std::stod(pretStr);
		bool disp = (dispStr == "True");

		Rochie r{ cod, denumire, marime, pret, disp };
		rochii.push_back(r); // adaugam in vector
	}
	in.close();
}

void RepoRochii::saveToFile() {
	std::ofstream out(numeFisier);
	if (!out.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul pt scriere!");
	}
	for (const auto& r : rochii) {
		// bool - text
		std::string dispStr = r.isDisponibila() ? "True" : "False";

		out << r.getCod() << ","
			<< r.getDenumire() << "," << r.getMarime() << "," << r.getPret() << "," << dispStr << "\n";
	}
	out.close();
}

void RepoRochii::adauga(const Rochie& r) {
	// verif unicitatea codului
	for (const auto& rochieExistenta : rochii) {
		if (rochieExistenta.getCod() == r.getCod()) {
			throw RepoException("Exista deja o rochie cu acest cod!\n");
		}
	}

	rochii.push_back(r);
	saveToFile();
}

void RepoRochii::sterge(int cod) {
	// parcurgem vectorul
	for (auto it = rochii.begin(); it != rochii.end(); it++) {
		if (it->getCod() == cod) {
			rochii.erase(it);
			saveToFile();
			return;
		}
	}
	throw RepoException("Nu exista nicio rochie cu acest cod pentru a fi stearsa!");
}

/*
// TEMPLATE: Citire din fisier cand datele sunt separate prin spatii
void RepoRochii::loadFromFileSpatii() {
	std::ifstream in(numeFisier);
	if (!in.is_open()) {
		return;
	}

	int cod;
	std::string denumire, marime, dispStr;
	double pret;

	// in >> variabila citeste automat pana la primul spatiu sau rand nou
	while (in >> cod >> denumire >> marime >> pret >> dispStr) {
		bool disp = (dispStr == "True");
		Rochie r{ cod, denumire, marime, pret, disp };
		rochii.push_back(r);
	}

	in.close();
}
*/