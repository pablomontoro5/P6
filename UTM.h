//
// Created by pablomontoro5 on 10/12/2025.
//

/**
 * @file UTM.h
 * @brief Definición de la clase UTM.
 *
 * La clase UTM representa unas coordenadas geográficas simples mediante
 * latitud y longitud expresadas como valores en coma flotante.
 * Proporciona constructores, operadores de comparación y métodos de acceso
 * para su uso en búsquedas espaciales y ordenaciones.
 */

#ifndef P6_UTM_H
#define P6_UTM_H

/**
 * @class UTM
 * @brief Representa unas coordenadas geográficas (latitud y longitud).
 *
 * Esta clase encapsula una posición mediante dos valores:
 * - latitud
 * - longitud
 *
 * Permite copiar, asignar y comparar coordenadas, siendo útil como clave
 * en contenedores ordenados o para cálculos de cercanía.
 */
class UTM {
private:
    /** @brief Latitud de la coordenada */
    float _latitud = 0.0;

    /** @brief Longitud de la coordenada */
    float _longitud = 0.0;

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la latitud y la longitud a 0.0.
     */
    UTM(): _latitud(0.0), _longitud(0.0) {
    }

    /**
     * @brief Constructor parametrizado.
     *
     * @param latitud Valor de la latitud.
     * @param longitud Valor de la longitud.
     */
    UTM(float latitud, float longitud)
        : _latitud(latitud),
          _longitud(longitud) {
    }

    /**
     * @brief Constructor de copia.
     *
     * @param other Objeto UTM a copiar.
     */
    UTM(const UTM &other)
        : _latitud(other._latitud),
          _longitud(other._longitud) {
    }

    /**
     * @brief Operador de asignación.
     *
     * Copia la latitud y la longitud desde otro objeto UTM.
     *
     * @param other Objeto UTM a asignar.
     * @return Referencia al objeto actual.
     */
    UTM & operator=(const UTM &other) {
        if (this == &other)
            return *this;
        _latitud = other._latitud;
        _longitud = other._longitud;
        return *this;
    }

    /**
     * @brief Obtiene la latitud.
     * @return Valor de la latitud.
     */
    float get_latitud() const {
        return _latitud;
    }

    /**
     * @brief Asigna la latitud.
     * @param latitud Nuevo valor de la latitud.
     */
    void set_latitud(const float latitud) {
        _latitud = latitud;
    }

    /**
     * @brief Obtiene la longitud.
     * @return Valor de la longitud.
     */
    float get_longitud() const {
        return _longitud;
    }

    /**
     * @brief Asigna la longitud.
     * @param longitud Nuevo valor de la longitud.
     */
    void set_longitud(const float longitud) {
        _longitud = longitud;
    }

    /**
     * @brief Operador de igualdad.
     *
     * Dos coordenadas son iguales si coinciden tanto la latitud como la longitud.
     *
     * @param lhs Coordenada izquierda.
     * @param rhs Coordenada derecha.
     * @return true si ambas coordenadas son iguales; false en caso contrario.
     */
    friend bool operator==(const UTM &lhs, const UTM &rhs) {
        return lhs._latitud == rhs._latitud
               && lhs._longitud == rhs._longitud;
    }

    /**
     * @brief Operador de desigualdad.
     *
     * @param lhs Coordenada izquierda.
     * @param rhs Coordenada derecha.
     * @return true si las coordenadas son distintas; false en caso contrario.
     */
    friend bool operator!=(const UTM &lhs, const UTM &rhs) {
        return !(lhs == rhs);
    }

    /**
     * @brief Operador menor que.
     *
     * Compara primero por latitud y, en caso de igualdad, por longitud.
     * Permite el uso de UTM en contenedores ordenados.
     *
     * @param lhs Coordenada izquierda.
     * @param rhs Coordenada derecha.
     * @return true si lhs es menor que rhs.
     */
    friend bool operator<(const UTM &lhs, const UTM &rhs) {
        if (lhs._latitud < rhs._latitud)
            return true;
        if (rhs._latitud < lhs._latitud)
            return false;
        return lhs._longitud < rhs._longitud;
    }

    /**
     * @brief Operador menor o igual que.
     * @param lhs Coordenada izquierda.
     * @param rhs Coordenada derecha.
     * @return true si lhs es menor o igual que rhs.
     */
    friend bool operator<=(const UTM &lhs, const UTM &rhs) {
        return !(rhs < lhs);
    }

    /**
     * @brief Operador mayor que.
     * @param lhs Coordenada izquierda.
     * @param rhs Coordenada derecha.
     * @return true si lhs es mayor que rhs.
     */
    friend bool operator>(const UTM &lhs, const UTM &rhs) {
        return rhs < lhs;
    }

    /**
     * @brief Operador mayor o igual que.
     * @param lhs Coordenada izquierda.
     * @param rhs Coordenada derecha.
     * @return true si lhs es mayor o igual que rhs.
     */
    friend bool operator>=(const UTM &lhs, const UTM &rhs) {
        return !(lhs < rhs);
    }
};

#endif // P6_UTM_H
