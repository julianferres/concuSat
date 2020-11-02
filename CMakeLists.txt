cmake_minimum_required(VERSION 3.17)
project(ConcuSat)

include_directories(config)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        concuSat
        config/Config.cpp
        config/Config.h
        observatorio/Observatorio.cpp observatorio/Observatorio.h
        observatorio/Camara.cpp observatorio/Camara.h
        logger/Logger.cpp logger/Logger.h
        observatorio/Ajustador.cpp observatorio/Ajustador.h
        main.cpp
        concu/memoria/MemoriaCompartida.cpp concu/memoria/MemoriaCompartida.h concu/señales/EventHandler.h concu/señales/SignalHandler.cpp concu/señales/SignalHandler.h concu/señales/ObservatorioHandlerSIGINT.h concu/señales/AjustadorHandlerSIGINT.h concu/fifos/Fifo.cpp concu/fifos/Fifo.h concu/fifos/FifoEscritura.cpp concu/fifos/FifoEscritura.h concu/fifos/FifoLectura.cpp concu/fifos/FifoLectura.h)
