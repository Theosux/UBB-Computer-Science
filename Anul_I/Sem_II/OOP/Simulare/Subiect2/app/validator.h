#pragma once
#include <string>
#include "domain.h"

//exceptii fila/repo
class RepoException {
private:
	std::string mesaj;
public:
	RepoException(const std::string& mesaj) : mesaj{ mesaj } {}
	std::string getMesaj() const { return mesaj; }
};

//exceptii validare date
class ValidException {
private:
	std::string mesaj;
public:
	ValidException(const std::string& mesaj) : mesaj{ mesaj } {}
	std::string getMesaj() const { return mesaj; }
};

//validare masina
class ValidatorMasina {
public:
	void valideaza(const Masina& m) const {
		std::string erori = "";
		if (m.getId() <= 0) erori += "Id-ul trb sa fie strict pozitiv!\n";
		if (m.getMarca().empty()) erori += "Marca nu poate fi goala!\n";
		if (m.getModel().empty()) erori += "Modelul nu poate fi gol!\n";
		if (m.getPretZi() <= 0) erori += "Pretul trb sa fie strict pozitiv!\n";
	
		if (!erori.empty()) {
			throw ValidException(erori);
		}
	}
};