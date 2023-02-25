//
// Created by rhys on 25/02/23.
//

#include "Lan.h"

Lan &Lan::name(std::string name) {
    _name = name;

    return *this;
}
