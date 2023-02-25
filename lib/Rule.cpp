//
// Created by rhys on 24/02/23.
//

#include "Rule.h"

#include <iostream>

#define DEF_SETTER(name, var, type) Rule& Rule::name(type name){ var = name ; return *this; }

void Rule::dump(std::ostream& ostream) {
    std::cout << "Dump Rule!\n\n";

    ostream << "iptables";

    if(! _table.empty()) ostream << " -t " << _table;
    if(! _chain.empty()) ostream << " -A " << _chain;
    if(_stateful) ostream << " -m state --state NEW";
    if(! _proto.empty()) ostream << " -p " << _proto;
    if(! _dst.empty()) ostream << " -d " << _dst;
    if(! _src.empty()) ostream << " -s " << _src;
    if(_dport) ostream << " --dport " << _dport;
    if(_sport) ostream << " --_sport " << _sport;
    if(! _action.empty()) ostream << " -j " << _action;
    if(! _to_dst.empty()) ostream << " --to-destination " << _to_dst;
    if(! _to_src.empty()) ostream << " --to-source " << _to_src;
    if(! _policy.empty()) ostream << " --policy " << _policy;

    ostream << std::endl;
}

Rule Rule::dnat(std::string dst, std::string proto, int port) {
    return Rule{
            ._chain = "PREROUTING",
            ._proto = proto,
            ._dport = port,
            ._action = "DNAT",
            ._to_dst = dst,
    };
}

DEF_SETTER(table, _table, std::string);
DEF_SETTER(chain, _chain, std::string);
DEF_SETTER(stateful, _stateful, bool);
DEF_SETTER(proto, _proto, std::string);
DEF_SETTER(dst, _dst, std::string);
DEF_SETTER(src, _src, std::string);
DEF_SETTER(dport, _dport, int);
DEF_SETTER(sport, _sport, int);
DEF_SETTER(action, _action, std::string);
DEF_SETTER(to_dst, _to_dst, std::string);
DEF_SETTER(to_src, _to_src, std::string);
DEF_SETTER(policy, _policy, std::string);