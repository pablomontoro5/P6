//
// Created by pablomontoro5 on 10/12/2025.
//

#ifndef P6_UTM_H
#define P6_UTM_H


class UTM {
private:
    float _latitud = 0.0;
    float _longitud = 0.0;
public:
    UTM(): _latitud(0.0), _longitud(0.0) {

    };

    UTM(float latitud, float longitud)
        : _latitud(latitud),
          _longitud(longitud) {
    }

    UTM(const UTM &other)
        : _latitud(other._latitud),
          _longitud(other._longitud) {
    }


    UTM & operator=(const UTM &other) {
        if (this == &other)
            return *this;
        _latitud = other._latitud;
        _longitud = other._longitud;
        return *this;
    }

    float get_latitud() const {
        return _latitud;
    }

    void set_latitud(const float latitud) {
        _latitud = latitud;
    }

    float get_longitud() const {
        return _longitud;
    }

    void set_longitud(const float longitud) {
        _longitud = longitud;
    }



    friend bool operator==(const UTM &lhs, const UTM &rhs) {
        return lhs._latitud == rhs._latitud
               && lhs._longitud == rhs._longitud;
    }

    friend bool operator!=(const UTM &lhs, const UTM &rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const UTM &lhs, const UTM &rhs) {
        if (lhs._latitud < rhs._latitud)
            return true;
        if (rhs._latitud < lhs._latitud)
            return false;
        return lhs._longitud < rhs._longitud;
    }

    friend bool operator<=(const UTM &lhs, const UTM &rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const UTM &lhs, const UTM &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const UTM &lhs, const UTM &rhs) {
        return !(lhs < rhs);
    }
};


#endif //P6_UTM_H