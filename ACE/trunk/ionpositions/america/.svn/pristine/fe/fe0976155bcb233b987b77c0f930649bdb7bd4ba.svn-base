#! /usr/bin/perl
# File:  axlv2_cat.pl
#
# Description:
#   Concatentate axlv2 output files into one file per type.
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Revision controlled by CVS:
# $Id: axlv2_cat.pl,v 1.5 2005/06/08 18:43:46 jraines Exp $
#
# Major Modification History:
#   10May2005   jmr   initial coding
#

use File::Basename;
use Getopt::Long;

$thisprog = "axlv2_cat";

# ----------------------------------------------------------------------
# ===> configure <===
# ----------------------------------------------------------------------
@rate_types = ("br", "sr", "pr");
@raw_types = ("distfunc", "nvt");
@deliv_types = ("deliv_nvt", "deliv_elem", "deliv_qratio", "deliv_elem_la",
	       "deliv_C_qdist", "deliv_Fe_qdist", "deliv_Mg_qdist",
	       "deliv_Ne_qdist", "deliv_O_qdist", "deliv_Si_qdist");

# set file types to be included by default to 1
$opt_deliv = 1;
$opt_raw   = 0;

# ----------------------------------------------------------------------
# config. processing
# ----------------------------------------------------------------------
$allowed_types = join(' ',@rate_types) . " " . join(' ',@raw_types) 
  . " " . join(' ',@deliv_types);
# ----------------------------------------------------------------------
# get command line options
# ----------------------------------------------------------------------
GetOptions("help!","dir=s","stdin!","rate!","raw!","deliv!","all!",
	   "maxdepth=i", "verbose!", "type=s");

# print revision
print $thisprog.' -I- revision $Id: axlv2_cat.pl,v 1.5 2005/06/08 18:43:46 jraines Exp $ ';
print "\n";

# print usage statement and exit
if ($opt_help){
  print <<EOF;

usage: $thisprog [optional args]

  Concatenates data files from the ACE Level II data processor, axlv2, into
  one file per type in current working directory.

  Caveat:  This uses 'find' so be careful and use --maxdepth=0 if necessary.

  optional args:
  --help                  prints this message
  --dir='01-001-02/01'    look for files in dir and descendents
  --maxdepth=N            only descend N levels from dir, default is no limit
                          hint: use maxdepth=0 for files in dir only
  --rate                  include rate file types
  --raw                   include raw file types (nvt and distfunc)
  --deliv                 include deliverable file types (default)
  --all                   include all file types
  --verbose               add more verbose output, useful for debugging
  --type='nvt'            process specified type only (allowed listed below)

  allowed types: $allowed_types


EOF
  exit(0);
}

# assemble file list
if ($opt_deliv || $opt_all){ push @file_types, @deliv_types }
if ($opt_raw || $opt_all){ push @file_types, @raw_types }
if ($opt_rates || $opt_all){ push @file_types, @rate_types }
# if type is specified, only do that one
if ($opt_type) {@file_types = (); push @file_types, $opt_type}

# check for trailing / on dir (if specified)
if ($opt_dir){
  if ($opt_dir !~ /\/$/) { $opt_dir .= '/' }
}

# format option for passing to 'find'
if ($opt_maxdepth) {$opt_maxdepth = "-maxdepth $opt_maxdepth"}
# ----------------------------------------------------------------------
## get date range from NVT files
# ----------------------------------------------------------------------
#  @nvt_files = glob $opt_dir.'axlv2_nvt*.dat';
@nvt_files = get_files("nvt");

if (scalar @nvt_files <= 1) {
  die "$thisprog -F- there does not appear to be a good set of axlv2 output files in this directory";
}

$start_ydoy = 9999999;
$stop_ydoy = 0;
foreach $file (@nvt_files){
  if ($file =~ /axlv2_nvt_(\d{7})\.dat/){
    $ydoy = $1;

    push @ydoys, $ydoy;

    # check for extremes
    if ($ydoy < $start_ydoy) {$start_ydoy = $ydoy}
    if ($ydoy > $stop_ydoy) {$stop_ydoy = $ydoy}
  }
}

# ----------------------------------------------------------------------
# do the concatenation of each file type
# ----------------------------------------------------------------------
print "$thisprog -I- processing files from $start_ydoy to $stop_ydoy\n";

foreach $type (@file_types){
  $outfile = "axlv2_${type}_${start_ydoy}_${stop_ydoy}.dat";
  $status = open(OUT, ">$outfile");
  if (! $status) {
    print "$thisprog -W- cannot open $outfile for writing";
    print "+ skipping this type\n";
    next;
  }

  print "$thisprog -I- concatenating axlv2_${type}\*.dat into $outfile\n";

  # find all files of this type
  @files = get_files($type);

  foreach $file (@files){
    if ($opt_verbose){print "$thisprog -I- working on $file\n";}

    $status = open(IN, "<$file");
    if (! $status) {
      print "$thisprog -W- cannot open $file for reading\n";
      print "+ skipping this type\n";
      last;
    }

    # copy in to out
    while (<IN>){print OUT $_}

    close(IN);
  }

  close(OUT);

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

# ----------------------------------------------------------------------------
# Routine: get_files
#
# Description:
#   Uses find to find all files of specified type.
#
# Method:
#   Uses $opt_* variables from main program.  All others are local.
#
# Author(s):  Jim Raines (jmr)
#
#
# Major Modification History:
#
#   01Jun2005   jmr   initial coding
# ----------------------------------------------------------------------------
sub get_files($){
  my $type = $_[0];
  my @files;

  open(FILES, "find $opt_dir $opt_maxdepth -name \'axlv2_${type}_[0-9][0-9][0-9][0-9][0-9][0-9][0-9].dat\' -print |") or
    die "$thisprog -F- could not open pipe to find";
  while(<FILES>){
    chomp $_;
    push @files, $_;
  }
  close(FILES);
  
  @files = sort @files;

  return @files;
}
