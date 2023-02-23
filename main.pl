#!/usr/bin/perl

use strict;
use warnings;

use lib '.';
use Machine;
use Lan;
use Lab;

my $lab = Lab->new(
	name => 'TestLab',
	out_dir => 'res',
);
my $ext_www_lan = Lan->new('ExtWWW');
my $dmz_lan = Lan->new('Dmz');
my $staff_lan = Lan->new('Staff');


my $r2 = Machine->new(
	name => 'r2',
	interfaces => [0, 1] # Eth0, Eth1
);

my $staff_1 = Machine->new(
	name => 'Staff-1',
	interfaces => [0] # Eth0
);

$staff_1->attach(
	lan => $staff_lan,
	eth => 0 # Attach eth0 to $staff_lan
);


$r2->attach(
	lan => $dmz_lan,
	eth => 0
);

$r2->attach(
	lan => $staff_lan,
	eth => 1
);


$r2->extra('######### Firewall Rules #########

iptables --policy FORWARD DROP');


$lab->dump($staff_1, $r2);
