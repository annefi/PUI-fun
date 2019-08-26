#!/usr/bin/perl -w
# svs.pl -- swindal validation (from) sxd
# Jim Raines, 24Sep2001

# Based on
# sxd.pl --- Share SWICS/ACE data
# 1998 by Hefti (hef), University of Michigan (hefti@umich.edu)
$rcsid = '$Id: sxd.pl,v 1.5 2001/09/24 15:06:00 jraines Exp $ ';

### NOTE ###################################################################
# This version modified for validation of swindal.  Do not use for real sxd.
# JR, 24Sep2001
############################################################################

# Major Revision History
#   Added pav checking for both 22.8 kV and 26.1 kV.  J. Raines, 11May2001

# --- vvv config -------------------------------------------------------------
use libhef;
use Getopt::Long;

@ionnam  = qw(c_5  c_6  o_6  o_7  o_8  fe3  fe4  fe5  fe6  fe7  fe8  fe9  
              fea  feb  fec  fed  fee  fef  feg);
@amas    =   (12.0,12.0,16.0,16.0,16.0,56.0,56.0,56.0,56.0,56.0,56.0,56.0,
	      56.0,56.0,56.0,56.0,56.0,56.0,56.0);
@acrg    =   ( 5.0, 6.0, 6.0, 7.0, 8.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
	      10.0,11.0,12.0,13.0,14.0,15.0,16.0);
@afmt    = qw(%.2f %.2f %.2f %.2f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f
              %.3f %.3f %.3f %.3f %.3f %.3f %.3f);

$Nionnam = @ionnam;

#$XGEOM = 1.85e-2;                       # [cm^2] geometrical factor
$XGEOM = 1.0;
$XWEOQ = 0.043;                         # width of E/q window
$XACCT = 12.0;                          # [s] accumulation time
$MELEM = 1.6606e-27;                    # [kg]
$QELEM = 1.6022e-19;                    # [Cb]

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
svs.pl --- Share SWICS/ACE data
1998 by Hefti (hef), University of Michigan (hefti\@umich.edu)
\$Id: svs.pl,v 1.5 2001/09/24 15:06:00 jraines Exp $\

svs.pl [options] yyyyddd
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
  $tfn = sprintf("%s/x%s.svs",$sxd_dir, $yyyyddd);
}

print "DBG: output file is $tfn\n";
open(FH, ">$tfn") || die "cannot open $tfn: $!\n";

# ----------------------------------------------------------------------------
# write header
# ----------------------------------------------------------------------------

print FH "name: $tfn\n";
$tmp = localtime(time());
print FH "gen.: $tmp\n";
print FH "by:   Hefti (hefti\@umich.edu)\n";
print FH "ver:  $rcsid\n";
$tmp = libhef::libhefrev();
print FH "lib:  $tmp\n";
print FH "\n";
print FH "\n";
print FH "\n";
print FH "tim     nH    vH     vthH   vO6    vthO6  nC5 C6 nO6 O7 O8 nFe3 ... nFe16\n";
print FH "[sec70] [a.u] [km/s] [km/s] [km/s] [km/s] [a.u.]\n";

# ----------------------------------------------------------------------------
# get memory
# ----------------------------------------------------------------------------
$mv = libhef::dvec_get(58);             # for moment: speed
$mc = libhef::dvec_get(58);             # for moment: counts

# ----------------------------------------------------------------------------
# loop cycles
# ----------------------------------------------------------------------------

