use warnings;
use strict;

use lib '.';

use Netkit;

my $test = Netkit::Machine->new
            ->name('a');

my $lab = Netkit::Lab->new
            ->name('test')
            ->data_dir('data')
            ->out_dir('res')
            ->description('A LAB')
            ->machine($test);

$lab->dump();