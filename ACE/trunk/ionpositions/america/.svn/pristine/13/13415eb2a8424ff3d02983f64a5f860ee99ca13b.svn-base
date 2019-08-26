#! /usr/bin/perl
# File:  
#
# Description:
#   Converts maxedb file output from axlv2_rates.pro to a C++ array for inserti#   on into ProbRates::calc.  FOR DEBUGGING ONLY.
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Major Modification History:
#   22Aug2003   jmr   initial coding
#

while (<STDIN>){
  if (! /^\#/) {
    @line = split(/\s+/,$_);

#  foreach $f ( @line ){
#    print "$f ";
#  }
#  print "\n";

#  for ($i = 0; $i < @line; $i++){
#    print "line[$i]=$line[$i] ";
#  }
#  print "\n";

    printf("maxedb[%d]=%d;    // max. edb for %s\n", $line[0], $line[2],
	   $line[1]);
  }
}
