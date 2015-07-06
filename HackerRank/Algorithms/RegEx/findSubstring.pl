# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
#!/usr/bin/perl
use strict;
use warnings;

my $num = <STDIN>; chomp $num;
my @input;
for (my $i=0; $i<$num; $i++) {
    my $line = <STDIN>; chomp $line;
    while ($line =~ /(\w*)\W+(.*)/) {
        push @input, $1;
        $line = $2;
    }
    if ($line =~ /(\w+)/) {
        push @input, $line;
    }
}

my $tc = <STDIN>; chomp $tc;
for (my $i=0; $i<$tc; $i++) {
    my $ss = <STDIN>; chomp $ss;
    my $ctr=0;
    foreach my $w (@input) {
        my $word = $w;
        while ($w =~ /(\w+?)$ss(\w+)/) {
            $ctr += 1;
            $w = $1 . $2;
        }
    }
    print $ctr, "\n";
}
