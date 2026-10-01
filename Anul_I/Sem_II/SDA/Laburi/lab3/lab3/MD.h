#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

// LDI intern (lista de valori pt o anumita cheie)
struct NodValoare {
	TValoare valoare;
	NodValoare* prec;
	NodValoare* urm;
};

// LDI extern (lista de chei unice)
struct NodCheie { 
	TCheie cheie;
	NodValoare* primval;
	NodValoare* ultimval;
	NodCheie* prec;
	NodCheie* urm;
};

class MD
{
	friend class IteratorMD;

private:
	NodCheie* prim;
	NodCheie* ultim;
	int dimensiune;

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();



};

