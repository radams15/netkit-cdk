//
// Created by rhys on 24/02/23.
//

#include "Interface.h"

#include <iostream>


void Interface::dump(std::ostream& ostream) {
    std::cout << "Dump Interface!\n\n";

    if(! mac.empty()){
        ostream << "ip link set dev eth" << eth << " address " << mac << std::endl;
    }

    if(! ip.empty()){
        ostream << "ip addr add " << ip << "dev eth" << eth << std::endl;
    }

    ostream << "ip link set eth" << eth << " up" << std::endl << std::endl;
}
