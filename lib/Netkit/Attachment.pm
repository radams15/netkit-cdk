package Attachment;

use strict;
use warnings;

=head1 DESCRIPTION

Simple module which is basically a struct.

Stores eth number and a Lan object.

=over 4

=item new()

Creates a new Attachment.

Usage:

 my $lan = Lan->new (eth => 0, lan => $lan, vlan=$vlan, group=$group);

=back
=cut

sub new {
	my $class = shift;
	my %params = @_;

	my $self = bless {
		eth => $params{eth},
		lan => $params{lan},
		vlan => $params{vlan},
		untagged => $params{untagged},
		group => $params{group},
		machine => $params{machine},
	}, $class;
	
	return $self;
}

sub generate_lan_name {
	my ($switch, $machine) = @_;
	
	my $out = join '-', sort ($switch->{name}, $machine->{name});
	$out =~ s/\-/\_/g;
	$out;
}

1;
