//
// Created by USUARIO on 11/12/2025.
//

#include "Usuario.h"
#include "MediExpress.h"

int Usuario::getId() const {
    return _id;
}

void Usuario::setId(int id) {
    _id = id;
}

const std::string &Usuario::getProvincia() const {
    return _provincia;
}

void Usuario::setProvincia(const std::string &provincia) {
    _provincia = provincia;
}

Usuario::~Usuario() {

}

Usuario::Usuario(int id, const std::string &provincia, UTM &coord, MediExpress *linkUser) : _id(id),
                                                                                            _provincia(provincia),
                                                                                            _coord(coord),
                                                                                            linkUser(linkUser) {}

std::vector<PA_Medicamento *> Usuario::quieroMedicam(std::string nombMedicam, Farmacia *f) {
    return f->buscarMedicamNombre(nombMedicam);
}

int Usuario::comprarMedicam(int n, PA_Medicamento *PA, Farmacia *f) {
    return f->comprarMedicam(PA->getIdNum(),n,PA);
}

Usuario::Usuario(const Usuario &orig):_id(orig._id), _provincia(orig._provincia),_coord(orig._coord),linkUser(orig.linkUser) {}

std::vector<Farmacia *> Usuario::getFarmaciaCercana(int n) {
    std::vector<Farmacia*> toRet = linkUser->buscarFarmacias(_coord,n);
    return toRet;
}

const UTM &Usuario::getCoord() const {
    return _coord;
}

void Usuario::setCoord(const UTM &coord) {
    _coord = coord;
}
