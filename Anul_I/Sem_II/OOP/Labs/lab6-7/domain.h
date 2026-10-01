#pragma once
#include <string>
#include <iostream>

class Locatar {
private:
	int apartament;
	std::string numeProprietar;
	int suprafata;
	std::string tipApartament;
public:
	Locatar() noexcept;

	Locatar(int apartament, const std::string& nume, int suprafata, const std::string& tip);
	Locatar(const Locatar& ot) = default;

	int getApartament() const noexcept;
	const std::string& getNumeProprietar() const noexcept;
	int getSuprafata() const noexcept;
	const std::string& getTipApartament() const noexcept;

	void setNumeProprietar(const std::string& numeNou);
	void setSuprafata(int suprafataNoua) noexcept;
	void setTipApartament(const std::string& tipNou);
};