$rres = 0;
$ic   = 0;
while($rres == 0) {

  # --------------------------------------------------------------------------
  # read and expand
  # --------------------------------------------------------------------------
  $rres = libhef::a3readcycle();
  if( $rres != 0 ) {last};
  $res  = libhef::a3expand();

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

      if ($ic == 1) {
	print "sxd -D- pavlev=$pavlev ";
	printf ("pav=%f valid\n",$lev2kv{$pavlev});
      }

    }

  }
  #print "\n";

  if (! $fPavOk ){
    print "sxd -I- non-nominal pav level; skipping cycle\n";
  }

  if( $res == 0 && $fPavOk ) {

    $tim = libhef::a3gtime();
    if( $tim > 852076800 ) {  # after 1-1-1997

      printf FH ("%.0f\t",$tim);

      # ----------------------------------------------------------------------
      # kinetic properties from AUX channel (protons)
      # ----------------------------------------------------------------------

      $tmp  = libhef::a3auxspd();
      $vH = libhef::aget($tmp,1);
      printf FH ("%.0f\t", libhef::aget($tmp,0));
      printf FH ("%6.1f\t",$vH);
      printf FH ("%6.2f\t",libhef::aget($tmp,2));

      # ----------------------------------------------------------------------
      # v(O6) with moments
      # ----------------------------------------------------------------------

      @kpt = kpmomment(16.0,6.0,$vH);

      printf FH ("%6.1f\t",$kpt[0]);
      printf FH ("%6.2f\t",$kpt[1]);

      # ----------------------------------------------------------------------
      # counts in ellipses
      # ----------------------------------------------------------------------

      for($ion = 0; $ion < $Nionnam; $ion++) {

	## print "$ionnam[$ion] --- cyc $ic\n";
	
	# --------------------------------------------------------------------
	# get counts
	# --------------------------------------------------------------------

	$den  = 0.0;
	$nmom = 0.0;

	for($ie = 2; $ie < 60; $ie++) {

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

	  # ................................................................
	  # O8+ : only half an ellipse
	  # ................................................................

	  @tel = ($tof,$stof,$stof,$esd,$sesd,$sesd);

	  if( ($mas == 16.0) && ($crg == 8.0) ) {
	    @tel = ($tof,$stof,$stof,$esd,0.01,$sesd);
	  }

	  # ----------------------------------------------------------------
	  # get counts
	  # ----------------------------------------------------------------

	  # Flags: filter (1)
	  if (1){
	    $tcnt  = boxcount();
	  }
	  else{
	    $tcnt  = libhef::a3xelletm($ie,1,$vH,(1),@tel);
	  }

	  #printf("DBG svs.pl --- Step: %2d cnts: %.3e\n",$ie,$tcnt);
	  # ................................................................
	  # O8+ : account for half ellipse
	  # ................................................................

	  if( ($mas == 16.0) && ($crg == 8.0) ) {
	    $tcnt *= 2.0;
	  }

	  ## printf("%2d %3.0f ",$ie,$tcnt);

	  # ................................................................
	  # BR weight
	  # ................................................................

	  $wgt  = libhef::a3xbrwgt($ie,1);  # only range 1

	  #$tcnt = $tcnt * $wgt;
	  ## printf("%3.0f ",$tcnt);

	  # ................................................................
	  # dj
	  # ................................................................

	  $tcnt = $tcnt / $XGEOM / $XACCT;
	  
	  # ----------------------------------------------------------------
	  # efficiency for O and Fe
	  # ----------------------------------------------------------------

	  if( ($mas == 16.0) || ($mas == 56.0) ) {

	    $etot = $crg * ($eoq + $pav);
	    $eff  = libhef::xeffv1($etot,$mas);

	    # not using eff. for swindal validation, JMR
	    #$tcnt /= $eff;   
	    ## printf("%3.0f ",$tcnt);
	  }

	  # ----------------------------------------------------------------
	  # phase-space density f
	  # ----------------------------------------------------------------

	  $tcnt = $tcnt * 0.537 * ($moq * $moq) / $eoq / ($eoq * $XWEOQ) /
	    1.0e3;
	  ## printf("%5.2f ",$tcnt);
	  ## printf("%.3f %.3f\n",$eoq,$eoq * $XWEOQ);

	  # ----------------------------------------------------------------
	  # v_i
	  # ----------------------------------------------------------------

	  $v_i  = sqrt(2.0e3 * $eoq / $moq / $MELEM * $QELEM) / 1.0e3;

	  # ----------------------------------------------------------------
	  # sum up density moment
	  # ----------------------------------------------------------------

	  $nmom += $tcnt * $v_i;
	}

	# ------------------------------------------------------------------
	# density
	# ------------------------------------------------------------------

	#                          E/q stepping width   arbitrary norm
	$den = ($vH * $vH) / 0.5 * 0.0358969 * $nmom  / 1.0e6;
	#                    duty

	$tmp = $afmt[$ion];
	printf FH ("$tmp\t",$den);
      }
      printf FH ("\n");
      $ic++;
    }
  }
}

