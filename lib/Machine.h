//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_MACHINE_H
#define NETKITSDK_MACHINE_H


#include <vector>
#include <string>

#include "Interface.h"
#include "Route.h"
#include "Attachment.h"
#include "Rule.h"

struct Machine {
    std::string name;
    std::vector<Interface> interfaces;
    std::string extra_conf;
    std::string extra_startup;
    std::vector<Route> routes;
    std::vector<Attachment> attachments;
    std::vector<Rule> rules;

    void rule(Rule rule);
    void dump_startup(std::ostream& ostream);
    void dump_conf(std::ostream& ostream);
};


#endif //NETKITSDK_MACHINE_H
