# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
#!/usr/bin/perl

# Need to refactor! I'm not really a perl guy ;)

use strict;
use warnings;
my %table;
my $num = <STDIN>; chomp $num;

sub accumulate {
  my $key = $_[0];
  my $attr = $_[1];
  #print "for tag $key, pushing $attr \n";
  my $arrref1 = \@{$table{$key}};
  foreach my $val (@{$arrref1}) {
      if ($val eq $attr) {
          return;
      }
  }
  
  my $arrref = \@{$table{$key}}; 
  
  push (@{$arrref}, $attr);
}

sub addTable {
    my ($head, $attr) = @_;
    if (exists $table{$head}) {
        unless ($attr eq "") {
            &accumulate($head, $attr);
        }
    } else {
        my @arr;
        if ($attr eq "") {
        push @{$table{$head}} , "";
        } else {
            push @arr, $attr;
            push @{$table{$head}}, $attr;
        }
    }
}

sub processTag {
    my $tag = shift @_;
    my $head = "";
    my $attr = "";
    if ($tag =~ /^(\S+)(.*=.*)/) {
        $head = $1;
        $tag = $2;        
        while ($tag =~ /^.*?\s+([a-z]+)\s*=(.*)/) {    
            $attr = $1;
            $tag = $2;          
            &addTable($head, $attr);
        }
    } elsif ($tag =~ /^(\S+).*/) {
        $head = $1;
        &addTable($head, $attr);
    }

}

for (my $i=0; $i<$num; $i++) {
    my $line = <STDIN>; chomp $line;
    while ($line =~ /.*?<([^\/].*?)>(.*)/) {
        my $tag = $1;
        $line = $2;
        &processTag($tag);
    }
}

foreach my $key (sort keys %table) {
    print $key, ":";
    my $arrref = \@{$table{$key}};
    my @arr = sort @{$arrref};
    my $ctr=0;
    #print @{$table{$key}};
    for (my $ctr=0; $ctr < (scalar @arr); $ctr++) {
        print $arr[$ctr];
        if (($ctr + 1) != (scalar @arr)) {print ",";}
    }
    print "\n";
}

