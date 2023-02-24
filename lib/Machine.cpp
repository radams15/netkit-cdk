//
// Created by rhys on 24/02/23.
//

#include "Machine.h"

#include <iostream>
#include <algorithm>

void Machine::rule(Rule rule) {
    rules.push_back(rule);
}

void Machine::dump_startup(std::ostream& ostream) {
    std::cout << "Dump startup!\n\n";

    for(auto i : interfaces){
        i.dump(ostream);
    }

    for(auto r : routes){
        r.dump(ostream);
    }

    // If any rules have stateful=true set.
    if(std::any_of(rules.begin(), rules.end(), [](auto r){ return r.stateful; })){
        ostream << "\niptables -A FORWARD -m state --state RELATED,ESTABLISHED -j ACCEPT \n\n";
    }

    for(auto r : rules) {
        r.dump(ostream);
    }

    ostream << extra_startup << std::endl;
}

void Machine::dump_conf(std::ostream& ostream) {
    std::cout << "Dump lab.conf!\n\n";

    for(auto att : attachments) {
        att.dump(ostream, name);
    }

    ostream << extra_conf << std::endl;
}
