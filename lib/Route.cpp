//
// Created by rhys on 24/02/23.
//

#include "Route.h"

#include <iostream>

#define DEF_SETTER(name, var, type) Route& Route::name(type name){ var = name ; return *this; }

void Route::dump(std::ostream& ostream) {
    std::cout << "Dump route!\n\n";

    ostream << "ip route add " << _dst;

    if(! _via.empty()){
        ostream << " via " << _via;
    }

    if(! _dev.empty()){
        ostream << " dev " << _dev;
    }

    ostream << std::endl;
}

DEF_SETTER(dst, _dst, std::string);
DEF_SETTER(via, _via, std::string);
DEF_SETTER(dev, _dev, std::string);