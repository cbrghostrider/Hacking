# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
use strict;
use warnings;

my $num = <STDIN>; chomp $num;
my @input;
for (my $i=0; $i<$num; $i++) {
    my $line = <STDIN>; chomp $line;
    my @words = split / /, $line;
    foreach my $word (@words) {
        push @input, $word;
    }
}

my $tc = <STDIN>; chomp $tc;
for (my $i=0; $i<$tc; $i++) {
    my $british = <STDIN>; chomp $british;

    my $checkstr = "";
    $checkstr  = $checkstr . ":" . $british . ":";
    if ($british =~ /(.*)our(.*)$/) {
        my $american = $1 . "or" . $2;        
        $checkstr = $checkstr . ":" . $american . ":";
    }

    my $ctr = 0;
    foreach my $word (@input) {
        if ($checkstr =~ /:$word:/) {
            $ctr++;
        }
    }

    print $ctr, "\n";
}
