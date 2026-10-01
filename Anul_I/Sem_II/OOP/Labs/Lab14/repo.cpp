#include "repo.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

RepoException::RepoException(const std::string& msg) : mesaj{ msg } {

}

const std::string& RepoException::getMesaj() const noexcept {
	return mesaj;
}

void LocatarRepo::adauga(const Locatar& l) {
	auto it = std::find_if(locatari.begin(), locatari.end(), [&l](const Locatar& loc) noexcept {
		return loc.getApartament() == l.getApartament();
		});
	if (it != locatari.end()) {
		throw RepoException("Exista deja un locatar in acest ap");
	}
	locatari.push_back(l);
}

void LocatarRepo::sterge(int apartament) {
	auto it = std::find_if(locatari.begin(), locatari.end(), [apartament](const Locatar& loc) noexcept {
		return loc.getApartament() == apartament;
		});
	if (it == locatari.end()) {
		throw RepoException("Nu exista locatar in acest apartament");
	}
	locatari.erase(it);
}

void LocatarRepo::modifica(const Locatar& locatarNou) {
	auto it = std::find_if(locatari.begin(), locatari.end(), [&locatarNou](const Locatar& loc) noexcept {
		return loc.getApartament() == locatarNou.getApartament();
		});
	if (it == locatari.end()) {
		throw RepoException("Nu exista locatar in acest apartament!");
	}
	/*
	it->setNumeProprietar(locatarNou.getNumeProprietar());
	it->setSuprafata(locatarNou.getSuprafata());
	it->setTipApartament(locatarNou.getTipApartament());
	*/
	const auto index = std::distance(locatari.begin(), it);
	locatari.at(index).setNumeProprietar(locatarNou.getNumeProprietar());
	locatari.at(index).setSuprafata(locatarNou.getSuprafata());
	locatari.at(index).setTipApartament(locatarNou.getTipApartament());
}

std::vector<Locatar> LocatarRepo::getAll() const {
	return locatari;
}

void LocatarRepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) {
		return;													// daca nu exista, repo e gol
	}

	std::string linie;
	while (std::getline(in, linie)) {
		if (linie.empty()) continue;

		std::stringstream linestream(linie);
		std::string apStr, nume, suprStr, tip;

		std::getline(linestream, apStr, ',');
		std::getline(linestream, nume, ',');
		std::getline(linestream, suprStr, ',');
		std::getline(linestream, tip, ',');

		const int ap = std::stoi(apStr);
		const int supr = std::stoi(suprStr);
		const Locatar l{ ap, nume, supr, tip };

		LocatarRepo::adauga(l);
	}
	in.close();
}

void LocatarRepoFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) {
		throw RepoException("Eroare deschidere fisier!");
	}

	for (const auto& loc : getAll()) {
		out << loc.getApartament() << ","
			<< loc.getNumeProprietar() << ","
			<< loc.getSuprafata() << ","
			<< loc.getTipApartament() << "\n";
	}
	out.close();
}

LocatarRepoFile::LocatarRepoFile(std::string fName) : LocatarRepo(), fName{ fName } {
	loadFromFile();
}

void LocatarRepoFile::adauga(const Locatar& l) {
	LocatarRepo::adauga(l);
	writeToFile();
}

void LocatarRepoFile::sterge(int apartament) {
	LocatarRepo::sterge(apartament);
	writeToFile();
}

void LocatarRepoFile::modifica(const Locatar& locatarNou) {
	LocatarRepo::modifica(locatarNou);
	writeToFile();
}

// Repo-ul cu dict

LocatarRepoDict::LocatarRepoDict(double prob) : probabilitate{ prob } {
}

void LocatarRepoDict::aruncaExceptieAleator() const {
	// random
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> dist(0.0, 1.0);

	const double randomValue = dist(mt);

	if (randomValue < probabilitate) {
		throw RepoException("Exceptie probabilitate");
	}
}

void LocatarRepoDict::adauga(const Locatar& l) {
	aruncaExceptieAleator(); // dam cu zarul inainte de operatie

	if (locatari.find(l.getApartament()) != locatari.end()) {
		throw RepoException("Exista deja un locatar in acest ap");
	}
	locatari.insert({ l.getApartament(), l });
}

void LocatarRepoDict::sterge(int apartament) {
	aruncaExceptieAleator();

	if (locatari.find(apartament) == locatari.end()) {
		throw RepoException("Nu exista locatar in acest apartament");
	}
	locatari.erase(apartament);
}

void LocatarRepoDict::modifica(const Locatar& locatarNou) {
	aruncaExceptieAleator();

	if (locatari.find(locatarNou.getApartament()) == locatari.end()) {
		throw RepoException("Nu exista locatar in acest apartament!");
	}
	locatari.at(locatarNou.getApartament()) = locatarNou;
}

std::vector<Locatar> LocatarRepoDict::getAll() const {
	aruncaExceptieAleator();

	std::vector<Locatar> rez;
	for (const auto& pereche : locatari) {
		rez.push_back(pereche.second);
	}
	return rez;
}