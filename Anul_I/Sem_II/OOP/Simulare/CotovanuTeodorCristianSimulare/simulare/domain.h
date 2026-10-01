#pragma once
#include <string>

class Masina {
private:
	int cod;
	std::string denumire;
	std::string tip;
	int necesarApa;
public:
	Masina() = default;
	Masina(int cod, const std::string& denumire, const std::string& tip, int necesarApa);

	//gettere
	int getCod() const;
	std::string getDenumire() const;
	std::string getTip() const;
	int getNecesarApa() const;
};