package Lab;

use strict;
use warnings;

sub new {
	my $class = shift;
	my %params = @_;

	my $self = bless {
		name => $params{name} // 'Unknown',
		description => $params{description} // 'None',
		version => $params{version} // 'None',
		author => $params{author} // 'Unknown',
		email => $params{email} // 'Unknown',
		out_dir => $params{out_dir} // '.',
	}, $class;

	return $self;
}

sub dump {
	my $class = shift;
	
	my @machines = @_;
	
	print "Machines: ", scalar @machines, "\n\n";
	
	if (! -e $class->{out_dir}) {
		mkdir($class->{out_dir});
	}
	
	my $conf_file = "$class->{out_dir}/lab.conf";
	
	open FH, '>', $conf_file;
	select FH;
	
	print "LAB_DESCRIPTION=$class->{description}
LAB_VERSION=$class->{version}
LAB_AUTHOR=$class->{author}
LAB_EMAIL=$class->{email}\n\n";
	
	for (@machines) {
		$_->dump_conf;
	}
	
	select STDOUT;
	close FH;
	
	# Create the .startup files.
	for (@machines) {
		my $name = $_->{name};
		
		my $fname = "$class->{out_dir}/$name.startup";
		
		print "* Dumping $fname\n";
		
		open FH, '>', $fname;
		select FH;
		
		print "****** $name ******\n\n";
		
		$_->dump_startup;
		
		select STDOUT;
		close FH;
	}
}

1;
