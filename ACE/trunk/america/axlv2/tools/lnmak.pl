#! /usr/bin/perl
# File:  lnmak.pl
#
# Description:
#   Link .mak files given on command line to 'Makefile' in that directory.
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Major Modification History:
#   13Aug2003   jmr   initial coding
#

use File::Basename;

foreach $item (@ARGV){
  ($name,$path,$suffix) = fileparse($item,'.mak');
  $cmd = sprintf("ln -s %s %sMakefile\n",$item,$path);
  mysystem($cmd,0,0);
}

# ----------------------------------------------------------------------------
# mysystem --- call system(), monitor response.  From Simon Hefti
# ----------------------------------------------------------------------------
sub mysystem {

  local($cmd)     = $_[0];
  local($testres) = $_[1];
  local($severe)  = $_[2];

  print "DBG - mysystem - $cmd\n";

  $res = system($cmd);

  print "DBG - mysystem - answer: $res (expected: $testres)\n";
  if( ($res != $testres) && ($severe == 1) ) {
    exit(1);
  }

  0;
}

# enables inclusion in other code by require
1;
