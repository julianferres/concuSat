//
// Created by julian on 11/1/20.
//

#ifndef CONCUSAT_SIGNALHANDLER_H
#define CONCUSAT_SIGNALHANDLER_H

#include <csignal>
#include <cstdio>
#include <memory.h>

#include "EventHandler.h"

class SignalHandler {

private:
    static SignalHandler *instance;
    static EventHandler *signal_handlers[NSIG];

    SignalHandler(void);

    static void dispatcher(int signum);

public:
    static SignalHandler *getInstance();

    static void destruir();

    EventHandler *registrarHandler(int signum, EventHandler *eh);

    int removerHandler(int signum);

};

#endif //CONCUSAT_SIGNALHANDLER_H
