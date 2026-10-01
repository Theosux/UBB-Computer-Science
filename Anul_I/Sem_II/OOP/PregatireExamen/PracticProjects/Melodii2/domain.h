#pragma once
#include <string>

class Melodie {
private:
	int id;
	std::string titlu;
	std::string artist;
	std::string gen;
public:
	//constructor default
	Melodie() = default;

	//constructor init
	Melodie(int id, const std::string& titlu, const std::string& artist, const std::string& gen);

	//gettere
	int getId() const;
	std::string getTitlu() const;
	std::string getGen() const;
	std::string getArtist() const;
};