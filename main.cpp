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
    std::cout << "*** Programa de prueba 1: Ajuste del tamanio de la Malla Regular ***" << std::endl;
    try{
        MediExpress prueba("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv","../usuarios.csv",3310,0.65);
    }catch(std::runtime_error &rte){
        std::cerr << rte.what() << std::endl;
    }catch(std::out_of_range &oor){
        std::cerr << oor.what() << std::endl;
    }catch(std::bad_alloc &ba){
        std::cerr << ba.what() << std::endl;
    }catch(std::invalid_argument &inarg){
        std::cerr << inarg.what() << std::endl;
    }

    return 0;
}

