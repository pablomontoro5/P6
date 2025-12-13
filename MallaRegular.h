//
// Created by pablomontoro5 on 10/12/2025.
//

#ifndef P6_MALLAREGULAR_H
#define P6_MALLAREGULAR_H

#include "Casilla.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
template <typename T>
class MallaRegular {

private:
    float xMin, yMin, xMax, yMax;
    float tamaCasillaX, tamaCasillaY;
    unsigned taml, ndivi;

    std::vector<std::vector<Casilla<T>>> mr;

    Casilla<T>* obtenerCasilla(float x, float y);

    // Si quieres Haversine, declara aquí:
    // float distancia2(float lat1, float lon1, float lat2, float lon2);

    float distancia(float x, float y, float xcentro, float ycentro);

public:

    MallaRegular(float aXMin=0.0, float aYMin=0.0,
                 float aXMax=0.0, float aYMax=0.0, int nDiv=0);

    MallaRegular(const MallaRegular<T> &malla);

    void insertar(float x, float y, const T &dato);
    T buscar(float x, float y, const T& dato);
    bool borrar(float x, float y, T& dato);

    ~MallaRegular(){}

    std::vector<T> buscarCercana(float x, float y, int n = 1);

    unsigned numElementos();
    unsigned maxElementosPorCelda2();
    float promedioElementosPorCelda2();
};


// ================== IMPLEMENTACIÓN ===================

template <typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int NDiv)
        : xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax), taml(0), ndivi(NDiv)
{
    tamaCasillaX = (xMax - xMin) / NDiv;
    tamaCasillaY = (yMax - yMin) / NDiv;

    mr.insert(mr.begin(), NDiv, std::vector<Casilla<T>>(NDiv));
    // mr.resize(NDiv, std::vector<Casilla<T>>(NDiv));
}

template <typename T>
MallaRegular<T>::MallaRegular(const MallaRegular<T> &malla)
        : xMin(malla.xMin), xMax(malla.xMax), yMin(malla.yMin), yMax(malla.yMax),
          taml(malla.taml), ndivi(malla.ndivi), mr(malla.mr)
{
}

template <typename T>
float MallaRegular<T>::distancia(float lat1, float lon1, float lat2, float lon2){
    return sqrt(pow(lat1-lat2,2) + pow(lon1-lon2,2));
}

template <typename T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y){
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[i][j];
}

template <typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    Casilla<T>* c = obtenerCasilla(x,y);
    c->insertar(dato);
    taml++;
}

template <typename T>
T MallaRegular<T>::buscar(float x, float y, const T &dato) {
    Casilla<T>* c = obtenerCasilla(x, y);
    return c->buscar(dato);
}

template <typename T>
bool MallaRegular<T>::borrar(float x, float y, T& dato){
    Casilla<T>* c = obtenerCasilla(x,y);
    taml--;
    return c->borrar(dato);
}

template <typename T>
unsigned MallaRegular<T>::numElementos(){
    return taml;
}

template <typename T>
unsigned MallaRegular<T>::maxElementosPorCelda2(){
    unsigned maximo=0;

    for (int i=0; i<ndivi; i++){
        for (int j=0; j<ndivi; j++){
            int tam = mr[i][j].get_tam();
            if (tam > maximo)
                maximo = tam;
        }
    }
    return maximo;
}

template <typename T>
float MallaRegular<T>::promedioElementosPorCelda2(){
    return (float)numElementos()/(ndivi*ndivi);
}
template <typename T>
std::vector<T> MallaRegular<T>::buscarCercana(float x, float y, int n) {
    std::vector<T> resultado;
    if (n <= 0 || ndivi == 0) return resultado;

    // 1) localizar celda base (índices)
    int ci = static_cast<int>((x - xMin) / tamaCasillaX);
    int cj = static_cast<int>((y - yMin) / tamaCasillaY);

    if (ci < 0) ci = 0;
    if (ci >= static_cast<int>(ndivi)) ci = static_cast<int>(ndivi) - 1;
    if (cj < 0) cj = 0;
    if (cj >= static_cast<int>(ndivi)) cj = static_cast<int>(ndivi) - 1;

    // 2) expandir por anillos y recoger candidatos
    std::vector<std::pair<float, T> > candidatos;
    candidatos.reserve(n * 8); // reserva aproximada

    int radio = 0;

    while (static_cast<int>(candidatos.size()) < n && radio < static_cast<int>(ndivi)) {

        int iMin = ci - radio;
        int iMax = ci + radio;
        int jMin = cj - radio;
        int jMax = cj + radio;

        if (iMin < 0) iMin = 0;
        if (jMin < 0) jMin = 0;
        if (iMax >= static_cast<int>(ndivi)) iMax = static_cast<int>(ndivi) - 1;
        if (jMax >= static_cast<int>(ndivi)) jMax = static_cast<int>(ndivi) - 1;

        // Recorremos SOLO el borde del anillo:
        // - fila superior (jMin) y fila inferior (jMax)
        // - columna izquierda (iMin) y columna derecha (iMax)
        // evitando duplicar esquinas

        // fila superior
        int i;
        for (i = iMin; i <= iMax; ++i) {
            typename std::list<T>::iterator it;
            for (it = mr[i][jMin].begin(); it != mr[i][jMin].end(); ++it) {
                float d = distancia(x, y, (*it)->getPos().get_latitud(), (*it)->getPos().get_longitud());
                candidatos.push_back(std::make_pair(d, *it));
            }
        }

        // fila inferior (si es distinta)
        if (jMax != jMin) {
            for (i = iMin; i <= iMax; ++i) {
                typename std::list<T>::iterator it;
                for (it = mr[i][jMax].begin(); it != mr[i][jMax].end(); ++it) {
                    float d = distancia(x, y, (*it)->getPos().get_latitud(), (*it)->getPos().get_longitud());
                    candidatos.push_back(std::make_pair(d, *it));
                }
            }
        }

        // columna izquierda (sin esquinas ya contadas)
        int j;
        for (j = jMin + 1; j <= jMax - 1; ++j) {
            typename std::list<T>::iterator it;
            for (it = mr[iMin][j].begin(); it != mr[iMin][j].end(); ++it) {
                float d = distancia(x, y, (*it)->getPos().get_latitud(), (*it)->getPos().get_longitud());
                candidatos.push_back(std::make_pair(d, *it));
            }
        }

        // columna derecha (si es distinta, sin esquinas ya contadas)
        if (iMax != iMin) {
            for (j = jMin + 1; j <= jMax - 1; ++j) {
                typename std::list<T>::iterator it;
                for (it = mr[iMax][j].begin(); it != mr[iMax][j].end(); ++it) {
                    float d = distancia(x, y, (*it)->getPos().get_latitud(), (*it)->getPos().get_longitud());
                    candidatos.push_back(std::make_pair(d, *it));
                }
            }
        }

        ++radio;
    }

    // 3) ordenar por distancia
    std::sort(candidatos.begin(), candidatos.end(),
              [](const std::pair<float, T>& a, const std::pair<float, T>& b) {
                  return a.first < b.first;
              });

    // 4) quedarnos con los n primeros
    int limite = n;
    if (limite > static_cast<int>(candidatos.size()))
        limite = static_cast<int>(candidatos.size());

    int k;
    for (k = 0; k < limite; ++k) {
        resultado.push_back(candidatos[k].second);
    }

    return resultado;
}



#endif // P6_MALLAREGULAR_H
