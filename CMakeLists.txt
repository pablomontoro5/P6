cmake_minimum_required(VERSION 3.31)
project(P6)

set(CMAKE_CXX_STANDARD 26)

add_executable(P6 main.cpp Farmacia.cpp Farmacia.h Laboratorio.cpp Laboratorio.h MediExpress.cpp MediExpress.h PA_Medicamento.cpp PA_Medicamento.h Stock.cpp Stock.h
        THashMedicam.cpp
        THashMedicam.h
        Entrada.h
        Casilla.h
        MallaRegular.h
        UTM.h
        Usuario.h
        Usuario.cpp)
