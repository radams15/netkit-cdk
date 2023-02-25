//
// Created by rhys on 24/02/23.
//

#ifndef NETKIT_SDK_ATTACHMENT_H
#define NETKIT_SDK_ATTACHMENT_H

#include "Lan.h"

#define DECL_SETTER(name, var, type) Attachment& name(type name)

struct Attachment {
    Lan _lan;
    int _eth;

    DECL_SETTER(lan, _lan, Lan);
    DECL_SETTER(eth, _eth, int);

    void dump(std::ostream& ostream, std::string machine);
};

#undef DECL_SETTER

#endif //NETKIT_SDK_ATTACHMENT_H
