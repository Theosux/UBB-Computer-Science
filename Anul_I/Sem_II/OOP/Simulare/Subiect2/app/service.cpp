#include "service.h"
#include <algorithm>

std::vector<Masina> ServiceMasini::getAll() {
	return repo.getAll();
}

void ServiceMasini::inchiriazaMasina(int id) {
	repo.inchiriaza(id);
}

void ServiceMasini::stergeMasina(int id) {
	repo.sterge(id);
}

void ServiceMasini::adaugaMasina(int id, const std::string& marca, const std::string& model, double pretZi) {
	Masina m{ id, marca, model, pretZi, true };

	ValidatorMasina val;
	val.valideaza(m);
	repo.adauga(m);
}

std::vector<Masina> ServiceMasini::sortareMarca() {
	std::vector<Masina> copie = repo.getAll();

	std::sort(copie.begin(), copie.end(), [](const Masina& m1, const Masina& m2) {
		return m1.getMarca() < m2.getMarca();
		});
	return copie;
}

std::vector<Masina> ServiceMasini::sortarePret() {
	std::vector<Masina> copie = repo.getAll();

	std::sort(copie.begin(), copie.end(), [](const Masina& m1, const Masina& m2) {
		return m1.getPretZi() < m2.getPretZi();
		});
	return copie;
}

std::vector<Masina> ServiceMasini::filtrareMarca(const std::string& marca) {
	std::vector<Masina> filtrat;
	for (const auto& m : repo.getAll()) {
		if (m.getMarca() == marca) {
			filtrat.push_back(m);
		}
	}
	return filtrat;
}