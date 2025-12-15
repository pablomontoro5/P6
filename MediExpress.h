//
// Created by Lazaro Ruiz on 08/10/2025.
//

#ifndef P2_MEDIEXPRESS_H
#define P2_MEDIEXPRESS_H

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "PA_Medicamento.h"
#include "Laboratorio.h"
#include "Farmacia.h"
#include "THashMedicam.h"
#include "MallaRegular.h"
#include "Usuario.h"

class MediExpress {
private:
    std::multimap<std::string,Farmacia> _pharmacy;
    std::list<Laboratorio> _labs;
    THashMedicam idMedication;
    std::vector<int> _vMedi;
    std::multimap<std::string,PA_Medicamento*> _nombMedication;
    std::list<PA_Medicamento> listaPaMed;
    MallaRegular<Farmacia*> _grid;
    std::map<int,Usuario> users;
    float distancia(float lat1, float lon1, float lat2, float lon2); //Parejas

public:
    void _postprocesarCargas(const std::string &fichFarmacias);
    void _cargarLaboratoriosDesdeFichero(const std::string& _ficheroLaboratorios);

    void _cargarUsuariosDesdeFichero(const std::string &nomFichUsu);
    std::vector<Laboratorio*> buscarLabs(const std::string &nombrePa);


    std::vector<Farmacia*> buscarFarmacias(UTM utm, int n);
    void _cargarMedicamentosDesdeFichero(const std::string& _ficheroMedicamentos);

    void _cargarFarmaciasDesdeFichero(const std::string& _ficheroFarmacias);
    MediExpress(const std::string &nomFichPaMed, const std::string &nomFichLab,
                const std::string &nomFichFar, const std::string &nomFichUsu, unsigned long tam, float lamda);

    std::vector<PA_Medicamento*> getMedicamentosSinLab();
    Laboratorio* buscarLab(const std::string &nombreLab);

    void _metodoDeFarmaciaParteParejas();
    void suministrarFarmacia(Farmacia *f, int id_num, int n);

    MediExpress();
    std::vector<Usuario*> buscaUsuario(const std::string &prov);

    std::vector<Farmacia*> buscarFarmacias(const std::string &provincia);
    bool eliminarMedicamento(int id_num);

    void suministrarMed(PA_Medicamento *pa, Laboratorio *l);
    PA_Medicamento* buscarCompuesto(int _idDelNumero);

    std::vector<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    Farmacia* buscarFarmacia(const std::string &cif);

    void mostrarEstadoTabla();
    std::vector<PA_Medicamento*> buscarCompuesto(const std::string &nombrePA);


    void asignarLabsMadridAMedicamentosSinAsignar();
    static unsigned long contarMedicamentos(const std::string &nomFichPaMed);

    void PintarImagen(std::string nomFich);   //PR6 voluntaria
};


#endif //P2_MEDIEXPRESS_H
