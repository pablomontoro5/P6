//
// Created by USUARIO on 11/12/2025.
//

#ifndef P6_USUARIO_H
#define P6_USUARIO_H

#include <string>
#include <vector>

#include "UTM.h"
#include "Farmacia.h"

class MediExpress;

class Usuario {
private:
    int _id;
    std::string _provincia;
    UTM _coord;
    MediExpress *linkUser;
public:
    Usuario();
    Usuario(int id, const std::string &provincia, UTM &coord, MediExpress *linkUser);
    Usuario(const Usuario& orig);

    int getId() const;
    void setId(int id);

    const std::string &getProvincia() const;
    void setProvincia(const std::string &provincia);

    const UTM &getCoord() const;
    void setCoord(const UTM &coord);

    virtual ~Usuario();

    std::vector<Farmacia*> getFarmaciaCercana(int n);
    std::vector<PA_Medicamento*> quieroMedicam(std::string nombMedicam, Farmacia *f);
    int comprarMedicam(int n, PA_Medicamento *PA, Farmacia *f);
};


#endif //P6_USUARIO_H
