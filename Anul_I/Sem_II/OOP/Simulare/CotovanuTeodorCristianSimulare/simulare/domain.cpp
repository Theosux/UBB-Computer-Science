#include "domain.h"

//constructor
Masina::Masina(int cod, const std::string& denumire, const std::string& tip, int necesarApa) : cod{ cod }, denumire{ denumire }, tip{ tip }, necesarApa{ necesarApa } {}

//gettere
int Masina::getCod() const {
	return cod;
}
std::string Masina::getDenumire() const {
	return denumire;
}
std::string Masina::getTip() const {
	return tip;
}
int Masina::getNecesarApa() const {
	return necesarApa;
}