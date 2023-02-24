package Machine;

use strict;
use warnings;

sub new {
	my $class = shift;
	
	my %params = @_;
	
	my $name = $params{name};
	my @interfaces = @{ $params{interfaces} };
	my @routes = @{ $params{routes} };
	my @attachments = @{ $params{attachments} // [] };

	my $self = bless {
		name => $name,
		interfaces => \@interfaces,
		conf_buffer => $params{extra_conf} // '',
		startup_buffer => $params{extra} // '',
		routes => \@routes,
		attachments => \@attachments,
	}, $class;

	return $self;
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
	
	for (@{$class->{routes}}){
		print "ip route add $_->{dst} ";
		
		print "via $_->{via} " if(defined $_->{via});
		print "dev $_->{dev} " if(defined $_->{dev});
		
		print "\n";
	}
	
	print $class->{startup_buffer}, "\n";
}

sub dump_conf {
	my $class = shift;
			
	for (@{$class->{attachments}}) {
		my $lan = $_->{lan};
		
		print $class->{name}, '[', $_->{eth} . "]=$lan->{name}\n";
	}
		
	print $class->{conf_buffer}, "\n";
}

1;
