package Lab;

use strict;
use warnings;

use List::Util qw(any);
use File::Spec qw(rel2abs);
use File::Copy::Recursive qw(dircopy);

=head1 DESCRIPTION
This module stores information about the lab which is output to the lab.conf file.
=cut
sub new {
	my $class = shift;
	my (%params) = @_;
	
	die "Must specify data_dir" if not defined($params{data_dir});

	printf "Name: %s\n", ($params{name} // 'BAD');

	my $self = bless {
		name => ($params{name} // 'Unknown'),
		description => $params{description} // 'None',
		version => $params{version} // 'None',
		author => $params{author} // 'Unknown',
		email => $params{email} // 'Unknown',
		out_dir => $params{out_dir} // 'lab',
		data_dir => $params{data_dir},
                shared => $params{shared} // '',
	}, $class;

	return $self;
}

=item dump()

Outputs the content of lab.conf into the folder defined as out_dir.

Dumps every machine passes as args, which dumps its' own content in the lab.conf and its' own startup files.

=back
=cut
sub dump {
	my $class = shift;
	my %params = @_;
	
	my @machines = @{ $params{machines} };
	
	print "Machines: ", scalar @machines, "\n\n";
	
	if (! -e $class->{out_dir}) {
		mkdir($class->{out_dir});
	}
	
	## Create lab.conf
	
	my $conf_file = "$class->{out_dir}/lab.conf";
	
	print "* Dumping $conf_file\n";
	open FH, '>', $conf_file;
	select FH;
	
	print "LAB_NAME=$class->{name}
LAB_DESCRIPTION=$class->{description}
LAB_VERSION=$class->{version}
LAB_AUTHOR=$class->{author}
LAB_EMAIL=$class->{email}\n\n";
	
	for (@machines) {
		$_->dump_conf;
	}
	
	select STDOUT;
	close FH;
	
	print "* Dumping Startup Files\n";
	
	## Create .startup files.
	for (@machines) {
		my $name = $_->{name};
		
		my $fname = "$class->{out_dir}/$name.startup";
		
		print "\t* Dumping $fname\n";
		
		open FH, '>', $fname;
		select FH;
		
		print "###### $name ######\n\n";
		
		$_->dump_startup(
			disable_vlans => $params{disable_vlans} // 0,
			disable_firewalls => $params{disable_firewalls} // 0,
		);

		print "\n###### Shared Startup ######\n\n";

		print $class->{shared}, "\n\n";
		
		select STDOUT;
		close FH;
	}
	
	print "* Copying Data Folders\n";
	
	## Copy override files
	
	my @machine_names = map {$_->{name}} @machines;
	my $data_dir = $class->{data_dir};
	
	for my $machine (@machine_names) {
		my $expected_folder = File::Spec->rel2abs("$data_dir/$machine");
		my $dest_folder = File::Spec->rel2abs($class->{out_dir}."/$machine");
		
		if(-d $expected_folder) { # Source folder exists
				print "\t* Copy $expected_folder to dest_folder\n";
				dircopy($expected_folder, $dest_folder) or die("$!\n");
		}else { # No source folder exists, create an empty one.
			print "\t* Create $dest_folder for $machine\n";
			mkdir $dest_folder;
			
			open FH, '>', "$dest_folder/.gitkeep"; # Make file so git commits the folder.
			close FH;
		}
	}
	
	for my $folder (<$data_dir/*>) {
			$folder =~ s/$data_dir\///g;
			
			if((any {$_ eq $folder} @machine_names) || $folder eq 'shared') {
				print "\t* Copy $folder to $class->{out_dir}/$folder\n";
				dircopy("$data_dir/$folder", "$class->{out_dir}/$folder") or die("$!\n");
			}else {
				print "\t* Create folder for machine $folder\n";
			}
	}
	
	## Create lab.dep
	
	open FH, '>', "$class->{out_dir}/lab.dep";
	close FH;
}

1;
