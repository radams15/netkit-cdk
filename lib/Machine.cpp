//
// Created by rhys on 24/02/23.
//

#include "Machine.h"

#include <ostream>

void Machine::rule(Rule rule) {
    rules.push_back(rule);
}

void Machine::extra(std::string data) {
    extra_startup += data;
}

void Machine::dump_startup(std::ostream ostream) {
    ostream << "Dump startup!\n\n";
}

void Machine::dump_conf(std::ostream ostream) {
    ostream << "Dump lab.conf!\n\n";
}
