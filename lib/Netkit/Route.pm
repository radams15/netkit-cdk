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

sub dump {
	my $class = shift;
	
	print "ip route add $class->{dst} ";
	
	print "via $class->{via} " if(defined $class->{via});
	print "dev $class->{dev} onlink " if(defined $class->{dev}); # Onlink = allow even if nexthop is invalid; requires dev to be used.
	
	print "\n";
}

1;
