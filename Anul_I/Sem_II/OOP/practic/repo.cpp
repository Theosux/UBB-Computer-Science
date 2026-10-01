#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>

RepoStudent::RepoStudent(const std::string& numeFisier) : numeFisier{ numeFisier } {
	loadFromFile();		//citim datele la pornire
}
std::vector<Student> RepoStudent::getAll() {
	return studenti;
}

void RepoStudent::loadFromFile() {
	std::ifstream in(numeFisier);
	if (!in.is_open()) {
		std::cerr << "eroare: fisierul " << numeFisier << " nu exista!\n";
		return;
	}
	std::string linie;
	while (std::getline(in, linie)) {
		if (linie.empty()) continue;

		std::stringstream ss(linie);
		std::string nrMatricolStr, nume, varstaStr, facultate;

		//citim pana la virgula
		std::getline(ss, nrMatricolStr, ',');
		std::getline(ss, nume, ',');
		std::getline(ss, varstaStr, ',');
		std::getline(ss, facultate, ',');

		//conversii Str
		int nrMatricol = std::stoi(nrMatricolStr);
		int varsta = std::stoi(varstaStr);

		Student s{ nrMatricol, nume, varsta, facultate };
		studenti.push_back(s);
	}
	in.close();
}

void RepoStudent::saveToFile() {
	std::ofstream out(numeFisier);
	if (!out.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul pt scriere!");
	}
	for (const auto& s : studenti) {
		out << s.getNrMatricol() << "," << s.getNume() << "," << s.getVarsta() << "," << s.getFacultate() << "\n";
	}
	out.close();
}

void RepoStudent::sterge(int nrMatricol) {
	for (auto it = studenti.begin(); it != studenti.end(); it++) {
		if (it->getNrMatricol() == nrMatricol) {
			studenti.erase(it);
			saveToFile();
			return;
		}
	}
	throw RepoException("Nu exista student cu acest Nr Matricol pt stergere!");
}

void RepoStudent::imbatranire() {
	for (auto& s : studenti) {
		s.setVarsta(s.getVarsta() + 1);
	}
	saveToFile();		//update
}

void RepoStudent::intinerire() {
	for (auto& s : studenti) {
		s.setVarsta(s.getVarsta() - 1);
	}
	saveToFile();		//update
}

void RepoStudent::setAll(const std::vector<Student>& studentiNoi) {
	studenti = studentiNoi;
	saveToFile();		//update la starea de undo
}