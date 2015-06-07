use strict;
use warnings;
use File::Find;
use File::Basename;

sub checkUsage () {
    if ((scalar @ARGV) != 4) {
        print "Usage: perl placeCopyrightNotice.pl dir copyR ext comment\n";
        print "     : dirname = Directory to process\n";
        print "     : copyR   = Copyright header to place\n";
        print "     : ext     = Affects files with these extensions (with leading dot)\n";
        die   "     : comment = Type of comment of source file (e.g. //)";
    }
}
sub findFilesInDir {
    my ($dir, $ext) = @_;
    opendir DIR, $dir or die "cannot open dir $dir: $!";
    my @file= readdir DIR;
    closedir DIR;
    my @retfiles;
    my $f;
    foreach $f (@file) {
        if (-d $f) { next;}
	my ($d, $fn, $e) = fileparse($f, qr/\.[^.]*$/);
	if ($e ne $ext) {next;}
	push @retfiles, $f;
    }
    return @retfiles;
}

sub processCopyright {
    my ($cpr, $comment) = @_;
    open CPR, "<$cpr" or die "Cannot open copyright file $cpr: $!";
    my @cprlines;
    while (<CPR>) {
        my $line = $comment . " " . $_;
	push @cprlines, $line;
    }
    return @cprlines;
}

sub addCopyrightIfNeeded {
    my ($dir, $files, $cprlines) = @_;
    foreach my $f (@$files) {
	my $breakout = 0;
	my $file = $dir."\\".$f;
        open my $in,  '<',  "$file"      or die "Can't read old file $file: $!";
        open my $out, '>',  "$file.new"  or die "Can't write new file $file.new: $!";

        print $out @$cprlines;

        while( <$in> ) {
	    if ($_ eq @$cprlines[1]) {
	        close $out; close $in;
		unlink ("$file.new");
		$breakout = 1;
		last;
	    }
            print $out $_;
        }
	if ($breakout) { next; }
        close $out;
        close $in;

	unlink($file);
	rename("$file.new", $file);
    }
}

checkUsage();
my ($dirname, $copyright, $ext, $comment) = @ARGV;
my @files    = findFilesInDir($dirname, $ext);
my @cprlines = processCopyright($copyright, $comment);
addCopyrightIfNeeded($dirname, \@files, \@cprlines);
