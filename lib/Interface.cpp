//
// Created by rhys on 24/02/23.
//

#include "Interface.h"

#include <iostream>

#define DEF_SETTER(name, var, type) Interface& Interface::name(type name){ var = name ; return *this; }


void Interface::dump(std::ostream& ostream) {
    std::cout << "Dump Interface!\n\n";

    if(! _mac.empty()){
        ostream << "ip link set dev _eth" << _eth << " address " << _mac << std::endl;
    }

    if(! _ip.empty()){
        ostream << "ip addr add " << _ip << "dev _eth" << _eth << std::endl;
    }

    ostream << "ip link set _eth" << _eth << " up" << std::endl << std::endl;
}

DEF_SETTER(eth, _eth, int);
DEF_SETTER(ip, _ip, std::string);
DEF_SETTER(mac, _mac, std::string);