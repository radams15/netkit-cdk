//
// Created by rhys on 24/02/23.
//

#include "Route.h"

#include <iostream>

void Route::dump(std::ostream& ostream) {
    std::cout << "Dump route!\n\n";

    ostream << "ip route add " << dst;

    if(! via.empty()){
        ostream << " via " << via;
    }

    if(! dev.empty()){
        ostream << " dev " << dev;
    }

    ostream << std::endl;
}
