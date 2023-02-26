package Vlan;

use strict;
use warnings;

sub new {
	my $class = shift;
	my ($vid) = @_;

	my $self = bless {
		vid => $vid,
	}, $class;

	return $self;
}

1;
