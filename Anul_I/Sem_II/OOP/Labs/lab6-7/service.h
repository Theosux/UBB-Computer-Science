#pragma once
#include "repo.h"
#include "validator.h"
#include "raport.h"
#include "undo.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <unordered_map>

class LocatarService : public Observable  { //*
private:
	RepoAbstract& repo;
	ValidatorLocatar& val;

	std::vector<Locatar> listaNotificare;
	std::vector<std::unique_ptr<ActiuneUndo>> undoActions;

public:
	LocatarService(RepoAbstract& repo, ValidatorLocatar& val) noexcept : repo{ repo }, val{ val } {}
	LocatarService(const LocatarService& ot) = delete;

	void adaugaLocatar(int apartament, const std::string& nume, int suprafata, const std::string& tip);
	void stergeLocatar(int apartament);
	void modificaLocatar(int apartament, const std::string& numeNou, int suprafataNoua, const std::string& tipNou);

	const std::vector<Locatar> getAllLocatari() const;
	Locatar cautaApartament(int apartament) const;

	std::vector<Locatar> filtreazaDupaTip(const std::string& tip) const;
	std::vector<Locatar> filtreazaDupaSuprafata(int suprafata) const;

	std::vector<Locatar> sorteazaDupaNume() const;
	std::vector<Locatar> sorteazaDupaSuprafata() const;
	std::vector<Locatar> sorteazaDupaTipSiSuprafata() const;

	void golesteListaNotificare() noexcept;
	void adaugaInListaNotificare(int apartament);
	void genereazaListaNotificare(int numar);
	const std::vector<Locatar>& getListaNotificare() const noexcept;
	void exportaListaNotificare(const std::string& numeFisier) const;
	std::unordered_map<std::string, RaportDTO> getRaportTipuri() const;
	void undo();
};