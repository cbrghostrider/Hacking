# -------------------------------------------------------------------------------------
#         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
#                       For email, run on linux (perl v5.8.5):
#   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
# -------------------------------------------------------------------------------------
use strict;
use warnings;

my $languages = ":C:CPP:JAVA:PYTHON:PERL:PHP:RUBY:CSHARP:HASKELL:CLOJURE:BASH:SCALA:ERLANG:CLISP:LUA:BRAINFUCK:JAVASCRIPT:GO:D:OCAML:R:PASCAL:SBCL:DART:GROOVY:OBJECTIVEC:";

my $num = <STDIN>; chomp $num;
for (my $i=0; $i<$num; $i++) {
    my $line = <STDIN>; chomp $line;
    if ($line =~ /^[0-9]{5}\s+([A-Za-z]+)\s*$/) {
        my $lang = uc $1;
        if ($languages =~ /:$lang:/) {
            print "VALID\n";
            next;
        }
    }
    print "INVALID\n";
}