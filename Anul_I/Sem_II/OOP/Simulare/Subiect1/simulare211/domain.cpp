#include "domain.h"

// implementare constructor
Rochie::Rochie(int cod, const std::string& denumire, const std::string& marime, double pret, bool disponibila)
	: cod{ cod }, denumire{ denumire }, marime{ marime }, pret{ pret }, disponibila{ disponibila } { }

// implementare gettere
int Rochie::getCod() const {
	return cod;
}

std::string Rochie::getDenumire() const {

	return denumire;
}

std::string Rochie::getMarime() const {
	return marime;
}

double Rochie::getPret() const {
	return pret;
}

bool Rochie::isDisponibila() const {
	return disponibila;
}

// implementare setter
void Rochie::setDisponibila(bool stare) {
	disponibila = stare;
}