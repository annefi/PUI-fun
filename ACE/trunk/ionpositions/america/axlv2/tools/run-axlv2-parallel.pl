#! /usr/bin/perl
# File:  run-axlv2-parallel.pl
#
# Description:
#   Run a batch of days with axlv2 on a parallel machine, like xena or grendel
#   from CSEM.
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Revision controlled by CVS:
# $Id: run-axlv2-parallel.pl,v 1.1 2005/05/25 15:24:02 jraines Exp $
#
# Major Modification History:
#   25May2005   jmr   initial coding
#

use File::Basename;
use Getopt::Long;

$thisprog = "run-axlv2-parallel";

# ----------------------------------------------------------------------
# parse arguments for start and stop ydoy
# ----------------------------------------------------------------------
# get command line options
GetOptions("help!");

# print revision
print $thisprog.' -I- revision $Id: run-axlv2-parallel.pl,v 1.1 2005/05/25 15:24:02 jraines Exp $ ';
print "\n";

# print usage statement and exit
if ($opt_help){
  print <<EOF;

usage: $thisprog start-yyyydoy stop-yyyydoy [optional args]

  Runs ACE Level II data processor, axlv2, on multiple processors 
  for days start-yyyydoy to stop-yyyydoy (inclusive).

  optional args:
  --help                  prints this message
 
EOF
  exit(0);
}

if (@ARGV == 2){
  $start_ydoy = $ARGV[0];
  $stop_ydoy = $ARGV[1];

  if ($start_ydoy =~ /(\d{4})(\d{3})/){
    $year = $1;
  }
  else {
    die "$thisprog -F- bad argument format; use --help option for syntax";
  }    
}
else {
  die "$thisprog -F- bad arguments; use --help option for syntax";
}

# ----------------------------------------------------------------------
# build lists of nodes and start/stop ydoys
# ----------------------------------------------------------------------
# read list of nodes allocated for this job
$nodefile = $ENV{"PBS_NODEFILE"};
open(IN, "<$nodefile") or 
    die "$thisprog -F- could not open node file ($nodefile)";
while (<IN>){
    chomp $_;
    push @nodes, $_;
}
close(IN);
$NumProc = 2 * @nodes;

# build structure of start and stop ydoys for each cpu
$range = $stop_ydoy - $start_ydoy + 1;
$days_per_proc = int ($range / $NumProc + 0.5); # .5 rounds up
for ($nproc == 0; $nproc < $NumProc; $nproc++){

  # calculate start/stop doy
  $start = $nproc * $days_per_proc + 1;
  $stop = ($nproc+1) * $days_per_proc; 

  # do not wrap around years
  if ($stop > 366) { $stop = 366 };

  # add year to make 7 digit ydoy
  $start += $year*1000;
  $stop += $year*1000;

  push @ranges, {'start' => $start, 'stop' => $stop};
}


# loop over processors to execute jobs
$nproc = 0;
for( $nnode = 0; $nnode < @nodes; $nnode++) {

  # excute jobs on both processors of machine by running 
  # it twice on each machine
  for ($ncpu = 0; $ncpu < 2; $ncpu++){

    $date_str = sprintf("%07d_%07d",$ranges[$nproc]{start},
			$ranges[$nproc]{stop});

    $cmd = "rsh $nodes[$nnode] ~/run-axlv2-many.pl ".$ranges[$nproc]{start};
    $cmd .= " ".$ranges[$nproc]{stop}." >& run-axlv2-${date_str}.out";
    
    # put jobs in background except for last one
    if (! ($nnode == (@nodes - 1) && $ncpu == 1)){
      $cmd .=  ' &';
    }

    mysystem($cmd, 0, 0);

    $nproc++;
  }

}


# ----------------------------------------------------------------------------
# Routine: mysystem
#
# Description:
#   Print command, call system(), and monitor response.  Use severity = -1
#   to just echo command instead of issuing it.
#
# Author(s):  Simon Hefti (sh)
#             Jim Raines (jmr)
#
#
# Major Modification History:
#
#   04Apr2002  jmr  Changed message codes so -E- was displayed if necessary
#   15Aug2002  jmr  Added -1 option to severity. 
# ----------------------------------------------------------------------------
sub mysystem {

  local($cmd)     = $_[0];
  local($testres) = $_[1];
  local($severe)  = $_[2];

  if ($severe != -1){
    print "$thisprog mysystem -I- $cmd\n";
    $res = system($cmd);
  }
  else{
    print "$thisprog mysystem -I- would exec: $cmd\n";
    return(0);
  }

  # print message according to return status
  print "$thisprog mysystem";
  if ($res != $testres){
    print " -E- ";
  }
  else {
    print " -I- ";
  }
  print "answer: $res (expected: $testres)\n";

  if( ($res != $testres) && ($severe == 1) ) {
    exit($res);
  }

  return($res);
}

# enables inclusion in other code by require
1;


