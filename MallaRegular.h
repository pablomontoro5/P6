//
// Created by pablomontoro5 on 10/12/2025.
//

#ifndef P6_MALLAREGULAR_H
#define P6_MALLAREGULAR_H

#include "Casilla.h"
#include <vector>
#include <cmath>

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
    std::vector<std::pair<float, T>> candidatos;

    int ci = (x - xMin) / tamaCasillaX;
    int cj = (y - yMin) / tamaCasillaY;

    if (ci < 0) ci = 0;
    if (ci >= ndivi) ci = ndivi - 1;
    if (cj < 0) cj = 0;
    if (cj >= ndivi) cj = ndivi - 1;

    int radio = 0;

    while ((int)candidatos.size() < n && radio < ndivi) {

        for (int i = ci - radio; i <= ci + radio; i++) {
            for (int j = cj - radio; j <= cj + radio; j++) {

                if (i < 0 || i >= ndivi || j < 0 || j >= ndivi) continue;

                // Iterador explícito (sin auto)
                typename std::list<T>::iterator it;

                for (it = mr[i][j].puntos.begin(); it != mr[i][j].puntos.end(); ++it) {

                    // elem = *it
                    T elem = *it;

                    float d = distancia(x, y,
                                        elem->getPos().GetX(),
                                        elem->getPos().GetY());

                    candidatos.push_back(std::pair<float, T>(d, elem));
                }
            }
        }
        radio++;
    }

    // ordenar por distancia (sin auto)
    sort(candidatos.begin(), candidatos.end(),
         [](const std::pair<float, T> &a, const std::pair<float, T> &b) {
             return a.first < b.first;
         });

    // devolver solo los n más cercanos
    std::vector<T> resultado;
    for (int k = 0; k < n && k < (int)candidatos.size(); k++) {
        resultado.push_back(candidatos[k].second);
    }

    return resultado;
}



#endif // P6_MALLAREGULAR_H
