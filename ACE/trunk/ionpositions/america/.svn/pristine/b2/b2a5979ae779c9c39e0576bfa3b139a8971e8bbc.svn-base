#!/usr/bin/perl -w
# svsbare.pl -- swindal validation (from) sxd BAREBONES EDITION
# Jim Raines, 24Sep2001

# Based on
# sxd.pl --- Share SWICS/ACE data
# 1998 by Hefti (hef), University of Michigan (hefti@umich.edu)
$rcsid = '$Id: sxd.pl,v 1.5 2001/09/24 15:06:00 jraines Exp $ ';

$thisprog = 'svsbare.pl';

### NOTE ###################################################################
# This version modified for validation of swindal.  Do not use for real sxd.
# JR, 24Sep2001
############################################################################

# Major Revision History
#   Added pav checking for both 22.8 kV and 26.1 kV.  J. Raines, 11May2001

# --- vvv config -------------------------------------------------------------
use libhef;
use Getopt::Long;

@ionnam  = qw(o_6  o_7  o_8  fe8  fe9 );
@amas    =   (16.0,16.0,16.0,56.0,56.0);
@acrg    =   (6.0, 7.0, 8.0, 8.0, 9.0);

$Nionnam = @ionnam;

$XACCT = 12.0;                          # [s] accumulation time

# post-acceleration level to voltage (kV) conversion
# Note: this is a temporary workaround and should be read from cycle
# Note2: data is not processed if the read-out level is not in this table
%lev2kv = (127 => 22.8, 171 => 26.1);

$ncdir = "/home/acedata/LV1";
$sxd_dir = '.';

# --- ^^^ config -------------------------------------------------------------

# ----------------------------------------------------------------------------
# cmd line
# ----------------------------------------------------------------------------

GetOptions("ncdir=s"   => \$ncdir,"sxddir=s"   => \$sxd_dir, 
	   "outfile=s" => \$outfile);

$argc = @ARGV;

if( $argc < 1 ) {
  print STDERR <<EOM;
$thisprog --- Share SWICS/ACE data
1998 by Hefti (hef), University of Michigan (hefti\@umich.edu)
\$Id: svs.pl,v 1.5 2001/09/24 15:06:00 jraines Exp $\

$thisprog [options] yyyyddd
--ncdir=$ncdir         specify alternate LV1 dir.; default shown
--sxddir=$sxd_dir      specify alternate sxd output dir.; default shown
--outfile=filename     specify alt. output file

EOM
  exit(1);
}

$yyyyddd = $ARGV[0];
($yyyy) = ($yyyyddd =~ /(\d\d\d\d)/);

# ----------------------------------------------------------------------------
# open input file
# ----------------------------------------------------------------------------

$fn  = sprintf("%s/%4.4d/%s.nc",$ncdir,$yyyy,$yyyyddd);
$res = libhef::a3opencyclefile($fn);
if( $res ) {
  print "sxd --- cannot open $fn\n";
  exit(1);
}

# ----------------------------------------------------------------------------
# open output file
# ----------------------------------------------------------------------------

if ($outfile){
  $tfn = sprintf("%s/%s",$sxd_dir, $outfile);
}
else {
  $tfn = sprintf("%s/x%s.svsbare",$sxd_dir, $yyyyddd);
}

print "DBG: output file is $tfn\n";
open(FH, ">$tfn") || die "cannot open $tfn: $!\n";

# ----------------------------------------------------------------------------
# write header
# ----------------------------------------------------------------------------

print FH "name: $tfn\n";
$tmp = localtime(time());
print FH "gen.: $tmp\n";
print FH "by:   J. Raines (jraines\@umich.edu)\n";
print FH "ver:  $rcsid\n";
$tmp = libhef::libhefrev();
print FH "lib:  $tmp\n";
print FH "\n";
print FH "\n";
print FH "\n";
print FH "nO6 O7 O8 nFe8 nFe9 nFe10 [counts/sec]\n";

# ----------------------------------------------------------------------------
# loop cycles
# ----------------------------------------------------------------------------

# init variables
$rres = 0;
$ncycle = 0;
@trate = 0.0 x $Nionnam;
$nphatot = 0;
@tottcnt = 0 x $Nionnam;
for ($ion = 0; $ion < $Nionnam; $ion++){
  for ($ie = 0; $ie < 60; $ie++){
    $tottcnt[$ion][$ie] = 0;
  }
}

