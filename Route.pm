package Route;

use strict;
use warnings;

sub new {
	my $class = shift;
	
	my %params = @_;

	my $self = bless {
		dst => $params{dst},
		via => $params{via},
		dev => $params{dev},
	}, $class;

	return $self;
}

1;
