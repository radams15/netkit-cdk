//
// Created by rhys on 24/02/23.
//

#include "Rule.h"

#include <iostream>

void Rule::dump(std::ostream& ostream) {
    std::cout << "Dump Rule!\n\n";

    ostream << "iptables";

    if(! table.empty()) ostream << " -t " << table;
    if(! chain.empty()) ostream << " -A " << chain;
    if(stateful) ostream << " -m state --state NEW";
    if(! proto.empty()) ostream << " -p " << proto;
    if(! dst.empty()) ostream << " -d " << dst;
    if(! src.empty()) ostream << " -s " << src;
    if(dport) ostream << " --dport " << dport;
    if(sport) ostream << " --sport " << sport;
    if(! action.empty()) ostream << " -j " << action;
    if(! to_dst.empty()) ostream << " --to-destination " << to_dst;
    if(! to_src.empty()) ostream << " --to-source " << to_src;
    if(! policy.empty()) ostream << " --policy " << policy;

    ostream << std::endl;
}
