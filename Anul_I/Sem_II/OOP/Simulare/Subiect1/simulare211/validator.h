#pragma once
#include <string>
#include "domain.h"

//exceptii pt lucrul cu file/repo
class RepoException {
private:
	std::string mesaj;
public:
	RepoException(const std::string& mesaj) : mesaj{ mesaj } {}
	std::string getMesaj() const { return mesaj; }
};

//exceptii pt validarea datelor
class ValidException {
private:
	std::string mesaj;
public:
	ValidException(const std::string& mesaj) : mesaj{ mesaj } {}
	std::string getMesaj() const { return mesaj; }
};

//validare rochie
class ValidatorRochie {
public:
	void valideaza(const Rochie& r) const {
		std::string erori = "";
		if (r.getCod() < 0) erori += "Codul nu poate fi negativ!\n";
		if (r.getDenumire().empty()) erori += "Denumirea nu poate fi goala!\n";
		if (r.getMarime().empty()) erori += "Marimea nu poate fi negativa!\n";
		if (r.getPret() <= 0) erori += "Pretul nu poate fi negativ!\n";

		if (!erori.empty()) {
			throw ValidException(erori);
		}
	}
};