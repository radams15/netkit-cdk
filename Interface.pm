package Interface;

use strict;
use warnings;

sub new {
	my $class = shift;
	
	my %params = @_;

	my $self = bless {
		eth => $params{eth},
		ip => $params{ip},
		mac => $params{mac},
	}, $class;

	return $self;
}

1;
