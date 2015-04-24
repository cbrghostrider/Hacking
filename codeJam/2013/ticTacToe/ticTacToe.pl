#!/usr/bin/perl
use strict;
use warnings;
# perl reeeallllly isn't my strong suit ;)

sub compileTC {
    my ($l1, $l2, $l3, $l4) = @_;
    my $testcase = $l1 . ":" . $l2 . ":" . $l3 . ":" . $l4; 
    return $testcase;
}

sub decompileTC {
    my ($tc) = @_;
    my @grid = split(/:/, $tc);
    return @grid;
}

sub readInput {
    my ($ipfile) = @_;
    open FILE, "<$ipfile" or die "Could not open file $ipfile for reading: $!";
    my @fcontents = <FILE>;

    my $tests = $fcontents[0]; chomp $tests;
    my @retval;
    for (my $i = 0; $i < $tests; $i++) {
        my $line1 = $fcontents[5*($i)+1]; chomp $line1;
        my $line2 = $fcontents[5*($i)+2]; chomp $line2;
        my $line3 = $fcontents[5*($i)+3]; chomp $line3;
        my $line4 = $fcontents[5*($i)+4]; chomp $line4;

        my $testcase = &compileTC($line1, $line2, $line3, $line4); 
        push @retval, $testcase;
    }

    return @retval;
}

sub transpose {
    my ($input) = @_;
    my @grid = &decompileTC($input);
    my @g0s = split ('', $grid[0]); my @g1s = split ('', $grid[1]); my @g2s = split ('', $grid[2]); my @g3s = split ('', $grid[3]);
    my $ng0 = $g0s[0] . $g1s[0] . $g2s[0] . $g3s[0];
    my $ng1 = $g0s[1] . $g1s[1] . $g2s[1] . $g3s[1];
    my $ng2 = $g0s[2] . $g1s[2] . $g2s[2] . $g3s[2];
    my $ng3 = $g0s[3] . $g1s[3] . $g2s[3] . $g3s[3];
    my @newGrid = ($ng0, $ng1, $ng2, $ng3); 
    my $retval = &compileTC(@newGrid);
    return $retval;
}

sub diagonalWin {
    my ($s, $testcase) = @_;
    my ($l1, $l2, $l3, $l4) = split(/:/, $testcase);
    if (($l1 =~ /$s.../) and ($l2 =~ /.$s../) and ($l3 =~ /..$s./) and ($l4 =~ /...$s/)) {
        return 1;
    } elsif (($l1 =~ /...$s/) and ($l2 =~ /..$s./) and ($l3 =~ /.$s../) and ($l4 =~ /$s.../)) {
        return 1;
    }
    return 0;
}

sub checkWin {
    my ($symbol, $testcase) = @_;

    if ($testcase =~ /(.*)T(.*)/) {
        $testcase = $1 . $symbol .$2;
    }

    my $transtest = &transpose($testcase);

    my $pattern = $symbol . $symbol . $symbol . $symbol;
    if (($testcase =~ /.*$pattern.*/) or ($transtest =~ /.*$pattern.*/)) {
        return 1;
    } elsif (&diagonalWin($symbol, $testcase)) {
        return 1;
    }
    return 0;
}

sub doneGame {
    my ($game) = @_;
    if ($game =~ /.*\..*/) {
        return 0;
    }
    return 1;
}

sub checkTestCases {
    my (@testcases) = @_;
    my $i=1;
    for my $test (@testcases) {
        my $testStr = "Case #" . $i . ": ";
        #print "Checking:\n", $test, "\n";
        if (&checkWin('X', $test)) {
            print $testStr, "X won\n"; 
        } elsif (&checkWin('O', $test)) {
            print $testStr, "O won\n"; 
        } elsif (&doneGame($test)) {
            print $testStr, "Draw\n"; 
        } else {
            print $testStr, "Game has not completed\n"; 
        }
        $i++;
    }
}

my $file = shift @ARGV; 
my @testcases = &readInput($file);
&checkTestCases(@testcases);



