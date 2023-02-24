//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_LAB_H
#define NETKITSDK_LAB_H

#include <string>
#include "Machine.h"

struct Lab {
    std::string name;
    std::string description;
    std::string version;
    std::string author;
    std::string email;
    std::string out_dir;
    std::string data_dir;

    void dump(std::vector<Machine> machines);
};


#endif //NETKITSDK_LAB_H
