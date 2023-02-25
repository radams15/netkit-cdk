//
// Created by rhys on 24/02/23.
//

#include "Interface.h"
#include "Attachment.h"
#include "Lab.h"

int main(){
    Lab lab = Lab()
            .out_dir("res")
            .data_dir("data");

    Lan dmz_lan = Lan().name("Dmz");
    Lan ext_www_lan = Lan().name("Extwww");
    Lan staff_lan = Lan().name("Staff");

    Machine r2 = Machine()
            .name("r2")
            .interface(Interface().eth(0).ip("192.168.0.3/24").mac("a8:20:66:2d:30:bf"))
            .interface({
                               ._eth = 1,
                               ._ip = "10.0.0.1/20",
                               ._mac = "a8:20:66:3e:42:cf"
                       })
            .route(Route().dst("default").via("192.168.0.1"))
            .route({
                                ._dst = "172.16.0.0/24",
                                ._via = "192.168.0.2"
                        })
            .attachment(Attachment().lan(dmz_lan).eth(0))
            .attachment({
                                ._lan = staff_lan,
                                ._eth = 1
                        })
            .rule(Rule().policy("FORWARD DROP"));

    Machine gw{
            .machine_name = "gw",
            .interfaces = {
                    Interface{
                            ._eth = 0,
                            ._ip = "80.64.157.254"
                    },
                    Interface{
                            ._eth = 1,
                            ._ip = "192.168.0.1/24"
                    },
            },
            .routes = {
                    Route{
                            ._dst = "172.16.0.0/24",
                            ._via = "192.168.0.2"
                    },
                    Route{
                            ._dst = "10.0.0.0/20",
                            ._via = "192.168.0.3"
                    }
            },
            .attachments = {
                    Attachment{
                            ._lan = ext_www_lan,
                            ._eth = 0
                    },
                    Attachment{
                            ._lan = dmz_lan,
                            ._eth = 1
                    }
            },
            .rules {
                    Rule{
                            ._policy = "FORWARD DROP"
                    }
            }
    };

    for(auto port : {25, 587, 993}) {
        gw.rule({
            ._chain = "FORWARD",
            ._stateful = true,
            ._proto = "tcp",
            ._dst = "172.16.0.6",
            ._dport = port,
            ._action = "ACCEPT"
        });

        gw.rule(Rule::dnat("172.16.0.6", "tcp", port));
    }

    lab.dump({gw, r2});
}