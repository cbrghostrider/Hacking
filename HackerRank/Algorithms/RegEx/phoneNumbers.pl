# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
use strict;
use warnings;

my $num = <STDIN>; chomp $num;
for (my $i=0; $i<$num; $i++) {
    my $line = <STDIN>; chomp $line;
    if ($line =~ /^\s*([0-9]+)[-\s]([0-9]+)[-\s]([0-9]+)/) {
        print "CountryCode=", $1, ",LocalAreaCode=", $2, ",Number=", $3, "\n";   
    }
}
