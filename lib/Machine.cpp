//
// Created by rhys on 24/02/23.
//

#include "Machine.h"

#include <iostream>
#include <algorithm>
#include <utility>

void Machine::dump_startup(std::ostream& ostream) {
    std::cout << "Dump startup!\n\n";

    for(auto i : interfaces){
        i.dump(ostream);
    }

    for(auto r : routes){
        r.dump(ostream);
    }

    // If any rules have _stateful=true set.
    if(std::any_of(rules.begin(), rules.end(), [](auto r){ return r._stateful; })){
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
        att.dump(ostream, machine_name);
    }

    ostream << extra_conf << std::endl;
}

Machine &Machine::interface(Interface interface) {
    interfaces.push_back(interface);
    return *this;
}

Machine &Machine::conf(std::string conf) {
    extra_conf += conf + "\n";
    return *this;
}

Machine &Machine::startup(std::string startup) {
    extra_startup += startup + "\n";
    return *this;
}

Machine &Machine::route(Route route) {
    routes.push_back(route);
    return *this;
}

Machine& Machine::rule(Rule rule) {
    rules.push_back(rule);

    return *this;
}

Machine &Machine::attachment(Attachment attachment) {
    attachments.push_back(attachment);
    return *this;
}

Machine &Machine::name(std::string name) {
    machine_name = std::move(name);
    std::cout << "Machine name: " << machine_name << std::endl;
    return *this;
}