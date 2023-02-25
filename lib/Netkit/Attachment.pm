package Attachment;

use strict;
use warnings;

sub new {
	my $class = shift;
	my %params = @_;
	
	my $self = bless {
		eth => $params{eth},
		lan => $params{lan},
	}, $class;
	
	return $self;
}

1;
