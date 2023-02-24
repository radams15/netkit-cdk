//
// Created by rhys on 24/02/23.
//

#ifndef NETKITSDK_ROUTE_H
#define NETKITSDK_ROUTE_H

#include <string>

struct Route {
    std::string dst;
    std::string via;
    std::string dev;

    void dump(std::ostream& ostream);
};


#endif //NETKITSDK_ROUTE_H
