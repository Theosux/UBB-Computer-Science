#pragma once
#include <string>

class Melodie {
private:
	int id;
	std::string titlu;
	std::string artist;
	int rank;

public:
	//constructor default
	Melodie() = default;

	//constructor init
	Melodie(int id, const std::string& titlu, const std::string& artist, int rank);

	//gettere
	int getId() const;
	std::string getTitlu() const;
	std::string getArtist() const;
	int getRank() const;
};