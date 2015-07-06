# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
use strict;
use warnings;

my $num = <STDIN>; chomp $num;

for (my $i=0; $i<$num; $i++) {
    my $pan = <STDIN>; chomp $pan;
    if ($pan =~ /^[A-Z]{5}[0-9]{4}[A-Z]/) {
        print "YES\n";
    } else {
        print "NO\n";
    }
}