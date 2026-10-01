#pragma once
#include <string>

class Masina {
private:
	int id;
	std::string marca;
	std::string model;
	double pretZi;
	bool disponibila;

public:
	Masina() = default;

	Masina(int id, const std::string& marca, const std::string& model, double pretZi, bool disponibila);

	//gettere
	int getId() const;
	std::string getMarca() const;
	std::string getModel() const;
	double getPretZi() const;
	bool isDisponibila() const;

	//settere
	void setDisponibila(bool stare);
};