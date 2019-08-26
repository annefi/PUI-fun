#! /usr/bin/perl
# File:  makeShowVersions.pl
#
# Description: 
#
#   Make the showVersions() function by extracting all the RCS Ids
#   from axlv2/swindal source code.
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Revision controlled by CVS:
# $Id: makeShowVersions.pl,v 1.4 2005/01/07 19:50:45 jraines Exp $
#
# Major Modification History:
#   14Dec2004   jmr   initial coding
#

use File::Basename;
use Getopt::Long;

$thisprog = "makeShowVersions";

# ----------------------------------------------------------------------
# 
# ----------------------------------------------------------------------
$outfile = "showVersions.cc";

@EXTENTIONS = (".cc", ".h", ".mak");
# ----------------------------------------------------------------------
# set up files
# ----------------------------------------------------------------------
open(OUT, ">$outfile") or die "$thisprog -F- could not open $outfile";

# ----------------------------------------------------------------------
# get Id lines
# ----------------------------------------------------------------------

foreach $dir (@ARGV){
  open(FIND, "find $dir -type f -print|") or
  die "$thisprog -F- cannot open pipe to find command; check system process list for anomalous situation";

  while (<FIND>){

    # remove trailing newline from file
    $file = $_;
    chomp $file;

    # ------------------------------------------------------------
    # parse filename
    # ------------------------------------------------------------
    ($base, $path, $ext) = fileparse($file, @EXTENTIONS);

    if ($ext) {  # accept only specified file types
      $open_result = open(IN,"<$file");
      if (! $open_result){
	print "$thisprog -W- could not open $file\n";
	next;
      }
    }
    else { # not a specified filetype
      next;
    }

    while (<IN>){
      if (($_ =~ /(\$Id:)/) && (! /rcs_id/) && 
	  ($_ !~ /fprint/) ){
	chomp $_;
	push @id_lines, $_;
      }
    }
    close (IN);

  }

  close(FIND);
}

# ----------------------------------------------------------------------
# build showVersions.cc
# ---------------------------------------------------------------------- 
$now = scalar localtime();

print OUT <<EOF;
// showVersions.cc -- show all versions (RCS IDs) of included routines
// Built by $thisprog on $now
#include <iostream>
#include <string>

//int main(int argc, char *argv[]){

void showVersions(void)\{

  std::string version = "showVersions -I- code built from following versions:\\n";
EOF

foreach $line (@id_lines){
  print OUT "version += \"".$line."\\n\";\n";
}

print OUT <<EOF2;

  std::cout << version << std::endl;

  return;
\}
EOF2

close(OUT);

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
