package Machine;

use strict;
use warnings;

sub new {
	my $class = shift;
	
	my %params = @_;
	
	my $name = $params{name};
	my @interfaces = @{ $params{interfaces} };	

	my $self = bless {
		name => $name,
		interfaces => \@interfaces,
		conf_buffer => '',
		startup_buffer => '',
	}, $class;

	return $self;
}

sub attach {
	my $class = shift;
	
	my %params = @_;
	
	my $lan_name = $params{lan}->{name};
	my $eth = $params{eth};
	
	my $name = $class->{name};
	
	$class->{conf_buffer} .= $name . '[' . $eth . "]=$lan_name\n";
}

sub extra {
	my $class = shift;
	
	my %params = @_;
	
	$class->{startup_buffer} .= "\n######### $params{header} #########\n\n" if(defined $params{header});
	
	$class->{startup_buffer} .= "\n" . $params{data} . "\n";
}

sub dump_startup {
	my $class = shift;
	
	for (@{$class->{interfaces}}){
		print "ip link set dev eth$_->{eth} address $_->{mac}\n" if(defined $_->{mac});
		
		print "ip addr add $_->{ip} dev eth$_->{eth}\n" if(defined $_->{ip});
		
		print "ip link set eth$_->{eth} up\n";
		
		print "\n\n";
	}
	
	print $class->{startup_buffer}, "\n";
}

sub dump_conf {
	my $class = shift;
	
	print $class->{conf_buffer}, "\n";
}

1;
