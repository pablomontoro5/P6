//
// Created by pablomontoro5 on 10/12/2025.
//

/**
 * @file MallaRegular.h
 * @brief Implementación de una malla regular 2D genérica.
 */

#ifndef P6_MALLAREGULAR_H
#define P6_MALLAREGULAR_H

#include "Casilla.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

/**
 * @class MallaRegular
 * @brief Malla regular bidimensional para particionado espacial.
 *
 * Divide un espacio rectangular en una malla de N×N casillas. Cada casilla
 * almacena elementos de tipo T. Permite inserción, borrado, búsqueda directa
 * y búsqueda de vecinos cercanos.
 *
 * @tparam T Tipo de dato almacenado. En buscarCercana se asume que T es un
 *         puntero a un objeto con método getPos() que devuelve un UTM.
 */
template <typename T>
class MallaRegular {

private:
    float _coordenadaXMinima, _coordenadaYMinima;
    float _coordenadaXMaxima, _coordenadaYMaxima;
    float _tamanioCasillaX, _tamanioCasillaY;
    unsigned _tamanioLogico, _numeroDivisiones;

    std::vector<std::vector<Casilla<T>>> _miMallaRegular;

    /**
     * @brief Obtiene la casilla correspondiente a unas coordenadas.
     */
    Casilla<T>* obtenerCasilla(float x, float y);

    /**
     * @brief Calcula distancia euclídea entre dos puntos.
     */
    float distancia(float x, float y, float xcentro, float ycentro);

public:
    /**
     * @brief Constructor parametrizado.
     */
    MallaRegular(float xmin=0.0, float ymin=0.0,
                 float xmax=0.0, float ymax=0.0, int _nD=0);

    /**
     * @brief Constructor de copia.
     */
    MallaRegular(const MallaRegular<T> &_copiaMalla);

    /**
     * @brief Inserta un elemento en la malla.
     */
    void _insertarEnMalla(float x, float y, const T &dato);

    /**
     * @brief Busca un elemento en la malla.
     */
    T _buscarEnMalla(float x, float y, const T& dato);

    /**
     * @brief Borra un elemento de la malla.
     */
    bool _borrarEnMalla(float x, float y, T& dato);

    /**
     * @brief Destructor.
     */
    ~MallaRegular(){}

    /**
     * @brief Busca los n elementos más cercanos a un punto.
     */
    std::vector<T> buscarCercana(float x, float y, int n = 1);

    /**
     * @brief Devuelve el número total de elementos en la malla.
     */
    unsigned _getNumeroElementosMalla();

    /**
     * @brief Devuelve el máximo de elementos por celda.
     */
    unsigned _maximoDeElementosPorCelda();

    /**
     * @brief Devuelve el promedio de elementos por celda.
     */
    float _promedioDeElementosPorCelda();
};

/* ================= IMPLEMENTACIÓN ================= */

/**
 * @brief Constructor parametrizado.
 */
template <typename T>
MallaRegular<T>::MallaRegular(float xmin, float ymin, float xmax, float ymax, int NDiv)
        : _coordenadaXMinima(xmin),
          _coordenadaYMinima(ymin),
          _coordenadaXMaxima(xmax),
          _coordenadaYMaxima(ymax),
          _tamanioLogico(0),
          _numeroDivisiones(NDiv)
{
    _tamanioCasillaX = (_coordenadaXMaxima - _coordenadaXMinima) / NDiv;
    _tamanioCasillaY = (_coordenadaYMaxima - _coordenadaYMinima) / NDiv;

    _miMallaRegular.insert(_miMallaRegular.begin(), NDiv,
                           std::vector<Casilla<T>>(NDiv));
}

/**
 * @brief Constructor de copia.
 */
template <typename T>
MallaRegular<T>::MallaRegular(const MallaRegular<T> &_copiaMalla)
        : _coordenadaXMinima(_copiaMalla._coordenadaXMinima),
          _coordenadaXMaxima(_copiaMalla._coordenadaXMaxima),
          _coordenadaYMinima(_copiaMalla._coordenadaYMinima),
          _coordenadaYMaxima(_copiaMalla._coordenadaYMaxima),
          _tamanioLogico(_copiaMalla._tamanioLogico),
          _numeroDivisiones(_copiaMalla._numeroDivisiones),
          _miMallaRegular(_copiaMalla._miMallaRegular)
{
}

/**
 * @brief Calcula distancia euclídea en 2D.
 */
