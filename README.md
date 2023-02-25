# Netkit SDK

A more verbose yet more understandable way to create netkit machines using code.

Written in Perl, with few dependencies.

Generates a standalone netkit lab from a selection of configurable objects.

Allows configurations of:

- LANs
- Interface attachments
- Static Routes
- Firewall rules
- NAT rules

Other elements of startup files can be added using the Machine extra field.

## Example Lab

Place machine data folders in the ./data directory, run `perl main.pl`, and a lab folder appears in the ./res directory.

```perl
#!/usr/bin/perl

use strict;
use warnings;

use Machine;
use Lan;
use Lab;
use Interface;
use Route;
use Attachment;

my $lab = Lab->new(
	machine_name => 'TestLab',
	_out_dir => 'res',
	_data_dir => 'data',
);


my $ext_www_lan = Lan->new('ExtWWW');
my $dmz_lan = Lan->new('Dmz');
my $staff_lan = Lan->new('Staff');

my $r2 = Machine->new(
	machine_name => 'r2',
	interfaces => [
		Interface->new(
			_eth => 0,
			ip => '192.168.0.3/24',
			_mac => 'a8:20:66:2d:30:bf',
		),
		Interface->new(
			_eth => 1,
			ip => '10.0.0.1/20',
			_mac => 'a8:20:66:3e:42:cf',
		),
	],
	routes => [
		Route->new(
			_dst => 'default',
			via => '192.168.0.1'
		),
		Route->new(
			_dst => '172.16.0.0/24',
			via => '192.168.0.2'
		),
	],
	attachments => [
		Attachment->new(
			_lan => $dmz_lan,
			_eth => 0
		),
		Attachment->new(
			_lan => $staff_lan,
			_eth => 1
		),
	],
	rules => [
		Rule->new(
			policy => 'FORWARD DROP',
		),
	],
);

my $gw = Machine->new(
	machine_name => 'gw',
	interfaces => [
		Interface->new(
			_eth => 0,
			ip => '80.64.157.254',
		),
		Interface->new(
			_eth => 1,
			ip => '192.168.0.1/24',
		),
	],
	routes => [
		Route->new(
			_dst => '172.16.0.0/24',
			via => '192.168.0.2'
		),
		Route->new(
			_dst => '10.0.0.0/20',
			via => '192.168.0.3'
		),
	],
	attachments => [
		Attachment->new(
			_lan => $ext_www_lan,
			_eth => 0
		),
		Attachment->new(
			_lan => $dmz_lan,
			_eth => 1
		),
	],
	rules => [
		Rule->new(
			policy => 'FORWARD DROP',
		)
	],
);

my $staff_1 = Machine->new(
	machine_name => 'Staff-1',
	interfaces => [
		Interface->new(
			_eth => 0,
			ip => '10.0.0.5/20',
			_mac => 'a8:30:67:3f:42:cf',
		),
	],
	routes => [
		Route->new(
			_dst => 'default',
			via => '10.0.0.1'
		),
	],
	attachments => [
		Attachment->new(
			_lan => $staff_lan,
			_eth => 0,
		),
	],
);

for my $port (25, 587, 993) {
	$gw->rule(
		Rule->new(
			_chain => 'FORWARD',
			_stateful => 1,
			_proto => 'tcp',
			_dst => '172.16.0.6',
			dport => $port,
			_action => 'ACCEPT',
		)
	);
	
	$gw->rule(
		Rule->new(
				_table => 'nat',
				_chain => 'PREROUTING',
				_proto => 'tcp',
				_to_dst => '172.16.0.6',
				dport => $port,
				_action => 'DNAT',
		)
	);
}

$lab->dump($staff_1, $r2, $gw);
```
