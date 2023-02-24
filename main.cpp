//
// Created by rhys on 24/02/23.
//

#include "Interface.h"
#include "Attachment.h"
#include "Lab.h"

int main(){
    Lab lab{
        .out_dir = "res",
        .data_dir = "data",
    };

    Lan dmz_lan{"Dmz"};
    Lan ext_www_lan{"Extwww"};
    Lan staff_lan{"Staff"};

    Machine r2{
            .name = "r2",
            .interfaces = {
                    Interface{
                        .eth = 0,
                        .ip = "192.168.0.3/24",
                        .mac = "a8:20:66:2d:30:bf"
                    },
                    Interface{
                            .eth = 1,
                            .ip = "10.0.0.1/20",
                            .mac = "a8:20:66:3e:42:cf"
                    },
            },
            .routes = {
                    Route{
                        .dst = "default",
                        .via = "192.168.0.1"
                    },
                    Route{
                        .dst = "172.16.0.0/24",
                        .via = "192.168.0.2"
                    }
            },
            .attachments = {
                    Attachment{
                        .lan = dmz_lan,
                        .eth = 0
                    },
                    Attachment{
                        .lan = staff_lan,
                        .eth = 1
                    }
            },
            .rules {
                    Rule{
                        .policy = "FORWARD DROP"
                    }
            }
    };

    Machine gw{
            .name = "gw",
            .interfaces = {
                    Interface{
                            .eth = 0,
                            .ip = "80.64.157.254"
                    },
                    Interface{
                            .eth = 1,
                            .ip = "192.168.0.1/24"
                    },
            },
            .routes = {
                    Route{
                            .dst = "172.16.0.0/24",
                            .via = "192.168.0.2"
                    },
                    Route{
                            .dst = "10.0.0.0/20",
                            .via = "192.168.0.3"
                    }
            },
            .attachments = {
                    Attachment{
                            .lan = ext_www_lan,
                            .eth = 0
                    },
                    Attachment{
                            .lan = dmz_lan,
                            .eth = 1
                    }
            },
            .rules {
                    Rule{
                            .policy = "FORWARD DROP"
                    }
            }
    };

    for(auto port : {25, 587, 993}) {
        gw.rule(Rule{
            .chain = "FORWARD",
            .stateful = true,
            .proto = "tcp",
            .dst = "172.16.0.6",
            .dport = port,
            .action = "ACCEPT"
        });

        gw.rule(Rule::dnat("172.16.0.6", "tcp", port));
    }

    lab.dump({gw, r2});
}