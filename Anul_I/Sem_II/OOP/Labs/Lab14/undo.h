#pragma once
#include "domain.h"
#include "repo.h"

// clasa abstracta
class ActiuneUndo {
public:
	// *
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Locatar locatarAdaugat;
	RepoAbstract& repo;
public:
	UndoAdauga(RepoAbstract& repo, const Locatar& l) : repo{ repo }, locatarAdaugat{ l } {}

	// undo adaugare -> stergere
	void doUndo() override {
		repo.sterge(locatarAdaugat.getApartament());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Locatar locatarSters;
	RepoAbstract& repo;
public:
	UndoSterge(RepoAbstract& repo, const Locatar& l) : repo{ repo }, locatarSters{ l } {}

	// undo stergere -> adaugare
	void doUndo() override {
		repo.adauga(locatarSters);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	Locatar locatarVechi;
	RepoAbstract& repo;
public:
	UndoModifica(RepoAbstract& repo, const Locatar& l) : repo{ repo }, locatarVechi{ l } {}

	// undo modificare -> suprascriere cu cel vechi
	void doUndo() override {
		repo.modifica(locatarVechi);
	}
};