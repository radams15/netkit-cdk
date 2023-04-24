package Machine;

use strict;
use warnings;

use List::Util qw(any);

=head1 DESCRIPTION
This module stores the machine configuration.
=cut
sub new {
	my $class = shift;
	
	my %params = @_;
	
	my $name = $params{name};
	my @interfaces = @{ $params{interfaces} // [] };
	my @routes = @{ $params{routes} // [] };
	my @attachments = @{ $params{attachments} // [] };
	my @rules = @{ $params{rules} // []};

	my $self = bless {
		name => $name,
		interfaces => \@interfaces,
		conf_buffer => $params{extra_conf} // '',
		startup_buffer => $params{extra} // '',
		routes => \@routes,
		attachments => \@attachments,
		rules => \@rules,
		switch => $params{switch},
		vlan_filtering => $params{vlan_filtering} // 0,
		stp => $params{disable_stp}? 0 : 1,
	}, $class;

	return $self;
}

sub ips {
	my $class = shift;
	
	my %out;
	
	for(@{$class->{interfaces}}) {
		my $ip = $_->{ip};
		$ip =~ s/\/\d+$//g;
		
		$out{$_->{eth}} = $ip;
	}
	
	\%out;
}

sub rule {
	my $class = shift;
	
	my ($rule) = @_;
	
	push @{$class->{rules}}, $rule;
}

sub extra {
	my $class = shift;
	
	my %params = @_;
	
	$class->{startup_buffer} .= "\n######### $params{header} #########\n\n" if(defined $params{header});
	
	$class->{startup_buffer} .= "\n" . $params{data} . "\n";
}

sub dump_startup {
	my $class = shift;
	my %params = @_;
	
	# Dump the interface IPs and MACs.
	print "# Interface Configuration\n\n";
	for (@{$class->{interfaces}}){
		$_->dump;
	}
	
	# Dump the static routes
	print "# Static Route Configuration\n\n";
	for (@{$class->{routes}}){
		$_->dump;
	}

	if(defined($class->{switch})) {
		print "# Switch Configuration\n\n";
		print "
ip link add sw0 type bridge \\
	stp_state $class->{stp} \\
	priority 9000 \\
	vlan_filtering $class->{vlan_filtering}\n\n";

		for(@{$class->{interfaces}}) {
			my $eth = 'eth'.$_->{eth};
			
			print "ip link set dev $eth group 11\n";
		}
		
		print "\nip link set group 11 master sw0\n";
		print "ip link set group 11 promisc on\n\n";
		
		print "ip link set dev sw0 up\n\n";
	}

	unless($params{disable_vlans}) {
		# Dump the VLANs
		print "# VLAN Configuration\n\n";
		for (grep {defined($_->{vlan})} @{$class->{attachments}}) { # For every attachment with a VLAN		
			my $vlan = $_->{vlan};
			
			print "bridge vlan add vid $vlan->{vid} ";
			
			if(defined $_->{untagged}){
				print 'pvid untagged ';
			}
			
			print "dev eth$_->{eth}\n";
		}
	}
	
	unless($params{disable_firewalls}) {
		print "# Firewall Configuration\n\n";
		
		if (any {$_->{stateful}} @{$class->{rules}}) { # Add stateful rules if any of the rules has stateful=1
			print "\niptables -A FORWARD -m state --state RELATED,ESTABLISHED -j ACCEPT \n\n";
		}
		
		# Dump the firewall rules
		for (@{$class->{rules}}){
			$_->dump;
		}
	}
	
	print "# Extra Configuration\n\n";
	
	# Add the extra startup from the extra parameter.
	print $class->{startup_buffer}, "\n";
}

sub dump_conf {
	my $class = shift;
	
	for (grep {defined($_->{lan})} @{$class->{attachments}}) { # For every attachment of a LAN
		my $lan = $_->{lan};
	
		# Put 'machine[eth_num]=lan' into the lab.conf	
		print $class->{name}, '[', $_->{eth} . "]=$lan->{name}\n";
	}
		
	# Add the extra conf from the extra_conf parameter.
	print $class->{conf_buffer}, "\n";
}

=pod # TODO BROKEN
sub attach {
	my $class = shift;
	
	for(@_) {
		if(defined $_->{machine}) {
			$_->{lan} = Attachment::generate_lan_name ($_->{machine}, $class);
			
			push @{$_->{machine}->{attachments}}, $_;
		}
		
		push @{$class->{attachments}}, $_;
	}
	
	$class;
}
=cut

1;
