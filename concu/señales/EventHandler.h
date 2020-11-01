//
// Created by julian on 11/1/20.
//

#ifndef CONCUSAT_EVENTHANDLER_H
#define CONCUSAT_EVENTHANDLER_H

class EventHandler {

public:
    virtual int handleSignal ( int signum ) = 0;
    virtual ~EventHandler () {};
};

#endif //CONCUSAT_EVENTHANDLER_H