# build/init Measurement Array (MA)
$MAXTOFCH = 1024;
$MAXESDCH = 256;
for ($ntof = 0; $ntof < $MAXTOFCH; $ntof++){
  for ($nesd = 0; $nesd < $MAXESDCH; $nesd++){
    $MA[$ntof][$nesd] = 0.0;
  }
}

$o7box = 0.0;

while($rres == 0 && $ncycle < 1) {

  # --------------------------------------------------------------------------
  # read and expand
  # --------------------------------------------------------------------------
  $rres = libhef::a3readcycle();
  if( $rres != 0 ) {last};
  $res  = libhef::a3expand();

  printf("%s -I- Cycle[%03d] time is %s\n",$thisprog,$ncycle, 
	 libhef::a3zrecid());
  # --------------------------------------------------------------------------
  # check quality/data presence/nominal mode
  # --------------------------------------------------------------------------
  $res  = libhef::a3cycx_nominal(0);   # paps level (pavlev) checking disabled
  $pavlev = libhef::a3xpavlev();

  # test for valid nominal pav level
  $fPavOk = 0;
  foreach $lev ( keys(%lev2kv) ){

    if ($pavlev == $lev) {
      $fPavOk = 1;
    }

  }
  #print "\n";

  if (! $fPavOk ){
    print "sxd -I- non-nominal pav level; skipping cycle\n";
  }

  if( ($res != 0) || (! $fPavOk) ) {
    die "$thisprog -F- bad PAV or libhef return val.\n";
  }

  $tim = libhef::a3gtime();
  if( $tim <= 852076800 ) {  # before 1-1-1997
    die "$thisprog -F- cycle time is before 1Jan1997; data unreliable\n";
  }


  # ----------------------------------------------------------------------
  # counts in boxes
  # ----------------------------------------------------------------------

  for ($ion = 0; $ion < $Nionnam; $ion++) {

    # --------------------------------------------------------------------
    # get counts
    # --------------------------------------------------------------------

    for ($ie = 2; $ie < 60; $ie++) {

      # ----------------------------------------------------------------
      # forward model
      # ----------------------------------------------------------------

      # Note: use ie - 1 for correct E/q (Tech Note 3)
      $eoq = libhef::a3gxeqdpu_i($ie - 1);
      $pav = $lev2kv{$pavlev};
      $crg = $acrg[$ion];
      $mas = $amas[$ion];
      $moq = $mas / $crg;

      $tmp  = libhef::xfm($eoq,$pav,$mas,$crg);
      $tof  = libhef::aget($tmp,0);
      $stof = libhef::aget($tmp,1);
      $esd  = libhef::aget($tmp,2);
      $sesd = libhef::aget($tmp,3);

      # ----------------------------------------------------------------
      # get counts
      # ----------------------------------------------------------------

      $tcnt  = boxcount();

      #printf("DBG $thisprog --- Step: %2d cnts: %.3e\n",$ie,$tcnt);

      # ................................................................
      # BR weight
      # ................................................................

      $wgt  = libhef::a3xbrwgt($ie,1); # only range 1

      #$tcnt = $tcnt * $wgt;
      ## printf("%3.0f ",$tcnt);

      # ................................................................
      # change into rates, accumulate over EDBs
      # ................................................................

      $trate[$ion] += $tcnt / $XACCT;
      #print "$thisprog -D- ie=$ie trate[$ion]=$trate[$ion]\n";

      # write out per edb rates too
      $tottcnt[$ion][$ie] += $tcnt;
      if ($ionnam[$ion] eq 'o_7') {
	printf FH ("%s nedb=%02d counts=%.2f e/q=%.2f tof=%.2f stof=%.2f esd=%.2f sesd=%.2f\n",
		   $ionnam[$ion],$ie,$tottcnt[$ion][$ie],$eoq,
		   $tof,$stof,$esd,$sesd);
      }

    }				# loop over edbs
  }				#loop over ions

  for($ie = 2; $ie < 60; $ie++) {
    printf( "nphaedb[%d]=%d\n", $ie,libhef::a3xnpha($ie));
    $nphatot += libhef::a3xnpha($ie);
  }

  $ncycle++;
} # loop over cycles

# ----------------------------------------------------------------------------
# write output file
# ----------------------------------------------------------------------------

# header
for($ion = 0; $ion < $Nionnam; $ion++) {
  printf FH ("%s\t",$ionnam[$ion]);
}
print FH "\n";

# rates
for($ion = 0; $ion < $Nionnam; $ion++) {
  printf FH ("%.2f\t",$trate[$ion]);
}
print FH "\n";

