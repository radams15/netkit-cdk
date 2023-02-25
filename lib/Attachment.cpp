//
// Created by rhys on 24/02/23.
//
#include "Attachment.h"

#include <iostream>

#define DEF_SETTER(name, var, type) Attachment& Attachment::name(type name){ var = name ; return *this; }

void Attachment::dump(std::ostream &ostream, std::string machine) {
    ostream << machine << "[" << _eth << "]=" << machine << std::endl;
}

DEF_SETTER(lan, _lan, Lan);
DEF_SETTER(eth, _eth, int);