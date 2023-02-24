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

sub dump {
	my $class = shift;
	
	print "ip link set dev eth$class->{eth} address $class->{mac}\n" if(defined $class->{mac});
	
	print "ip addr add $class->{ip} dev eth$class->{eth}\n" if(defined $class->{ip});
	
	print "ip link set eth$class->{eth} up\n";
	
	print "\n\n";
}

1;
