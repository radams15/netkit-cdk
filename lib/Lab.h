//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_LAB_H
#define NETKITSDK_LAB_H

#include <string>
#include "Machine.h"

#define DECL_SETTER(name, var) Lab& name(std::string name)

#ifdef SWIG
#define DUMP_VEC dump_vec
#else
#define DUMP_VEC dump
#endif

struct Lab {
    std::string _name;
    std::string _description;
    std::string _version;
    std::string _author;
    std::string _email;
    std::string _out_dir;
    std::string _data_dir;
    std::vector<Machine> _machines;

    DECL_SETTER(name, _name);
    DECL_SETTER(description, _description);
    DECL_SETTER(version, _version);
    DECL_SETTER(author, _author);
    DECL_SETTER(email, _email);
    DECL_SETTER(out_dir, _out_dir);
    DECL_SETTER(data_dir, _data_dir);

    Lab& machine(Machine& machine);

    void dump();
    void DUMP_VEC(std::vector<Machine> machines);
};

#undef DECL_SETTER

#endif //NETKITSDK_LAB_H
