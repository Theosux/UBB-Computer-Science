#include "domain.h"

Locatar::Locatar(int apartament, const std::string& nume, int suprafata, const std::string& tip) :
	apartament{ apartament }, numeProprietar{ nume }, suprafata{ suprafata }, tipApartament{ tip } {
	std::cout << "Copie\n";
}

Locatar::Locatar() noexcept : apartament{ -1 }, suprafata{ 0 } {
}

int Locatar::getApartament() const noexcept {
	return apartament;
}

const std::string& Locatar::getNumeProprietar() const noexcept {
	return numeProprietar;
}

int Locatar::getSuprafata() const noexcept {
	return suprafata;
}

const std::string& Locatar::getTipApartament() const noexcept {
	return tipApartament;
}

void Locatar::setNumeProprietar(const std::string& numeNou) {
	numeProprietar = numeNou;
}

void Locatar::setSuprafata(int suprafataNoua) noexcept {
	suprafata = suprafataNoua;
}

void Locatar::setTipApartament(const std::string& tipNou) {
	tipApartament = tipNou;
}