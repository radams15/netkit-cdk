# Specification

```perl

use Lan;
use Machine;

my $ext_www_lan = Lan->new('ExtWWW');

my $dmz_lan = Lan->new('Dmz');

my $staff_lan = Lan->new('Staff');

my $r2 = Machine->new(
	'r2',
	(0, 1) # Eth0, Eth1
);

my $staff_1 = Machine->new(
	'Staff-1',
	(0) # Eth0
);

$staff_1->attach($staff_lan, 0); # Attach eth0 to $staff_lan

$r2->attach($dmz_lan, 0);
$r2->attach($staff_lan, 1);

$r2->extra('######### Firewall Rules #########

iptables --policy FORWARD DROP');
```