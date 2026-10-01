#pragma once
#include <stdexcept>

template <typename T>
class IteratorVectorTeo;

template <typename T>
class VectorDinamic {
private:
    int capacitate;
    int dimensiune;
    T* elemente;

    void redimensioneaza();

public:
    VectorDinamic() noexcept;

    VectorDinamic(const VectorDinamic& ot);
    VectorDinamic& operator=(const VectorDinamic& ot);
    ~VectorDinamic();

    VectorDinamic(VectorDinamic&& ot) noexcept;
    VectorDinamic& operator=(VectorDinamic&& ot) noexcept;

    void add(const T& element);

    T& get(int index);
    const T& get(int index) const;

    void erase(int index);
    int size() const noexcept;
    bool empty() const noexcept;

    friend class IteratorVectorTeo<T>;
    IteratorVectorTeo<T> begin() const noexcept;
    IteratorVectorTeo<T> end() const noexcept;
};

template <typename T>
VectorDinamic<T>::VectorDinamic() noexcept : capacitate{ 2 }, dimensiune{ 0 }, elemente{ new T[2] } {}

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
void VectorDinamic<T>::add(const T& element) {
    if (dimensiune == capacitate) {
        redimensioneaza();
    }
    elemente[dimensiune] = element;
    dimensiune++;
}

template <typename T>
T& VectorDinamic<T>::get(int index) {
    if (index < 0 || index >= dimensiune) {
        throw std::out_of_range("Index in afara limitelor vectorului!");
    }
    return elemente[index];
}

template <typename T>
const T& VectorDinamic<T>::get(int index) const {
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
IteratorVectorTeo<T> VectorDinamic<T>::begin() const noexcept {
    return IteratorVectorTeo<T>(*this);
}

template <typename T>
IteratorVectorTeo<T> VectorDinamic<T>::end() const noexcept {
    return IteratorVectorTeo<T>(*this, dimensiune);
}

template <typename T>
class IteratorVectorTeo {
private:
    const VectorDinamic<T>& vec;
    int curent;
public:
    IteratorVectorTeo(const VectorDinamic<T>& v) noexcept : vec{ v }, curent{ 0 } {}
    IteratorVectorTeo(const VectorDinamic<T>& v, int pozitie) noexcept : vec{ v }, curent{ pozitie } {}

    bool operator!=(const IteratorVectorTeo& ot) const noexcept { return curent != ot.curent; }

    IteratorVectorTeo& operator++() noexcept { curent++; return *this; }

    const T& operator*() const { return vec.get(curent); }
};