#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	// Reprezentarea sub forma de perechi
	struct Pereche {
		TElem elem;
		int frecv; // 0 = Liber, -1 = Sters, >0 = Ocupat
	};

	int m; // Capacitatea tabelei de dispersie
	int n; // Numarul total de elemente (suma frecventelor)
	int distincte; // Numarul de locatii efectiv ocupate in tabela
	Pereche* e; // Tabela de dispersie propriu-zisa

	// Functia de dispersie de baza
	int hash(TElem elem) const;
	// Functia de dispersie cu verificare patratica
	int d(TElem elem, int i) const;
	// Redimensionare cand gradul de incarcare depaseste pragul
	void redimensioneaza();
public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};

