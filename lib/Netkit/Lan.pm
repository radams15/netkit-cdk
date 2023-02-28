package Lan;

use strict;
use warnings;

=head1 DESCRIPTION
Simple module which again acts as a struct to store the lan name.
=cut
sub new {
	my $class = shift;
	my ($name) = @_;

	my $self = bless {
		name => $name,
	}, $class;

	return $self;
}

1;
