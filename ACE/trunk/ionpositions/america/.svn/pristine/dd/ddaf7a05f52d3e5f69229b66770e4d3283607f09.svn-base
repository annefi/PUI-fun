#! /usr/bin/perl -I /home/acedata/sw/perl
# read-skeleton.pl -- skeleton for building ACE data reading routines
# Jim Raines, 9Mar2001
#
# NOTE: this is a barebones routine for testing other sw

use libhef;

# name of this program
$thisprog = 'read-skeleton';

# location of level 1 files
$LV1DIR = '/home/acedata/LV1';

# ----------------------------------------------------------------------------
# open input file
# ----------------------------------------------------------------------------
# set input file based on 1st argument
## prototypical filename: 2001039.nc
if (@ARGV >= 1) { # there is an argument, use it
  if ($ARGV[0] =~ /(\d{4})(\d{3})\.nc/) { # argument is a filename
    $infile = $ARGV[0];
    $year = $1;
    $doy = $2;
    $yeardoy = "$year$doy";  # parse out year-day-of-year number
    
  }
  elsif ($ARGV[0] =~ /(\d{4})(\d{3})/) { # filename is a date (yyyydoy)
    $year = $1;
    $doy = $2;
    $yeardoy = $ARGV[0];

    # form input filename
    $infile  = sprintf("%s/%s/%s.nc",$LV1DIR,$year,$yeardoy);
  }
}
else { # no argument give -- exit
  print "$thisprog: yyyymmdd or filename required; ";
  print "use --help option for syntax\n";
  exit(1);
}

# -- actually open input file --
$infile  = sprintf("%s/%s/%s.nc",$LV1DIR,$year,$yeardoy);
$res = libhef::a3opencyclefile($infile);
if( $res ) {
  print "$thisprog -- fatal- cannot open $infile\n";
  exit(1);
}

# ----------------
# open output file
# ----------------
$outfile = sprintf("$thisprog.%s.dat",$yeardoy);
open(OUT, ">".$outfile) or die "$thisprog: cannot open $outfile for writing.";

# --------------------------------------
# loop over cycles 
# --------------------------------------
$ncycle = 0;
while(( $a3rcresult == 0) && ($ncycle < 200)){


  # read cycle
  $a3rcresult = libhef::a3readcycle();
  if( $a3rcresult !=0) {last};

  # expand cycle
  libhef::a3expand();

  # print cycle time
  printf("$thisprog: cycle[%03d] time is %s\n",$ncycle,libhef::a3zrecid());

  # --------------
  # loop over EDBs
  # --------------
  for ($nedb = 2; $nedb < 60; $nedb++){ # starts at 2 as sxd.pl does
    
    # --------------
    # loop over PHAs
    # --------------
    $nphaedb = libhef::a3xnpha($nedb);
    for ($npha = 0; $npha < $nphaedb; $npha++){
      
      # put code that does something here
      
    } # loop over PHAs

  } # loop over EDBs

  close OUT;

  $ncycle++;
} # loop over cycles

print "$thisprog -I- Exiting normally.\n";
exit(0);
