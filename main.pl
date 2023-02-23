#!/usr/bin/perl

use strict;
use warnings;

use lib '.';
use Machine;
use Lan;
use Lab;
use Interface;

my $lab = Lab->new(
	name => 'TestLab',
	out_dir => 'res',
);
my $ext_www_lan = Lan->new('ExtWWW');
my $dmz_lan = Lan->new('Dmz');
my $staff_lan = Lan->new('Staff');


my $r2 = Machine->new(
	name => 'r2',
	interfaces => [
		Interface->new(
			eth => 0,
			ip => '192.168.0.3/24',
			mac => 'a8:20:66:2d:30:bf',
		),
		Interface->new(
			eth => 1,
			ip => '10.0.0.1/20',
			mac => 'a8:20:66:3e:42:cf',
		)
	] # Eth0, Eth1
);

my $staff_1 = Machine->new(
	name => 'Staff-1',
	interfaces => [
		Interface->new(
			eth => 0,
			ip => '10.0.0.5/20',
			mac => 'a8:30:67:3f:42:cf',
		)
	] # Eth0
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


$r2->extra(
	header => 'Firewall Rules',
	data =>'iptables --policy FORWARD DROP',
);


$lab->dump($staff_1, $r2);
