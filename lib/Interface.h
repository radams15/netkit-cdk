//
// Created by rhys on 24/02/23.
//

#ifndef NETKIT_SDK_INTERFACE_H
#define NETKIT_SDK_INTERFACE_H

#include <string>

struct Interface {
    std::string eth;
    std::string ip;
    std::string mac;

    void dump(std::ostream ostream);
};


#endif //NETKIT_SDK_INTERFACE_H
