#include "domain.h"

//constructor
Masina::Masina(int id, const std::string& marca, const std::string& model, double pretZi, bool disponibila)
	: id{ id }, marca{ marca }, model{ model }, pretZi{ pretZi }, disponibila{ disponibila } {}

//gettere
int Masina::getId() const {
	return id;
}

std::string Masina::getMarca() const {
	return marca;
}

std::string Masina::getModel() const {
	return model;
}

double Masina::getPretZi() const {
	return pretZi;
}

bool Masina::isDisponibila() const {
	return disponibila;
}

// settere
void Masina::setDisponibila(bool stare) {
	disponibila = stare;
}