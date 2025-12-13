//
// Created by USUARIO on 11/12/2025.
//

#include "UTM.h"

UTM::UTM(float latitud, float longitud) : latitud(latitud), longitud(longitud) {}

UTM::UTM(const UTM &orig):latitud(orig.latitud), longitud(orig.longitud) {}

float UTM::getLongitud() const {
    return longitud;
}

void UTM::setLongitud(float longitud) {
    UTM::longitud = longitud;
}

float UTM::getLatitud() const {
    return latitud;
}

void UTM::setLatitud(float latitud) {
    UTM::latitud = latitud;
}

UTM::~UTM() {

}

