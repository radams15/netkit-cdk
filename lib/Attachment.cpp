//
// Created by rhys on 24/02/23.
//
#include "Attachment.h"

#include <iostream>

void Attachment::dump(std::ostream &ostream, std::string machine) {
    ostream << machine << "[" << eth << "]=" << machine << std::endl;
}

