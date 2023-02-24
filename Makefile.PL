use 5.032001;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    NAME              => 'Netkit',
    VERSION_FROM      => 'lib/Netkit/Lab.pm', # finds $VERSION, requires EU::MM from perl >= 5.5
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    ABSTRACT_FROM     => 'lib/Netkit/Lab.pm', # retrieve abstract from module
    AUTHOR            => 'Rhys Adams <rhys@therhys.co.uk>',
    LICENSE           => 'perl',
);
