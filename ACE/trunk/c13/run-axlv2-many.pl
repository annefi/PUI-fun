#! /usr/bin/perl
#
# File:  run-axlv2-many.pl
#
# Description:
#   Run $client for a group of days
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Revision controlled by CVS:
# $Id: run-axlv2-many.pl,v 1.33 2005/06/27 17:31:00 jraines Exp $
#
# Major Modification History:
#     Oct2003   jmr   adapted from run-template-deluxe.pl
#   03Nov2003   jmr   adapted to match improvements in run-axlv2.sh
#   19Nov2004   jmr   added ability to run multiple discrete periods
#   23Jun2005   jmr   major rework of method; changed to ext. config file
#                     and command line options
#

use Getopt::Long;
use File::Basename;

##############
# perl setup #
##############

# init. some flags
$increment = 1;

$thisprog = "run-axlv2-many";

#######################
# ===> configure <=== #
#######################
# location of axlv2 directory containing executable
# typical: $ENV{ACESW}."/bin"
$AXLV2_EXE_DIR = $ENV{PWD};

# name of axlv2 executable
# typical: "axlv2"
$AXLV2_EXE = "axlv2";

# location of axlv2 IDL files
$AXLV2_IDL_DIR = $ENV{PWD}."/../../axlv2/tools";

# location to store temporary files
# typical: "/tmp"
$TMP = "/tmp";

# copy executable to current working directory by default
$opt_copy = 0;

# ignore non-zero returns from axlv2 by default
$opt_severity = 0;

###########################
# ===> end configure <=== #
###########################
print "$thisprog -I- -START- at " . scalar localtime . "\n";
print "$thisprog -I- Running $AXLV2_EXE_DIR/$AXLV2_EXE \n";

# get command line options
GetOptions("help!","increment=i","interval_file=s","accum=s","config_file=s",
	  "copy!","severity=i");

# print revision
print $thisprog.' -I- revision $Id: run-axlv2-many.pl,v 1.33 2005/06/27 17:31:00 jraines Exp $ ';
print "\n";

# print usage statement and exit
if ($opt_help){
  print <<EOF;

usage: $thisprog <date spec> --accum=X --config_file='axlv2.in' [optional args]

  There are two main ways to specify the date(s) over which to run axlv2 
  with this program:

  ----------------------------------------------------------------------

  1) Run over date range:

  syntax:
  $thisprog start-yyyydoy [stop-yyyydoy] --accum=X --config_file='axlv2.in' [optional args]

  Runs ACE Level II data processor, axlv2, for days start-yyyydoy to
  stop-yyyydoy (inclusive).  Runs for start-yyyydoy only if
  stop-yyyydoy is omitted.  

  Optional argument(s) specific to this mode:
  --increment=N           run in N day increments; default is $increment.

  ----------------------------------------------------------------------

  2) Run with interval file:

  syntax:
  $thisprog --interval_file='intervals.txt' --accum=X --config_file='axlv2.in'[optional args]

  Runs ACE Level II data processor, axlv2, for days specified in the file 
  intervals.txt.  Interval file is list of intervals, one per line.  Each 
  is a pair of yyyydoy separated by whitespace.  The second, stop doy, 
  can be omitted for single day intervals.  Lines starting with '#' 
  are comments.

      e.g.:
      # Some optional comment here
      2000178
      1998057
      2003302 2003310

  ----------------------------------------------------------------------

  Other options in detail:

  --accum=N{m,h,d}        Accumulation time can be specified in N minutes
                          (m), hours (h) or days (d).  When not specified 
                          in minutes, times are converted to minutes and 
                          reduced by 1 minute to remove overlap with next. 
                          Times in minutes should be multiples of 12 min. 
                          cycle time.
      e.g.
      --accum=12m     accumulate for 12 min. per timestep (max. resolution)
      --accum=1h      accumulate for 1 hour (59 min.) per timestep
      --accum=2h      accumulate for 2 hours (119 min.) per timestep
      --accum=1d      accumulate for 1 day (1439 min.) per timestep

  --config_file='file'   Read other axlv2 configuration from this file.

  --copy        Copy axlv2 executable to directory before running.
                This ensures that an entire range is run with the same
                executable.  (Recommended and default.)

  --severity=N  Set to one of the following to control response to 
                spawned axlv2 process:
                -1     echo commands to run spawned axlv2 process but do not run
                 0     continue regardless of axlv2 return value
                 1     stop if axlv2 does not return 0

  --help        prints this message


EOF
  exit(0);
}

# set start and stop yyyydoy from argument list
if (! $opt_interval_file){
  if (@ARGV == 1) { # only one arg. --> run for one day
    $StartYdoy = $ARGV[0];
    $StopYdoy = $ARGV[0];
  }
  elsif (@ARGV > 1) { # two arg. --> run for day range (inclusive)
    $StartYdoy = $ARGV[0];
    $StopYdoy = $ARGV[1];
  }
  else { # not enough args
    die "$thisprog: start and stop dates required; use --help option for syntax\n";
  }
}

