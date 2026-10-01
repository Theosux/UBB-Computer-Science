#include "domain.h"

//constructor
Masina::Masina(int id, const std::string& marca, const std::string& model, int an) : id{ id }, marca{ marca }, model{ model }, an{ an } {}

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
int Masina::getAn() const {
	return an;
}