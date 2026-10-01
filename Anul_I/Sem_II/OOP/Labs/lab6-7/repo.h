#pragma once
#include "domain.h"
#include <vector>
#include <string>
#include <unordered_map>

class RepoException {
private:
	std::string mesaj;
public:
	RepoException(const std::string& msg);
	const std::string& getMesaj() const noexcept;
};

// pur abstract
class RepoAbstract {
public:
	virtual void adauga(const Locatar& l) = 0;
	virtual void sterge(int apartament) = 0;
	virtual void modifica(const Locatar& locatarNou) = 0;
	virtual std::vector<Locatar> getAll() const = 0;
	virtual ~RepoAbstract() = default;
};

// repo-ul vechi
class LocatarRepo : public RepoAbstract {
private:
	std::vector<Locatar> locatari;
public:
	LocatarRepo() = default;
	LocatarRepo(const LocatarRepo& ot) = delete;

	void adauga(const Locatar& l) override;
	void sterge(int apartament) override;
	void modifica(const Locatar& locatarNou) override;
	std::vector<Locatar> getAll() const override;
};

class LocatarRepoFile : public LocatarRepo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	LocatarRepoFile(std::string fName);
	void adauga(const Locatar& l) override;
	void sterge(int apartament) override;
	void modifica(const Locatar& locatarNou) override;
};

class LocatarRepoDict : public RepoAbstract {
private:
	std::unordered_map<int, Locatar> locatari;
	double probabilitate; // 0.0 - 1.0

	void aruncaExceptieAleator() const;

public:
	LocatarRepoDict(double probabilitate);

	void adauga(const Locatar& l) override;
	void sterge(int apartament) override;
	void modifica(const Locatar& locatarNou) override;
	std::vector<Locatar> getAll() const override;
};