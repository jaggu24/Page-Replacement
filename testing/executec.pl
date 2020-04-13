#!/usr/bin/perl
use Test::More;
use Test::Deep;

my $o_file = "output.txt";
my $bin = './a.out 3 7 1';
#my $bc = './l1';
#my $bd = './l2';
#my $be = './l3';
# run the C program
$result = `$bin > output.txt`;
#$result = `$bc >> output.txt`;
#$result = `$bd >> output.txt`;
#$result = `$be >> output.txt`;
print $result;
