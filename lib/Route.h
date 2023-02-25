//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_ROUTE_H
#define NETKITSDK_ROUTE_H

#include <string>

#define DECL_SETTER(name, var, type) Route& name(type name)

struct Route {
    std::string _dst;
    std::string _via;
    std::string _dev;

    DECL_SETTER(dst, _dst, std::string);
    DECL_SETTER(via, _via, std::string);
    DECL_SETTER(dev, _dev, std::string);

    void dump(std::ostream& ostream);
};


#undef DECL_SETTER

#endif //NETKITSDK_ROUTE_H
