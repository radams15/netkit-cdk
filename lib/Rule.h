//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_RULE_H
#define NETKITSDK_RULE_H

#include <string>
#include <vector>

struct Rule {
    std::string table;
    std::string chain;
    bool stateful;
    std::string proto;
    std::string dst;
    std::string src;
    int dport;
    int sport;
    std::string action;
    std::string to_dst;
    std::string to_src;
    std::string policy;

    void dump(std::ostream& ostream);

    static Rule dnat(std::string dst, std::string proto, int port);
};


#endif //NETKITSDK_RULE_H
