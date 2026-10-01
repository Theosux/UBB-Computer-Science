#pragma once
#include <stdexcept>

template <typename T>
class IteratorVector;

template <typename T>
class VectorDinamic {
private:
	int capacitate;
	int dimensiune;
	T* elemente;

	void redimensioneaza();

public:
	VectorDinamic();

	VectorDinamic(const VectorDinamic& ot);
	VectorDinamic& operator=(const VectorDinamic& ot);
	~VectorDinamic();

	VectorDinamic(VectorDinamic&& ot) noexcept;
	VectorDinamic& operator=(VectorDinamic&& ot) noexcept;

	void push_back(const T& element);
	T& at(int index);                   
	const T& at(int index) const;       
	void erase(int index);
	int size() const noexcept;
	bool empty() const noexcept;

	friend class IteratorVector<T>;
	IteratorVector<T> begin() const noexcept;
	IteratorVector<T> end() const noexcept;
};

template <typename T>
VectorDinamic<T>::VectorDinamic() : capacitate{ 2 }, dimensiune{ 0 } {
    elemente = new T[capacitate];
    if (elemente == nullptr) {
        throw std::bad_alloc(); // *
    }
}

/*
VectorDinamic<T>::VectorDinamic() noexcept: capacitate{ 2 }, dimensiune{ 0 }, elemente{ new T[2] }
*/


template <typename T>
VectorDinamic<T>::~VectorDinamic() {
	delete[] elemente;
}

template <typename T>
VectorDinamic<T>::VectorDinamic(const VectorDinamic& ot) : capacitate{ ot.capacitate }, dimensiune{ ot.dimensiune }, elemente{ new T[ot.capacitate] } {
    for (int i = 0; i < ot.dimensiune; ++i) {
        elemente[i] = ot.elemente[i];
    }
}

template <typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(const VectorDinamic& ot) {
    if (this == &ot) {
        return *this;
    }
    delete[] elemente;
    capacitate = ot.capacitate;
    dimensiune = ot.dimensiune;
    elemente = new T[capacitate];
    for (int i = 0; i < dimensiune; ++i) {
        elemente[i] = ot.elemente[i];
    }
    return *this;
}

template <typename T>
VectorDinamic<T>::VectorDinamic(VectorDinamic&& ot) noexcept : capacitate{ ot.capacitate }, dimensiune{ ot.dimensiune }, elemente{ ot.elemente } {
    ot.elemente = nullptr;
    ot.dimensiune = 0;
    ot.capacitate = 0;
}

template <typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(VectorDinamic&& ot) noexcept {
    if (this == &ot) {
        return *this;
    }
    delete[] elemente;
    capacitate = ot.capacitate;
    dimensiune = ot.dimensiune;
    elemente = ot.elemente;
    ot.elemente = nullptr;
    ot.dimensiune = 0;
    ot.capacitate = 0;
    return *this;
}

template <typename T>
void VectorDinamic<T>::redimensioneaza() {
    const int capacitateNoua = (capacitate == 0) ? 2 : capacitate * 2;

    T* elementeNoi = new T[capacitateNoua];
    for (int i = 0; i < dimensiune; ++i) {
        elementeNoi[i] = elemente[i];
    }

    delete[] elemente;
    elemente = elementeNoi;
    capacitate = capacitateNoua;
}

template <typename T>
void VectorDinamic<T>::push_back(const T& element) {
    if (dimensiune == capacitate) {
        redimensioneaza();
    }
    elemente[dimensiune] = element;
    dimensiune++;
}

template <typename T>
T& VectorDinamic<T>::at(int index) {
    if (index < 0 || index >= dimensiune) {
        throw std::out_of_range("Index in afara limitelor vectorului!");
    }
    return elemente[index];
}

template <typename T>
const T& VectorDinamic<T>::at(int index) const {
    if (index < 0 || index >= dimensiune) {
        throw std::out_of_range("Index in afara limitelor vectorului!");
    }
    return elemente[index];
}

template <typename T>
void VectorDinamic<T>::erase(int index) {
    if (index < 0 || index >= dimensiune) {
        throw std::out_of_range("Index in afara limitelor vectorului!");
    }
    for (int i = index; i < dimensiune - 1; ++i) {
        elemente[i] = elemente[i + 1];
    }
    dimensiune--;
}

template <typename T>
int VectorDinamic<T>::size() const noexcept {
    return dimensiune;
}

template <typename T>
bool VectorDinamic<T>::empty() const noexcept {
    return dimensiune == 0;
}

template <typename T>
IteratorVector<T> VectorDinamic<T>::begin() const noexcept {
    return IteratorVector<T>(*this);
}

template <typename T>
IteratorVector<T> VectorDinamic<T>::end() const noexcept {
    return IteratorVector<T>(*this, dimensiune);
}

template <typename T>
class IteratorVector {
private:
    const VectorDinamic<T>& vec;
    int curent;
public:
    IteratorVector(const VectorDinamic<T>& v) noexcept : vec{ v }, curent{ 0 } {}
    IteratorVector(const VectorDinamic<T>& v, int pozitie) noexcept : vec{ v }, curent{ pozitie } {}

    bool operator!=(const IteratorVector& ot) const noexcept { return curent != ot.curent; }
    void operator++() noexcept { curent++; }
    const T& operator*() const { return vec.at(curent); }
};