# O7+/O6+
print "\n";
printf FH ("O7+/O6+ = %.2f\n", $trate[1]/$trate[0]);

print "nphatot=$nphatot\n";

outputMA();
print "EDB41 o7box = $o7box\n";

# ----------------------------------------------------------------------------
# close output files
# ----------------------------------------------------------------------------

close(FH);

# ----------------------------------------------------------------------------
# close input file
# ----------------------------------------------------------------------------

$res = libhef::a3closecyclefile();
printf("$thisprog --- nc file closed with result %d\n",$res);

# return 0
0;

# ============================================================================
# functions
# ============================================================================

# boxcount -- count all PHAs in box according to forward model
sub boxcount {
  $count = 0;  # count of PHAs in box

  # sigma multipliers to make it easy to manipulate sigmas
  $STOFMUL = 2.0/2.0;
  $SESDMUL = $STOFMUL;

  for ($npha = 0; $npha < libhef::a3xnpha($ie); $npha++){

    $fCount = 0;  # counting flag, set to 1 to count this PHA

    $tptof = libhef::a3gxtof_i($ie,$npha); # this pha tof
    $tpesd = libhef::a3gxesd_i($ie,$npha); # this pha esd

    if ( ( $tptof >= ($tof - ($STOFMUL * $stof)) ) &&
         ( $tptof <= ($tof + ($STOFMUL * $stof)) ) ){
      $fCount = 1;
    }
    else{
      $fCount = 0;
    }

    if ( ( $tpesd >= ($esd - ($SESDMUL * $sesd)) ) &&
	 ( $tpesd <= ($esd + ($SESDMUL * $sesd)) ) ){
      $fCount = 1;
    }
    else{
      $fCount = 0;
    }

    if ($fCount == 1){
      $count += 1;
      $fCount = 0;
    }

    # accumulate into MA
    if (($ie == 41) && ($ionnam[$ion] eq 'o_7')){
      $MA[$tptof][$tpesd] += 1.0;

      # by hand O7+ box count
      if ( ( $tptof >= 340 ) && ( $tptof <= 348 ) ){
        if ( ( $tpesd >= 46 ) && ( $tpesd <= 57 ) ){
	  $o7box += 1.0;
	}
      }

    }

  } # loop over PHAs

  return ($count);
}

# output MA just like TNT matrix from C++ with extra headers (as in axlv2)
sub outputMA {

  # EDB 41 peak
  # ---------------
  $outfile = "svsbare_ma_sl41.dat";
  open(MAO, ">$outfile") or die "$thisprog -F- Cannot open $outfile\n";

  # --- print header ---
  print MAO "ACE/SWICS counts/second for day \n";
  print MAO "TOF_CH ESD_CH\n";

  @region41 = (300,350,1,30);
  for ($j = 0; $j < 4; $j++){
    print MAO "$region41[$j] ";
    $region41[$j] -= 1.0;  # TNT regions are 1 based, this is 0 based
  }
  print MAO "\n";

  # --- print dimensions ---
  printf MAO ("%d %d\n", $region41[1] - $region41[0] + 1,
	      $region41[3] - $region41[2] + 1);

  # --- print matrix region
  for ($ntof = $region41[0]; $ntof <= $region41[1]; $ntof++){
    for ($nesd = $region41[2]; $nesd <= $region41[3]; $nesd++){
      print MAO "$MA[$ntof][$nesd] ";
    }
    print MAO "\n";
  }

  close MAO;

  # EDB 41 O7+ box
  # ---------------
  $outfile = "svsbare_ma_sl41_o7.dat";
  open(MAO, ">$outfile") or die "$thisprog -F- Cannot open $outfile\n";

  # --- print header ---
  print MAO "ACE/SWICS counts/second for day \n";
  print MAO "TOF_CH ESD_CH\n";

  @region41 = (338,350,44,59);
  for ($j = 0; $j < 4; $j++){
    print MAO "$region41[$j] ";
    $region41[$j] -= 1.0;  # TNT regions are 1 based, this is 0 based
  }
  print MAO "\n";

  # --- print dimensions ---
  printf MAO ("%d %d\n", $region41[1] - $region41[0] + 1,
	      $region41[3] - $region41[2] + 1);

  # --- print matrix region
  for ($ntof = $region41[0]; $ntof <= $region41[1]; $ntof++){
    for ($nesd = $region41[2]; $nesd <= $region41[3]; $nesd++){
      print MAO "$MA[$ntof][$nesd] ";
    }
    print MAO "\n";
  }

  close MAO;

  return;
}
