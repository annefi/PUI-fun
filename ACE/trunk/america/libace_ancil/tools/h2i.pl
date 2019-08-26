#! /usr/bin/perl
# libsms-h2i.pl -- copy marked sections from libsms.h into libsms.i
#                  for SWIG/Perl interface to libsms
# Jim Raines, 21Dec99
#
# See libsmsInit for further documentation.
#
# This file is controlled by the Concurent Version System (CVS):
# $Id: h2i.pl,v 1.1.1.1 2003/10/02 17:08:31 jraines Exp $

########################
# initialization stuff #
########################

# define section markers
$begin = "h2i-begin";
$end = "h2i-end";


# other misc. variables
$fCopy = 0;  # flag to indicate when line is within marked section
$thisprog = "h2i";  # name of this program
$fSBlock = 0; # flag indicating if a SWIG block was started
$fDirective = 0; # 1 if line is a SWIG directive

# set infile based from 1st argument (or use default)
if (@ARGV == 2) {
  $Infile = $ARGV[0];
  $Outfile = $ARGV[1];
}
else {
  print "usage: $thisprog prj_header.h prj_header.i\n";
  print "Builds SWIG \.i file from a specially encoded C/C++ \.h file.\n";
}

# open input and output files
open(IN, $Infile ) or die "Cannot open $Infile\n";

# $Outfile = ">".$Outfile;
if ( -e $Outfile ) {
  @CMD = {'mv', $Outfile, $Outfile.".old"};
  printf("%s: moving %s %s\n",$thisprog,$Outfile, $Outfile.".old");
  system tcsh @CMD;
}
open(OUT, ">".$Outfile) or die "Cannot open $Outfile\n";

# put standard stuff in OUT
print OUT <<EOF ;
/* $Outfile -- prototypes for SWIG/Perl interface to libsms */
/* This file generated automatically by $thisprog */

EOF
######################################################
# get to work copying marked sections from IN to OUT #
######################################################
printf("%s: copying marked sections from %s to %s\n",$thisprog,$Infile,
       $Outfile);
while (<IN>) {
  # turn copying on when a begin marker is found
  if ( /$begin/ ) {
    if (/%\{/) { # switch flag to open SWIG block
      $fSBBegin = 1;
    }
    $fCopy = 1;
    next;
  }
  # turn copying off when an end marker is found
  if ( /$end/ ) { 
    if (/%\}/) {   # switch flag to close SWIG block
      $fSBEnd = 1;
    }
    $fCopy = 0;
    print OUT "\n";
    next;
  }

  if ($fSBBegin) { # open SWIG block
    print OUT "%{ /* SWIG block, copied directly to wrapper */\n";
    $fSBBegin = 0;
  }
  elsif ($fSBEnd) {   # close SWIG block
    print OUT "\%} /* end of SWIG block */\n";
    $fSBEnd = 0;
  }

  # copy SWIG directives into file, removing enclosing C comment characters
  if ($fCopy) { # if in a block to copy
    if (/\* (%\w+\s+.+)\*/) { # if it looks /* %word "something" */
      print OUT "$1\n";
      #print "$1\n";
      $fDirective = 1; # turn on flag to prevent copy below
    }
  }
  
  # copy lines to output (most lines are copied by this section)
  if ( $fCopy && !$fDirective){ # copy input to output if copy flag is true
    print OUT "$_";
  }

  # turn flag back off now that copying is done
  if ($fDirective) {
    $fDirective = 0;
  }
}
