#include "service.h"
#include <algorithm>

std::vector<Rochie> ServiceRochii::getAll() {
	return repo.getAll();
}

void ServiceRochii::inchiriazaRochie(int cod) {
	repo.inchiriazaRochie(cod);
}

std::vector<Rochie> ServiceRochii::sorteazaDupaMarime() {
	// luam rochiile
	std::vector<Rochie> copie = repo.getAll();

	// atribuim valori pt marimi
	auto getM = [](const std::string& marime) {
		if (marime == "XS") return 1;
		if (marime == "S") return 2;
		if (marime == "M") return 3;
		if (marime == "L") return 4;
		if (marime == "XL") return 5;
		if (marime == "XXL") return 6;
		return 99;
		};
	// sortam
	std::sort(copie.begin(), copie.end(), [getM](const Rochie& r1, const Rochie& r2) {
		return getM(r1.getMarime()) < getM(r2.getMarime());
		});
	return copie;
}

std::vector<Rochie> ServiceRochii::sorteazaDupaPret() {
	std::vector<Rochie> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Rochie& r1, const Rochie& r2) {
		return r1.getPret() < r2.getPret();
		});
	return copie;
}

void ServiceRochii::adaugaRochie(int cod, const std::string& denumire, const std::string& marime, double pret) {
	Rochie r{ cod, denumire, marime, pret, true }; // by defo e disp

	ValidatorRochie val;
	val.valideaza(r);
	repo.adauga(r);
}

void ServiceRochii::stergeRochie(int cod) {
	repo.sterge(cod);
}