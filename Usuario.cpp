//
// Created by Lázaro Ruiz on 11/12/2025.
//

/**
 * @file Usuario.cpp
 * @brief Implementación de la clase Usuario.
 *
 * Este fichero contiene la implementación de los métodos de la clase Usuario,
 * que representa a un usuario del sistema MediExpress capaz de consultar farmacias,
 * buscar medicamentos por nombre y realizar compras.
 */

#include "Usuario.h"
#include "MediExpress.h"

/**
 * @brief Obtiene el identificador del usuario.
 * @return Identificador numérico del usuario.
 */
int Usuario::getId() const {
    return _id;
}

/**
 * @brief Asigna el identificador del usuario.
 * @param id Nuevo identificador numérico.
 */
void Usuario::setId(int id) {
    _id = id;
}

/**
 * @brief Obtiene la provincia asociada al usuario.
 * @return Referencia constante a la provincia del usuario.
 */
const std::string &Usuario::getProvincia() const {
    return _provincia;
}

/**
 * @brief Asigna la provincia asociada al usuario.
 * @param provincia Nueva provincia del usuario.
 */
void Usuario::setProvincia(const std::string &provincia) {
    _provincia = provincia;
}

/**
 * @brief Destructor de Usuario.
 *
 * @note No libera memoria adicional; la clase no asume propiedad de punteros externos.
 */
Usuario::~Usuario() {
}

/**
 * @brief Constructor parametrizado de Usuario.
 *
 * @param id Identificador del usuario.
 * @param provincia Provincia del usuario.
 * @param coord Coordenadas UTM del usuario.
 * @param linkUser Puntero al objeto MediExpress para acceder a búsquedas de farmacias.
 *
 * @warning El puntero @p linkUser no es propiedad del Usuario; debe mantenerse válido
 * durante la vida del objeto Usuario.
 */
Usuario::Usuario(int id, const std::string &provincia, UTM &coord, MediExpress *linkUser)
    : _id(id),
      _provincia(provincia),
      _coord(coord),
      linkUser(linkUser) {}

/**
 * @brief Solicita a una farmacia la lista de medicamentos que coinciden con un nombre.
 *
 * Llama a la farmacia indicada para buscar medicamentos por nombre (principio activo o nombre comercial,
 * según la implementación de Farmacia).
 *
 * @param nombMedicam Nombre del medicamento a buscar.
 * @param f Puntero a la farmacia donde se realiza la búsqueda.
 * @return Vector de punteros a PA_Medicamento que coinciden con @p nombMedicam.
 *
 * @pre @p f != nullptr
 */
std::vector<PA_Medicamento *> Usuario::quieroMedicam(std::string nombMedicam, Farmacia *f) {
    return f->buscarMedicamNombre(nombMedicam);
}

/**
 * @brief Realiza la compra de un medicamento en una farmacia.
 *
 * Solicita a la farmacia que reduzca su stock del medicamento indicado por el identificador
 * del principio activo y devuelve el número de unidades finalmente compradas/servidas
 * (según la implementación de Farmacia::comprarMedicam).
 *
 * @param n Número de unidades solicitadas.
 * @param PA Puntero al medicamento (principio activo) a comprar.
 * @param f Puntero a la farmacia donde se realiza la compra.
 * @return Unidades compradas (habitualmente 0 si no hay stock suficiente).
 *
 * @pre @p f != nullptr
 * @pre @p PA != nullptr
 */
int Usuario::comprarMedicam(int n, PA_Medicamento *PA, Farmacia *f) {
    return f->comprarMedicam(PA->getIdNum(), n, PA);
}

/**
 * @brief Constructor de copia de Usuario.
 *
 * Copia los atributos básicos del usuario. El puntero a MediExpress se copia tal cual,
 * por lo que ambos objetos apuntarán al mismo enlace.
 *
 * @param orig Usuario original a copiar.
 */
Usuario::Usuario(const Usuario &orig)
    : _id(orig._id),
      _provincia(orig._provincia),
      _coord(orig._coord),
      linkUser(orig.linkUser) {}

/**
 * @brief Obtiene un listado de las @p n farmacias más cercanas al usuario.
 *
 * Utiliza el enlace a MediExpress para buscar farmacias cercanas a las coordenadas
 * actuales del usuario.
 *
 * @param n Número máximo de farmacias a devolver.
 * @return Vector con punteros a Farmacia ordenados por cercanía (según MediExpress).
 *
 * @pre linkUser != nullptr
 */
std::vector<Farmacia *> Usuario::getFarmaciaCercana(int n) {
    std::vector<Farmacia*> toRet = linkUser->buscarFarmacias(_coord, n);
    return toRet;
}

/**
 * @brief Obtiene las coordenadas UTM del usuario.
 * @return Referencia constante a las coordenadas UTM.
 */
const UTM &Usuario::getCoord() const {
    return _coord;
}

/**
 * @brief Asigna nuevas coordenadas UTM al usuario.
 * @param coord Nuevas coordenadas UTM.
 */
void Usuario::setCoord(const UTM &coord) {
    _coord = coord;
}
