# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
#!/usr/bin/perl
use strict;
use warnings;

sub checkRange {
  my $v = shift @_;
  #my $v = int $vs;
  if ($v >= 0 && $v <= 255) {
      return 1;    
  }
  return 0;
}

my $num = <STDIN>; chomp $num;
my @input;
for (my $i=0; $i<$num; $i++) {
    my $line = <STDIN>; chomp $line;
    if ($line =~ /^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$/) {
        if (&checkRange($1) && &checkRange($2) && &checkRange($3) && &checkRange($4)) {
            print "IPv4\n";
            next;
        }
        } elsif ($line =~ /^[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}:[a-fA-F0-9]{1,4}$/) {
        print "IPv6\n";
        next;
    } 
    print "Neither\n";
}
