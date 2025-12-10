//
// Created by pablomontoro5 on 10/12/2025.
//

#ifndef P6_CASILLA_H
#define P6_CASILLA_H

#include <list>

template <typename T>
class Casilla {

public:
    std::list<T> puntos;

    Casilla() : puntos() {}

    void insertar(const T &dato) {
        puntos.push_back(dato);
    }

    typename std::list<T>::iterator begin() {
        return puntos.begin();
    }

    typename std::list<T>::iterator end() {
        return puntos.end();
    }

    // Devuelve el elemento si lo encuentra, sino T() (nullptr si T es puntero)
    T buscar(const T &dato) {
        typename std::list<T>::iterator it;
        for ( it = puntos.begin(); it != puntos.end(); ++it) {
            if (*it == dato) {
                return *it;
            }
        }
        return T(); // CORREGIDO
    }

    bool borrar(const T &dato) {
        typename std::list<T>::iterator it;
        for ( it = puntos.begin(); it != puntos.end(); ++it) {
            if (*it == dato) {
                puntos.erase(it);
                return true;
            }
        }
        return false;
    }

    unsigned get_tam() const {
        return puntos.size();
    }
};

#endif //P6_CASILLA_H

