#pragma once
#include <string>

class Rochie {
private:
	int cod;
	std::string denumire;
	std::string marime;
	double pret;
	bool disponibila;

public:
	//constructor default(uneori necesar la crearea vectorilor)
	Rochie() = default;
	
	//constructor de initializare
	Rochie(int cod, const std::string& denumire, const std::string& marime, double pret, bool disponibila);

	//gettere pt citire de date
	int getCod() const;
	std::string getDenumire() const;
	std::string getMarime() const;
	double getPret() const;
	bool isDisponibila() const;

	//setter - doar disponibilitatea se schimba
	void setDisponibila(bool stare);

};