# assign accumulation time
# note: -1 removes overlap with next timestep
if ($opt_accum =~ /(\d+)m/){$NumMinToAccum = $1 - 1}
elsif ($opt_accum =~ /(\d+)h/) {$NumMinToAccum = $1*60 - 1}
elsif ($opt_accum =~ /(\d+)d/) {$NumMinToAccum = $1*24*60 - 1}
else {
  die "$thisprog -F- bad accumulation time; use --help for syntax\n";
}
print "$thisprog -I- accumulation time will be $NumMinToAccum minutes\n";

if (! $opt_config_file){die "$thisprog -F- --config_file option required; use --help for syntax"}

if ($opt_increment){
  $increment = $opt_increment;
}

##################################
# read in intervals (optionally) #
##################################
if ($opt_interval_file){
  open(IN,"<$opt_interval_file") or 
    die "$thisprog -F- cannot open $opt_interval_file";

  while (<IN>) {
    
    # only parse lines that do not begin with '#' and are 1-2 7 digit
    # numbers with arbitrary white space between the two
    if ($_ !~ /^#/ && ($_ =~ /\s*\d{7}/ || $_ =~ /\s*\d{7}\s*\d{7}/ )){ 
      @line = split(/\s+/, $_);

      # copy start doy to stop if omitted
      if (@line == 1){
	push @line, $line[0];
      }

      # store into interval hash
      $tmpint = {
		 'Start' => $line[0],
		 'Stop'  => $line[1]
		};

      # store latest interval into interval array
      push @intervals, $tmpint;
    }


  }
}
else {
  # store into interval hash
  $tmpint = {
	     'Start' => $StartYdoy,
	     'Stop'  => $StopYdoy
	    };

  # store latest interval into interval array
  push @intervals, $tmpint;
}


############################
# loop over years and days #
############################
for ($nint = 0; $nint < @intervals; $nint++){

  $StartYdoy = $intervals[$nint]->{"Start"};
  $StopYdoy = $intervals[$nint]->{"Stop"};

  for ($CurYdoy = $StartYdoy; $CurYdoy <= $StopYdoy;){ # increment below
    printf("%s: Working on $CurYdoy...\n",$thisprog);

    $axlv2 = $AXLV2_DIR;

    # set up input file for this day
    # note: the unique file tag (scalar time) allows different
    # users to running the same time period at the same time
    $run_script = $TMP . "/" . "run-axlv2-". $CurYdoy ."." . 
      scalar time .".sh";
    #$run_script = $TMP . "/" . "run-axlv2.".$CurYdoy.".sh";
    $open_result = open(RS, ">$run_script");
    if (! $open_result){
      print "$thisprog -E- could not open $run_script\n";
      goto skip_run;
    }

    if ($opt_copy){ # optionally copy axlv2 exe. to cwd
      if ( $AXLV2_EXE_DIR !~ /^\.$/ ){ # use axlv2 already in cwd
	# note: the subsequent run sometimes fails without the sleep
	$cmd = "cp -v $AXLV2_EXE_DIR/$AXLV2_EXE . ; sleep 1";
	mysystem($cmd,0,0);
      }

      $cmd = "time ./$AXLV2_EXE "; 
    }
    else { # run axlv2 exe. directly from where it lives
      $cmd = "time $AXLV2_EXE_DIR/$AXLV2_EXE ";
    }
    $cmd .= " $CurYdoy $CurYdoy $NumMinToAccum < $opt_config_file";
    mysystem($cmd, 0, $opt_severity);

  skip_run:

    # --- increment day, rolling over year if necessary ---
    $CurYdoy += $increment;

    # roll over year properly (warning: misses day 366 in leap years)
    $CurYdoy =~ /(\d{4})(\d{3})/;  # split out year and day
    $year = $1;
    $doy = $2;
    if ( $doy >= 365 ) {
      $CurYdoy = ($year + 1)*1000 + ($doy - 365);
    }

    close OUTFILE;

    # run associated idl routines
    if (0){
      $idlfile = $thisprog . '.idl';
      open(IDL, ">$idlfile") or print "$thisprog -E- could not open IDL; run manually.\n";
      print IDL <<EOF;
.run $IDLCLIENT
rp_axmr, file=\'$outfile\', data=d
exit
EOF
      close IDL;
      
      $cmd = "idl $idlfile";
      mysystem($cmd,0,0);
    }

  } # loop over days within an interval
} # loop over intervals

print "$thisprog -I- -DONE- at " . scalar localtime . "\n";

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
#  print "$thisprog mysystem";
#  if ($res != $testres){
#    print " -E- ";
#  }
#  else {
#    print " -I- ";
#  }
#  print "answer: $res (expected: $testres)\n";

  if( ($res != $testres) && ($severe == 1) ) {
    exit($res);
  }

  return($res);
}

# enables inclusion in other code by require
1;
