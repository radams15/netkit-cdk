//
// Created by rhys on 24/02/23.
//

#ifndef NETKIT_SDK_INTERFACE_H
#define NETKIT_SDK_INTERFACE_H

#include <string>

#define DECL_SETTER(name, var, type) Interface& name(type name)

struct Interface {
    int _eth;
    std::string _ip;
    std::string _mac;

    DECL_SETTER(eth, _eth, int);
    DECL_SETTER(ip, _ip, std::string);
    DECL_SETTER(mac, _mac, std::string);


    void dump(std::ostream& ostream);
};

#undef DECL_SETTER

#endif //NETKIT_SDK_INTERFACE_H
