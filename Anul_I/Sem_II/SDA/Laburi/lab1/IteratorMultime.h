#pragma once

class Multime;
typedef int TElem;

class IteratorMultime
{
	friend class Multime;
private:

	IteratorMultime(const Multime& m);

	const Multime& multime;
	int curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};
