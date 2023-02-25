//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_RULE_H
#define NETKITSDK_RULE_H

#include <string>
#include <vector>

#define DECL_SETTER(name, var, type) Rule& name(type name)

struct Rule {
    std::string _table;
    std::string _chain;
    bool _stateful;
    std::string _proto;
    std::string _dst;
    std::string _src;
    int _dport;
    int _sport;
    std::string _action;
    std::string _to_dst;
    std::string _to_src;
    std::string _policy;

    DECL_SETTER(table, _table, std::string);
    DECL_SETTER(chain, _chain, std::string);
    DECL_SETTER(stateful, _stateful, bool);
    DECL_SETTER(proto, _proto, std::string);
    DECL_SETTER(dst, _dst, std::string);
    DECL_SETTER(src, _src, std::string);
    DECL_SETTER(dport, _dport, int);
    DECL_SETTER(sport, _sport, int);
    DECL_SETTER(action, _action, std::string);
    DECL_SETTER(to_dst, _to_dst, std::string);
    DECL_SETTER(to_src, _to_src, std::string);
    DECL_SETTER(policy, _policy, std::string);

    void dump(std::ostream& ostream);

    static Rule dnat(std::string dst, std::string proto, int port);
};

#undef DECL_SETTER

#endif //NETKITSDK_RULE_H