template <typename T>
float MallaRegular<T>::distancia(float x, float y, float xcentro, float ycentro){
    return std::sqrt(std::pow(x-xcentro,2) + std::pow(y-ycentro,2));
}

/**
 * @brief Obtiene la casilla asociada a unas coordenadas.
 */
template <typename T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y) {

    int i = (int)((x - _coordenadaXMinima) / _tamanioCasillaX);
    int j = (int)((y - _coordenadaYMinima) / _tamanioCasillaY);

    if (i < 0) i = 0;
    if (j < 0) j = 0;
    if (i >= (int)_numeroDivisiones) i = (int)_numeroDivisiones - 1;
    if (j >= (int)_numeroDivisiones) j = (int)_numeroDivisiones - 1;

    return &_miMallaRegular[i][j];
}

/**
 * @brief Inserta un elemento en la malla.
 */
template <typename T>
void MallaRegular<T>::_insertarEnMalla(float x, float y, const T& dato){
    Casilla<T>* c = obtenerCasilla(x,y);
    c->_insertarEnCasilla(dato);
    _tamanioLogico++;
}

/**
 * @brief Busca un elemento en la malla.
 */
template <typename T>
T MallaRegular<T>::_buscarEnMalla(float x, float y, const T &dato) {
    Casilla<T>* c = obtenerCasilla(x, y);
    return c->_buscarEnCasilla(dato);
}

/**
 * @brief Borra un elemento de la malla.
 */
template <typename T>
bool MallaRegular<T>::_borrarEnMalla(float x, float y, T& dato){
    Casilla<T>* c = obtenerCasilla(x,y);
    _tamanioLogico--;
    return c->_borrarEnCasilla(dato);
}

/**
 * @brief Devuelve el número total de elementos.
 */
template <typename T>
unsigned MallaRegular<T>::_getNumeroElementosMalla(){
    return _tamanioLogico;
}

/**
 * @brief Devuelve el máximo número de elementos en una celda.
 */
template <typename T>
unsigned MallaRegular<T>::_maximoDeElementosPorCelda(){
    unsigned maximo=0;

    for (int i=0; i<_numeroDivisiones; i++){
        for (int j=0; j<_numeroDivisiones; j++){
            int tam = _miMallaRegular[i][j]._getTamanioCasilla();
            if (tam > maximo)
                maximo = tam;
        }
    }
    return maximo;
}

/**
 * @brief Calcula el promedio de elementos por celda.
 */
template <typename T>
float MallaRegular<T>::_promedioDeElementosPorCelda(){
    return (float)_getNumeroElementosMalla() /
           (_numeroDivisiones * _numeroDivisiones);
}

/**
 * @brief Busca los n elementos más cercanos a un punto.
 */
template <typename T>
std::vector<T> MallaRegular<T>::buscarCercana(float x, float y, int n) {

    std::vector<T> resultado;
    if (n <= 0 || _numeroDivisiones == 0) return resultado;

    int ci = (int)((x - _coordenadaXMinima) / _tamanioCasillaX);
    int cj = (int)((y - _coordenadaYMinima) / _tamanioCasillaY);

    if (ci < 0) ci = 0;
    if (cj < 0) cj = 0;
    if (ci >= (int)_numeroDivisiones) ci = _numeroDivisiones - 1;
    if (cj >= (int)_numeroDivisiones) cj = _numeroDivisiones - 1;

    std::vector<std::pair<float, T>> candidatos;
    int radio = 0;

    while ((int)candidatos.size() < n && radio < (int)_numeroDivisiones) {

        int iMin = std::max(0, ci-radio);
        int iMax = std::min((int)_numeroDivisiones-1, ci+radio);
        int jMin = std::max(0, cj-radio);
        int jMax = std::min((int)_numeroDivisiones-1, cj+radio);

        for (int i=iMin; i<=iMax; i++) {
            for (auto it=_miMallaRegular[i][jMin].begin();
                 it!=_miMallaRegular[i][jMin].end(); ++it) {
                float d = distancia(x,y,(*it)->getPos().get_latitud(),
                                          (*it)->getPos().get_longitud());
                candidatos.push_back({d,*it});
            }
        }
        radio++;
    }

    std::sort(candidatos.begin(), candidatos.end(),
              [](auto &a, auto &b){ return a.first < b.first; });

    for (int i=0; i<n && i<(int)candidatos.size(); i++)
        resultado.push_back(candidatos[i].second);

    return resultado;
}

#endif // P6_MALLAREGULAR_H
