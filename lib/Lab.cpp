//
// Created by rhys on 24/02/23.
//

#include "Lab.h"

#include <iostream>
#include <fstream>

#include <filesystem>

namespace fs = std::filesystem;

void Lab::dump(std::vector<Machine> machines) {
    std::cout << machines.size() << " Machines!" << std::endl << std::endl;

    if(!fs::is_directory(out_dir) || !fs::exists(out_dir)) {
        fs::create_directories(out_dir);
    }

    std::string conf_file = out_dir + "/lab.conf";
    std::ofstream conf_stream(conf_file);

    conf_stream << "LAB_DESCRIPTION=" << description
                << "\nLAB_VERSION=" << version
                << "\nLAB_AUTHOR=" << author
                << "\nLAB_EMAIL=" << email
                << "\n\n";

    for(auto machine : machines) {
        machine.dump_conf(conf_stream);
    }

    conf_stream.close();

    std::cout << "* Dumping Startup Files" << std::endl;

    for(auto machine : machines) {
        std::string fname = out_dir + "/" + machine.name + ".startup";

        std::cout << "\tDumping " << fname << std::endl;

        std::ofstream startup_stream(fname);

        machine.dump_startup(startup_stream);

        startup_stream.close();
    }

    std::cout << "* Copying Data Folders" << std::endl;

    for(auto folder : fs::directory_iterator{fs::path{data_dir}}){
        if(is_directory(folder.path())){
            for(auto machine : machines){
                if(machine.name == folder.path().filename().string()){
                    std::cout << "Copy " << folder.path().filename().string() << " to " << out_dir << std::endl;

                    copy(
                            folder.path(),
                            fs::path{ out_dir + "/" + folder.path().filename().string() },
                            fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                }
            }
        }
    }

    std::ofstream lab_dep(out_dir + "/lab.dep");
    lab_dep.close();
}
