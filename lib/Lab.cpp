//
// Created by rhys on 24/02/23.
//

#include "Lab.h"

#include <iostream>
#include <fstream>

#include <filesystem>

#define DEF_SETTER(name, var) Lab& Lab::name(std::string name){ var = name ; return *this; }

namespace fs = std::filesystem;

void Lab::dump() {
    return DUMP_VEC(_machines);
}

void Lab::DUMP_VEC(std::vector<Machine> machines) {
    std::cout << machines.size() << " Machines!" << std::endl << std::endl;

    if(!fs::is_directory(_out_dir) || !fs::exists(_out_dir)) {
        fs::create_directories(_out_dir);
    }

    std::string conf_file = _out_dir + "/lab.conf";
    std::ofstream conf_stream(conf_file);

    conf_stream << "LAB_DESCRIPTION=" << _description
                << "\nLAB_VERSION=" << _version
                << "\nLAB_AUTHOR=" << _author
                << "\nLAB_EMAIL=" << _email
                << "\n\n";

    for(auto machine : machines) {
        machine.dump_conf(conf_stream);
    }

    conf_stream.close();

    std::cout << "* Dumping Startup Files" << std::endl;

    for(auto machine : machines) {
        std::cout << "Machine name is now: " << machine.machine_name << std::endl;
        std::string fname = _out_dir + "/" + machine.machine_name + ".startup";

        std::cout << "\tDumping " << fname << std::endl;

        std::ofstream startup_stream(fname);

        machine.dump_startup(startup_stream);

        startup_stream.close();
    }

    std::cout << "* Copying Data Folders" << std::endl;

    for(auto folder : fs::directory_iterator{fs::path{_data_dir}}){
        if(is_directory(folder.path())){
            for(auto machine : machines){
                if(machine.machine_name == folder.path().filename().string()){
                    std::cout << "Copy " << folder.path().filename().string() << " to " << _out_dir << std::endl;

                    copy(
                            folder.path(),
                            fs::path{_out_dir + "/" + folder.path().filename().string() },
                            fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                }
            }
        }
    }

    std::ofstream lab_dep(_out_dir + "/lab.dep");
    lab_dep.close();
}

Lab& Lab::machine(Machine& machine) {
    _machines.push_back(machine);

    return *this;
};

DEF_SETTER(name, _name);
DEF_SETTER(description, _description);
DEF_SETTER(version, _version);
DEF_SETTER(author, _author);
DEF_SETTER(email, _email);
DEF_SETTER(out_dir, _out_dir)
DEF_SETTER(data_dir, _data_dir)