# ----------------------------------------------------------------------------
# close output files
# ----------------------------------------------------------------------------

close(FH);

# ----------------------------------------------------------------------------
# close input file
# ----------------------------------------------------------------------------

$res = libhef::a3closecyclefile();
printf("svs.pl --- nc file closed with result %d\n",$res);

# ----------------------------------------------------------------------------
# free memory
# ----------------------------------------------------------------------------
libhef::dvec_free($mc);
libhef::dvec_free($mv);

0;

# ============================================================================
# functions
# ============================================================================

# ----------------------------------------------------------------------------
# kpmoment --- kinetic properties from moments
# + The routine assumes there is memory allocated for $mv and $mc
# ----------------------------------------------------------------------------
sub kpmomment {

  local($mas,$crg,$vH) = ($_[0],$_[1],$_[2]);
  local($moq,$eoq,$tmp,$tof,$stof,$esd,$sesd,@tel,$tcnt,$wgt,$vvv,$vth);
  local($ie);

  # print "DBG kpmoment --- $mas $crg\n";

  libhef::aeset($mv,0,58,0.0);
  libhef::aeset($mc,0,58,0.0);

  for($ie = 2; $ie < 60; $ie++) {

#    printf("DBG kpmoment --- %6.2f %6.2f\n",
#	   libhef::a3gxeqdpu_i($ie - 1),
#	   libhef::a3gxeqdpu_i($ie - 2));

    $eoq  = (libhef::a3gxeqdpu_i($ie - 1) +
             libhef::a3gxeqdpu_i($ie - 2)) / 2.0;
    $tmp  = libhef::xfm($eoq,22.8,$mas,$crg);
    $moq  = $mas / $crg;

    $tof  = libhef::aget($tmp,0);
    $stof = libhef::aget($tmp,1);
    $esd  = libhef::aget($tmp,2);
    $sesd = libhef::aget($tmp,3);

    @tel  = ($tof,$stof,$stof,$esd,$sesd,$sesd);

    $tcnt = 0.0;

    $tcnt = libhef::a3xelletm($ie,1,$vH,(1),@tel);
    $wgt  = libhef::a3xbrwgt($ie,1);  # only range 1
    $tcnt = $tcnt * $wgt;
	
    $tmp  = sqrt(2.0e3 * $eoq / $moq / $MELEM * $QELEM) / 1.0e3;

    # --- carefull ---

    libhef::aset($mv,$ie-2,$tmp);
    libhef::aset($mc,$ie-2,$tcnt);
  }

  $vvv  = libhef::dmom1($mv,$mc,58);
  $tmp  = libhef::dmomN($mv,$mc,58,2.0);
  $tmp  = $tmp - $vvv * $vvv;
  if( $tmp > 0.0 ) {
    $vth  = sqrt($tmp);
  } else {
    $vth = -1.0;
  }

  # printf("DBG kpmoment --- v  = %5.1f, vth = %5.2f\n",$vvv,$vth);

  #return
  ($vvv,$vth);
}

# boxcount -- count all PHAs in box according to forward model
sub boxcount {
  $count = 0;  # count of PHAs in box
  $STOFMUL = 2.0/2.0;
  $SESDMUL = $STOFMUL;

  for ($npha = 0; $npha < libhef::a3xnpha($ie); $npha++){
    $fCount = 0;  # counting flag, set to 1 to count this PHA

    $tptof = libhef::a3gxtof_i($ie,$npha); # this pha tof
    $tpesd = libhef::a3gxesd_i($ie,$npha); # this pha esd

    if ( $tptof <= ($tof + sqrt($STOFMUL * $stof)) ||
         $tptof >= ($tof - sqrt($STOFMUL * $stof)) ){
      $fCount = 1;
    }
    else{
      $fCount = 0;
    }

    if ( $tpesd <= ($esd + sqrt($SESDMUL * $sesd)) ||
	 $tpesd >= ($esd - sqrt($SESDMUL * $sesd)) ){
      $fCount = 1;
    }
    else{
      $fCount = 0;
    }

    if ($fCount == 1){
      $count += 1;
    }

  }

  return ($count);
}
