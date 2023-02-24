//
// Created by rhys on 24/02/23.
//

#ifndef NETKIT_SDK_ATTACHMENT_H
#define NETKIT_SDK_ATTACHMENT_H

#include "Lan.h"

struct Attachment {
    Lan lan;
    int eth;

    void dump(std::ostream& ostream, std::string machine);
};

#endif //NETKIT_SDK_ATTACHMENT_H
