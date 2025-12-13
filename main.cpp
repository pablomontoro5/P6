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
    try{
        //PRUEBA: Mediexpress
        std::cout << std::endl << "PRUEBA.- MediExpress:" << std::endl;

        std::cout << "Comienzo de lectura de ficheros y carga de DATOS " << std::endl;

        MediExpress medi("../pa_medicamentos.csv","../lab2.csv",
                         "../farmacias-coord.csv","../usuarios.csv", 3310,0.65);

        //PUNTO 5
        //Compras de medicamentos varios en Jaen
        std::cout << std::endl << "Compran los Giennenses varios medicamentos:" << std::endl;
        std::string medicam[]={"MAGNESIO CLORURO HEXAHIDRATO","LIDOCAINA HIDROCLORURO","MENTA PIPERITA"};
        std::vector<Usuario*> vu= medi.buscaUsuario("Jaen");
        std::vector<Farmacia*> vf= medi.buscarFarmacias("JAEN");
        if (vf.size()!=0) {
            for (int i = 0; i < vu.size(); i++) {
                //compra
                std::vector<PA_Medicamento *> vp = vu[i]->quieroMedicam(medicam[i % 3], vf[0]);
                bool enc = false;
                PA_Medicamento *med;
                for (int j = 0; j < vp.size() && !enc; j++) {
                    int uni = vu[i]->comprarMedicam(1, vp[j], vf[0]);
                    if (uni > 0) {
                        enc = true;
                    }
                    med = vp[j];
                }
                if (enc) {
                    std::cout << "==>Usuario " << vu[i]->getId() << " compra " <<
                         med->getNombre() << " en farmacia " << vf[0]->getNombre() <<
                         " Stock: " << vf[0]->buscaMedicamID(med->getIdNum()) << std::endl;
                }else{
                    std::cout << "==>Usuario " << vu[i]->getId() << " **NO puede comprar " << medicam[i % 3]
                         << " y pide 10 unidades" << std::endl;
                    std::vector<PA_Medicamento*> vpos=medi.buscarCompuesto(medicam[i % 3]);
                    if (vpos.size()!=0)
                        vf[0]->nuevoStock(vpos[0],10);
                }
                //comprueba cercana
                std::vector<Farmacia *> cercana = vu[i]->getFarmaciaCercana(1);   //medi.buscarFarmacias(vu[i]->getCoord(), 1);
                if (cercana.size() > 0) {
                    if (cercana[0] == vf[0]) {
                        std::cout << "La farmacia " << vf[0]->getNombre() << " en " <<
                             vf[0]->getLocalidad() << ", " << vf[0]->getProvincia() << " es la mas cercana a usuario " <<
                             vu[i]->getId() << std::endl;
                    } else {
                        std::cout << "La farmacia " << vf[0]->getNombre() << " en " <<
                             vf[0]->getDireccion() << " **NO es la mas cercana a " <<
                             vu[i]->getId() << std::endl;
                    }
                }
            }
        }


        //Compras sevillanos en farmacia mas cercana
        std::vector<Usuario*> vS= medi.buscaUsuario("Sevilla");
        std::string medicina="MAGNESIO";

        std::cout << std::endl << "Compran los Sevillanos MAGNESIO:" << std::endl;
        for (int i=0; i<vS.size(); i++) {
            std::cout << " * Usuario " << i << ": " << std::endl;
            //farmacia mas cercana al usuario
            std::vector<Farmacia *> cercanaS = vS[i]->getFarmaciaCercana(1);
            //medicamentos de magnesio de esa farmacia
            std::vector<PA_Medicamento *> vp = vS[i]->quieroMedicam(medicina, cercanaS[0]);
            bool enc = false;
            PA_Medicamento *med;
            for (int j = 0; j < vp.size() && !enc; j++) {
                int uni = vS[i]->comprarMedicam(1, vp[j], cercanaS[0]);
                if (uni > 0) {
                    enc = true;
                }
                med = vp[j];
            }
            if (enc) {
                std::cout << "==>Usuario " << vS[i]->getId() << " compra " <<
                     med->getNombre() << " en farmacia " << cercanaS[0]->getNombre() <<
                     " Stock: " << cercanaS[0]->buscaMedicamID(med->getIdNum()) << std::endl;
            } else {
                std::cout << "==>Usuario " << vS[i]->getId() << " **NO puede comprar " << medicina
                     << " y pide 10 unidades" << std::endl;
                //medi.suministrarFarmacia(cercanaS[0],3640,10);
                std::vector<PA_Medicamento *> vpos = medi.buscarCompuesto("MAGNESIO OXIDO");
                if (vpos.size() != 0) {
                    cercanaS[0]->nuevoStock(vpos[0], 10);
                    std::cout << "Se solicita MAGNESIO OXIDO a la farmacia " << cercanaS[0]->getNombre() << std::endl;
                }
            }

        }

        //Buscar farmacias Madrid con BISMUTO y Usuarios Madrileños
        std::cout << std::endl << "Vendemos BISMUTO en Madrid a los madrileeños." << std::endl;
        std:: vector<Usuario*> vM= medi.buscaUsuario("Madrid");  //usuarios de Madrid
        std::vector<Farmacia*> vFM= medi.buscarFarmacias("MADRID");  //farmacias de Madrid
        std::vector<Farmacia*> vFMBismuto;
        //de las de madrid me quedo con las q venden BISMUTO y tienen unidades
        for (int i=0; i<vFM.size(); i++){
            std::vector<PA_Medicamento*> vPAM= vFM[i]->buscarMedicamNombre("BISMUTO");
            bool enc=false;
            for (int j=0; j<vPAM.size() && !enc; j++) {
                if (vFM[i]->buscaMedicamID(vPAM[j]->getIdNum()) > 0) {
                    vFMBismuto.push_back(vFM[i]);
                    enc = true;
                }
            }
        }

        for (int i=0; i<vM.size(); i++){   //por cada Usuario
            std::vector<Farmacia *> cercanasM = vM[i]->getFarmaciaCercana(3); //busco 3 mas cercanas
            bool enc=false;
            Farmacia *elegida;
            //PaMedicamento *elegido;
            for (int j=0; j<cercanasM.size() && !enc; j++){  //busco cada una
                for (int k=0; k<vFMBismuto.size() ; k++){   //entre las de madrid con Bismuto
                    if (cercanasM[j]->getCif()==vFMBismuto[k]->getCif()){
                        enc = true;
                        elegida = vFMBismuto[k];
                    }
                }
            }
            if (enc){   //si alguna cercana es de madrid, miro si vende BISMUTO y tiene unidades
                std::vector<PA_Medicamento*> vPAM= elegida->buscarMedicamNombre("BISMUTO");
                bool enc1=false;
                for (int j=0; j<vPAM.size() && !enc1; j++) {
                    if (vM[i]->comprarMedicam(1,vPAM[j],elegida)==1) {
                        std::cout << "-->Usuario " << vM[i]->getId() << " SI encontro BISMUTO en " << elegida->getCif() << std::endl;
                        std::cout << "   Unidades stock medicamento " << vPAM[j]->getNombre() << " que quedan:" << elegida->buscaMedicamID(vPAM[j]->getIdNum())  << std::endl;
                        enc1 = true;
                    }
                }
            }else
                std::cout << "Usuario " << vM[i]->getId() << " No encontro BISMUTO entre sus 3 farmacias mas cercanas" << std::endl;
        }
        std::cout << std::endl;
        //borramos todos los Bismutos de todas las farmacias y mediexpress  PR6
        std::vector<PA_Medicamento*> bismuto= medi.buscarCompuesto("BISMUTO");
        if (bismuto.size()==0)
            std::cout << "No se encontro Medicamentos con BISMUTO" << std::endl;
        for (int i=0; i<bismuto.size(); i++) {
            if (medi.eliminarMedicamento(bismuto[i]->getIdNum()))
                std::cout << "Se pudo eliminar el " << bismuto[i]->getNombre() << " !!!" << std::endl;
            else
                std::cout << "NO se encontro el " << bismuto[i]->getNombre() << " !!!" << std::endl;
            if (!medi.buscarCompuesto(bismuto[i]->getIdNum()))
                std::cout << "NO Existe el " << bismuto[i]->getNombre() << std::endl;
            else
                std::cout << "Existe el " << bismuto[i]->getNombre() << std::endl;
        }

        //PAREJAS
        std::cout << "En NUEVA FARMACIA, el Usuario mas cercano compra MAGNESIO OXIDO" << std::endl;
        medi.Farmacia_parejas();

        //Prueba de imagen
        //medi.PintarImagen("../imagen");

    }catch (std::out_of_range &e){
        std::cerr << e.what() << std::endl;
    }catch (std::runtime_error &e){ //std::ifstream::failure &e){
        std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
    }catch (std::bad_alloc &e){
        std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;
    }

    return 0;
}

