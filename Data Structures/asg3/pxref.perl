#!/usr/bin/perl
# $Id: pxref.perl,v 1.1 2011-01-28 19:57:52-08 - - $
use strict;
use warnings;

$0 =~ s|^(.*/)?([^/]+)/*$|$2|;
my $status = 0;
END {exit $status}
$SIG{'__WARN__'} = sub {print STDERR "$0: @_"; $status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my $sep = "\n" . ":" x 65 . "\n";
for my $filename (@ARGV ? @ARGV : "-") {
   open my $file, "<$filename" or do {warn "$filename: $!\n"; next};
   print "$sep$filename$sep\n";
   my %xref;
   while (defined (my $line = <$file>)) {
      m/^\d*$/ or push @{$xref{$_}}, $. for split m/\W+/, $line
   }
   close $file;
   print "$_ @{$xref{$_}}\n" for sort keys %xref;
}


