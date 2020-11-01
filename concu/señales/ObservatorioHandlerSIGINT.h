//
// Created by julian on 11/1/20.
//

#ifndef CONCUSAT_OBSERVATORIOHANDLERSIGINT_H
#define CONCUSAT_OBSERVATORIOHANDLERSIGINT_H

#include <csignal>
#include <cassert>
#include <iostream>
#include "EventHandler.h"
#include "../../logger/Logger.h"

using namespace std;

class AjustadorHandlerSIGINT : public EventHandler {

private:
    sig_atomic_t gracefulQuit;

public:

    AjustadorHandlerSIGINT() : gracefulQuit(0) {
    }

    ~AjustadorHandlerSIGINT() {
    }

    virtual int handleSignal(int signum) {
        assert (signum == SIGINT);
        cout << "Se recibió la señal SIGINT en el observatorio, cuando termine la ronda finalizará el proceso" << endl;
        LOG_INFO("Se recibió la señal SIGINT en el observatorio, cuando termine la ronda finalizará el proceso");
        this->gracefulQuit = 1;
        return 0;
    }

    sig_atomic_t getGracefulQuit() const {
        return this->gracefulQuit;
    }

};

#endif //CONCUSAT_OBSERVATORIOHANDLERSIGINT_H
