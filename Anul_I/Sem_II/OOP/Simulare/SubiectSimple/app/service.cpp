#include "service.h"
#include <algorithm>

std::vector<Masina> ServiceMasini::getAll() {
	return repo.getAll();
}

std::vector<Masina> ServiceMasini::sortareAn() {
	std::vector<Masina> copie = repo.getAll();

	std::sort(copie.begin(), copie.end(), [](const Masina& m1, const Masina& m2) {
		return m1.getAn() < m2.getAn();
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