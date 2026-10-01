#include "service.h"
#include <algorithm>

std::vector<Masina> ServiceMasini::getAll() {
	return repo.getAll();
}

std::vector<Masina> ServiceMasini::sortareTip() {
	std::vector<Masina> copie = repo.getAll();	// copiem toate elementele intr-un vector care va fi sortat si returnat

	std::sort(copie.begin(), copie.end(), [](const Masina& m1, const Masina& m2) {
		return m1.getTip() < m2.getTip();
	});
	return copie;
}

std::vector<Masina> ServiceMasini::filtrareApa(int apa) {
	std::vector<Masina> filtrat;
	for (const auto& m : repo.getAll()) {
		if (m.getNecesarApa() == apa) {
			filtrat.push_back(m);
		}
	}
	return filtrat;
}