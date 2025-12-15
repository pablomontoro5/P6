//
// Created by pablomontoro5 on 10/12/2025.
//

/**
 * @file Casilla.h
 * @brief Definición de la clase plantilla Casilla.
 *
 * La clase Casilla representa una celda genérica que almacena una colección
 * de elementos de tipo T mediante una lista enlazada (`std::list`).
 * Se utiliza típicamente como estructura auxiliar en mallas o particiones
 * espaciales.
 */

#ifndef P6_CASILLA_H
#define P6_CASILLA_H

#include <list>

/**
 * @class Casilla
 * @brief Casilla genérica que almacena elementos de tipo T.
 *
 * Esta clase encapsula una lista de elementos y proporciona operaciones básicas
 * para insertar, buscar, borrar y recorrer los elementos almacenados.
 *
 * @tparam T Tipo de los elementos almacenados. Debe implementar:
 *         - operador de igualdad (`operator==`)
 *         - constructor por defecto (`T()`)
 */
template <typename T>
class Casilla {

public:
    /**
     * @brief Contenedor interno de elementos.
     *
     * Lista enlazada que almacena los elementos contenidos en la casilla.
     */
    std::list<T> puntos;

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la casilla vacía.
     */
    Casilla() : puntos() {}

    /**
     * @brief Inserta un elemento en la casilla.
     *
     * El elemento se añade al final de la lista interna.
     *
     * @param dato Elemento a insertar.
     */
    void _insertarEnCasilla(const T &dato) {
        puntos.push_back(dato);
    }

    /**
     * @brief Devuelve un iterador al inicio de la casilla.
     *
     * Permite recorrer los elementos almacenados.
     *
     * @return Iterador al primer elemento.
     */
    typename std::list<T>::iterator begin() {
        return puntos.begin();
    }

    /**
     * @brief Devuelve un iterador al final de la casilla.
     *
     * @return Iterador al elemento siguiente al último.
     */
    typename std::list<T>::iterator end() {
        return puntos.end();
    }

    /**
     * @brief Busca un elemento dentro de la casilla.
     *
     * Recorre la lista interna comparando cada elemento con el dato proporcionado
     * mediante el operador `==`.
     *
     * @param dato Elemento a buscar.
     * @return El elemento encontrado si existe; en caso contrario,
     *         devuelve un objeto por defecto de tipo `T`.
     *
     * @note No es posible distinguir entre un elemento no encontrado y un
     *       elemento cuyo valor coincida con `T()`.
     */
    T _buscarEnCasilla(const T &dato) {
        typename std::list<T>::iterator it;
        for (it = puntos.begin(); it != puntos.end(); ++it) {
            if (*it == dato) {
                return *it;
            }
        }
        return T();
    }

    /**
     * @brief Elimina un elemento de la casilla.
     *
     * Busca el elemento indicado y lo elimina de la lista interna si existe.
     *
     * @param dato Elemento a eliminar.
     * @return true si el elemento fue encontrado y eliminado;
     *         false si no existía en la casilla.
     */
    bool _borrarEnCasilla(const T &dato) {
        typename std::list<T>::iterator it;
        for (it = puntos.begin(); it != puntos.end(); ++it) {
            if (*it == dato) {
                puntos.erase(it);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Devuelve el número de elementos almacenados en la casilla.
     *
     * @return Tamaño de la lista interna.
     */
    unsigned _getTamanioCasilla() const {
        return puntos.size();
    }
};

#endif // P6_CASILLA_H
