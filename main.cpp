#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "PA_Medicamento.h"
#include "Laboratorio.h"
#include "MediExpress.h"
#include "Farmacia.h"
/**  @author Pablo Javier Montoro Bermúdez pjmb0003@red.ujaen.es
      @author Lázaro Ruiz Fernández lrf00011@red.ujaen.es
*/


int main(int argc, const char * argv[]) {
    try {
        std::cout << std::endl << "***Programa de prueba de la Practica 6***" << std::endl;

        std::cout << "*** Apartado 1. Carga de ficheros y parametros de la Tabla Hash ***" << std::endl;

        MediExpress prueba("../pa_medicamentos.csv","../lab2.csv",
                         "../farmacias-coord.csv","../usuarios.csv", 3310,0.65);

        std::cout << std::endl << "*** Apartado 5. Compra de varios medicamentos en Jaen : ***" << std::endl;
        std::string _vNombreMedicamentos[]={"MAGNESIO CLORURO HEXAHIDRATO","LIDOCAINA HIDROCLORURO","MENTA PIPERITA"};
        std::vector<Usuario*> _vectorDeUsuarios= prueba.buscaUsuario("Jaen");
        std::vector<Farmacia*> _vectorDeFarmacias= prueba.buscarFarmacias("JAEN");
        if (_vectorDeFarmacias.size() != 0) {
            int i = 0;
            while (i < (int)_vectorDeUsuarios.size()) {

                std::vector<PA_Medicamento *> _vAux =
                    _vectorDeUsuarios[i]->quieroMedicam(_vNombreMedicamentos[i % 3], _vectorDeFarmacias[0]);

                bool _encontrado = false;
                PA_Medicamento *_pMedAux = nullptr;

                int j = 0;
                while (j < (int)_vAux.size() && !_encontrado) {
                    int _unidades = _vectorDeUsuarios[i]->comprarMedicam(1, _vAux[j], _vectorDeFarmacias[0]);
                    if (_unidades > 0) {
                        _encontrado = true;
                    }
                    _pMedAux = _vAux[j];
                    j++;
                }
                if (_encontrado) {
                    std::cout << "*** El usuario cuyo id es : *** " << _vectorDeUsuarios[i]->getId()
                              << " ***ha comprado el medicamento : ***" << _pMedAux->getNombre()
                              << " ***en la farmacia cuyo nombre es : *** " << _vectorDeFarmacias[0]->getNombre()
                              << " *** y que posee el siguiente numero de unidades : *** "
                              << _vectorDeFarmacias[0]->buscaMedicamID(_pMedAux->getIdNum())
                              << std::endl;
                } else {
                    std::cout << "*** El usuario cuyo id es : *** " << _vectorDeUsuarios[i]->getId()
                              << "  ***no puede adquirir el medicamento : ***" << _vNombreMedicamentos[i % 3]
                              << "*** y, por lo tanto, se piden 10 unidades ***" << std::endl;

                    std::vector<PA_Medicamento*> vpos = prueba.buscarCompuesto(_vNombreMedicamentos[i % 3]);
                    if (vpos.size() != 0) {
                        _vectorDeFarmacias[0]->nuevoStock(vpos[0], 10);
                    }
                }
                std::vector<Farmacia *> _vectorDeFarmaciasCercanas =
                    prueba.buscarFarmacias(_vectorDeUsuarios[i]->getCoord(), 1);
                if (_vectorDeFarmaciasCercanas.size() > 0) {
                    if (_vectorDeFarmaciasCercanas[0] == _vectorDeFarmacias[0]) {
                        std::cout << "*** La farmacia con el nombre : ***" << _vectorDeFarmacias[0]->getNombre()
                                  << " ***situada en: *** " << _vectorDeFarmacias[0]->getLocalidad()
                                  << " ***, Provincia : ***" << _vectorDeFarmacias[0]->getProvincia()
                                  << " *** es la mas cercana al usuario cuyo id es : ***"
                                  << _vectorDeUsuarios[i]->getId() << std::endl;
                    } else {
                        std::cout << "*** La farmacia con el nombre : ***" << _vectorDeFarmacias[0]->getNombre()
                                  << " ***situada en: *** " << _vectorDeFarmacias[0]->getDireccion()
                                  << " *** no es la mas cercana al usuario cuyo id es : *** "
                                  << _vectorDeUsuarios[i]->getId() << std::endl;
                    }
                }
                i++;
            }
        }
        std::cout << std::endl << "*** Apartado 6. Compra por parte de los Sevillanos en la farmacia mas cercana : ***" << std::endl;

        std::vector<Usuario*> _vectorDeSevilla= prueba.buscaUsuario("Sevilla");
        std::string medicina="MAGNESIO";
        int i2 = 0;
        while (i2 < (int)_vectorDeSevilla.size()) {
            std::vector<Farmacia *> _vFarmaciaMasCercanaEnSevilla = _vectorDeSevilla[i2]->getFarmaciaCercana(1);
            std::vector<PA_Medicamento *> _vectorDeMedicamentosDeMagnesio =
                _vectorDeSevilla[i2]->quieroMedicam(medicina, _vFarmaciaMasCercanaEnSevilla[0]);
            bool _encontrado2 = false;
            PA_Medicamento *_pMedAux2 = nullptr;
            int j2 = 0;
            while (j2 < (int)_vectorDeMedicamentosDeMagnesio.size() && !_encontrado2) {
                int _unidades2 = _vectorDeSevilla[i2]->comprarMedicam(
                    1, _vectorDeMedicamentosDeMagnesio[j2], _vFarmaciaMasCercanaEnSevilla[0]
                );
                if (_unidades2 > 0) {
                    _encontrado2 = true;
                }
                _pMedAux2 = _vectorDeMedicamentosDeMagnesio[j2];
                j2++;
            }
            if (_encontrado2) {
                std::cout << "***El usuario cuyo id es : ***" << _vectorDeSevilla[i2]->getId()
                          << "*** compra el medicamento : ***" << _pMedAux2->getNombre()
                          << " ***en la farmacia con nombre : ***" << _vFarmaciaMasCercanaEnSevilla[0]->getNombre()
                          << " ***Dicha farmacia posee el siguiente numero de unidades : ***"
                          << _vFarmaciaMasCercanaEnSevilla[0]->buscaMedicamID(_pMedAux2->getIdNum())
                          << std::endl;
            } else {
                std::cout << "***El usuario cuyo id es : ***" << _vectorDeSevilla[i2]->getId()
                          << " ***no puede comprar el medicamento : ***" << medicina
                          << std::endl;

                std::vector<PA_Medicamento *> _vMagnesioOxido = prueba.buscarCompuesto("MAGNESIO OXIDO");
                if (_vMagnesioOxido.size() != 0) {
                    _vFarmaciaMasCercanaEnSevilla[0]->nuevoStock(_vMagnesioOxido[0], 10);
                    std::cout << "***Se solicita MAGNESIO OXIDO a la siguiente farmacia : ***"
                              << _vFarmaciaMasCercanaEnSevilla[0]->getNombre() << std::endl;
                }
            }
            i2++;
        }

        std::cout << std::endl << "*** Apartado 7. Se vende BISMUTO en Madrid : ***" << std::endl;
        std::vector<Usuario*> _vectorDeMadrid = prueba.buscaUsuario("Madrid");
        std::vector<Farmacia*> _vectorFarmaciasMadrid = prueba.buscarFarmacias("MADRID");
        std::vector<Farmacia*> _vectorFarmaciasMadridConBismuto;

        int i3 = 0;
        while (i3 < (int)_vectorFarmaciasMadrid.size()) {
            std::vector<PA_Medicamento*> _vectorPrincipioActivoMadridConBismuto =
                _vectorFarmaciasMadrid[i3]->buscarMedicamNombre("BISMUTO");
            bool _encontrado3 = false;
            int j3 = 0;
            while (j3 < (int)_vectorPrincipioActivoMadridConBismuto.size() && !_encontrado3) {
                if (_vectorFarmaciasMadrid[i3]->buscaMedicamID(
                        _vectorPrincipioActivoMadridConBismuto[j3]->getIdNum()) > 0) {

                    _vectorFarmaciasMadridConBismuto.push_back(_vectorFarmaciasMadrid[i3]);
                    _encontrado3 = true;
                }
                j3++;
            }
            i3++;
        }
        i3 = 0;
        while (i3 < (int)_vectorDeMadrid.size()) {
            std::vector<Farmacia *> _vectorFarmaciasCercanasEnMadrid =
                _vectorDeMadrid[i3]->getFarmaciaCercana(3);
            bool _encontrado4 = false;
            Farmacia *_pFarmElegida = nullptr;
            int j3 = 0;
            while (j3 < (int)_vectorFarmaciasCercanasEnMadrid.size() && !_encontrado4) {
                int k3 = 0;
                while (k3 < (int)_vectorFarmaciasMadridConBismuto.size()) {
                    if (_vectorFarmaciasCercanasEnMadrid[j3]->getCif() ==
                        _vectorFarmaciasMadridConBismuto[k3]->getCif()) {
                        _encontrado4 = true;
                        _pFarmElegida = _vectorFarmaciasMadridConBismuto[k3];
                    }
                    k3++;
                }
                j3++;
            }
            if (_encontrado4) {
                std::vector<PA_Medicamento*> _vectorPrincipiosActivosMadridConBismuto2 =
                    _pFarmElegida->buscarMedicamNombre("BISMUTO");
                bool _encontrado5 = false;
                j3 = 0;
                while (j3 < (int)_vectorPrincipiosActivosMadridConBismuto2.size() && !_encontrado5) {
                    if (_vectorDeMadrid[i3]->comprarMedicam(
                            1,
                            _vectorPrincipiosActivosMadridConBismuto2[j3],
                            _pFarmElegida) == 1) {
                        std::cout << "***El usuario con id : ***" << _vectorDeMadrid[i3]->getId()
                                  << "*** ha encontrado el BISMUTO en la farmacia cuyo cif es : ***"
                                  << _pFarmElegida->getCif() << std::endl;
                        std::cout << "*** Dicho medicamento tiene como nombre : ***"
                                  << _vectorPrincipiosActivosMadridConBismuto2[j3]->getNombre()
                                  << "*** y sus unidades restantes son : ***"
                                  << _pFarmElegida->buscaMedicamID(
                                         _vectorPrincipiosActivosMadridConBismuto2[j3]->getIdNum())
                                  << std::endl;
                        _encontrado5 = true;
                    }
                    j3++;
                }
            } else {
                std::cout << "***El usuario con id : ***" << _vectorDeMadrid[i3]->getId()
                          << "*** no ha encontrado BISMUTO entre sus 3 farmacias mas cercanas ***"
                          << std::endl;
            }
            i3++;
        }
        std::cout << std::endl;

        std::cout << std::endl << "*** Apartado 8. Se borra el BISMUTO de todas las farmacias y de MediExpress : ***" << std::endl;
        std::vector<PA_Medicamento*> _vectorDeBismuto= prueba.buscarCompuesto("BISMUTO");
        if (_vectorDeBismuto.size()==0) {
            std::cout << "No se encontro Medicamentos con BISMUTO" << std::endl;
        }
        int i5 =0;
        while (i5 < _vectorDeBismuto.size()) {
            if (prueba.eliminarMedicamento(_vectorDeBismuto[i5]->getIdNum())) {
                std::cout << "***Elimnado satisfactoriamente: ***" << _vectorDeBismuto[i5]->getNombre() << std::endl;
            }else {
                std::cout << "***NO se ha hallado: ***" << _vectorDeBismuto[i5]->getNombre() <<  std::endl;
            }
            if (!prueba.buscarCompuesto(_vectorDeBismuto[i5]->getIdNum())) {
                std::cout << "***NO existe: ***" << _vectorDeBismuto[i5]->getNombre() << std::endl;
            }else {
                std::cout << "***Hay constancia de: *** " << _vectorDeBismuto[i5]->getNombre() << std::endl;
            }
            ++i5;
        }

        //PAREJAS
        std::cout << "En NUEVA FARMACIA, el Usuario mas cercano compra MAGNESIO OXIDO" << std::endl;
        std::cout << std::endl << "*** Apartado 9. (Parejas) Se crea un metodo auxiliar para que el usuario mas cercano compre MAGNESIO OXIDO : ***" << std::endl;

        prueba._metodoDeFarmaciaParteParejas();

        //Prueba de imagen
        //medi.PintarImagen("../imagen");

    }catch (std::out_of_range &oor){
        std::cerr << oor.what() << std::endl;
    }catch (std::runtime_error &rte){
        std::cerr << "***Excepcion en fichero: ***" << rte.what() << std::endl;
    }catch (std::bad_alloc &ba){
        std::cerr << "*** Memoria insuficiente ***" << std::endl;
    }

    return 0;
}

