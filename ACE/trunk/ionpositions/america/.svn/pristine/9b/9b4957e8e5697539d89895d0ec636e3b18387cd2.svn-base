#! /usr/bin/perl
#
# File:  run-axlv2-shock-many.pl
#
# Description:
#   Run $client for a group of days
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Revision controlled by CVS:
# $Id: run-axlv2-shock-many.pl,v 1.2 2005/02/21 21:46:33 jraines Exp $
#
# Major Modification History:
#     Oct2003   jmr   adapted from run-template-deluxe.pl
#   03Nov2003   jmr   adapted to match improvements in run-axlv2.sh
#   19Nov2004   jmr   added ability to run multiple discrete periods
#   18Feb2005   jmr   adapted to run axlv2_shock and do doyfr-centered calc.
#

use Getopt::Long;
use File::Basename;
use libhef;

##############
# perl setup #
##############

# init. some flags
$increment = 1;

$thisprog = "run-axlv2--shock-many";

# turn off buffered output
$| = 1;
#######################
# ===> configure <=== #
#######################
# location of axlv2 directory containing executable
# typical: $ENV{ACESW}."/bin"
#$AXLV2_EXE_DIR = $ENV{ACESW}."/bin";
$AXLV2_EXE_DIR = "/home/jraines/ace/axlv2";

# name of axlv2 executable
# typical: "axlv2"
$AXLV2_EXE = "axlv2_shock";

# name of IDL client to run
# typical: ''  (no client)
$IDLCLIENT  = '';

# location to store temporary files
# typical: "/tmp"
$TMP = "/tmp";

# location of level 1 files
$LV1DIR = $ENV{ACELV1};

###########################
# ===> end configure <=== #
###########################

# get command line options
GetOptions("help!","interval_file=s");

# print revision
print $thisprog.' -I- revision $Id: run-axlv2-shock-many.pl,v 1.2 2005/02/21 21:46:33 jraines Exp $ ';
print "\n";

# print usage statement and exit
if ($opt_help){
  print <<EOF;

usage: $thisprog --interval_file=shock_times.txt

  Runs special shock version of ACE Level II data processor, axlv2_shock, 
  for intervals contained in the interval_file.

  required args:
  --interval_file="file"  read intervals out 'file'

      Interval file is list of intervals, one per line.  Lines starting 
      with '#' are comments.  The first two values are a pair of
      yyyydoy separated by whitespace representing the start and stop ydoy of 
      the run.  The third value is the shock time, about which the run is to 
      be centered.  (The cycle containing this time is skipped.)  The fourth
      value is the number of cycles to run before and after (total run is 
      2x this value) the shock center.for single day intervals.  
      e.g.:

      # Some optional comment here
      2001094 2001094 2001094.5976 10
      2003306 2003307 2003306.95 10

  optional args:
  --help                  prints this message

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
    print "$thisprog: start and stop dates required; use --help option for syntax\n";
    exit(1);
  }
}

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
		 'Start'   => $line[0],
		 'Stop'    => $line[1],
		 'Center'  => $line[2],
		 'Bracket' => $line[3]
		};

      # store latest interval into interval array
      push @intervals, $tmpint;
    }


  }
}
else {
  print "$thisprog -F- must supply interval file.  See --help for syntax.\n";
  exit(1);
}

############################
# loop over years and days #
############################
for ($nint = 0; $nint < @intervals; $nint++){

  $StartYdoy = $intervals[$nint]->{"Start"};
  $StopYdoy = $intervals[$nint]->{"Stop"};

  printf("%s: Working on $StartYdoy..$StopYdoy\n",$thisprog);

  $axlv2 = $AXLV2_DIR;

  # set up input file for this day
  # note: the unique file tag (scalar time) allows different
  # users to running the same time period at the same time
  $run_script = $TMP . "/" . "run-axlv2-". $StartYdoy ."." . 
    scalar time .".sh";
  #$run_script = $TMP . "/" . "run-axlv2.".$StartYdoy.".sh";
  $open_result = open(RS, ">$run_script");
  if (! $open_result){
    print "$thisprog -E- could not open $run_script\n";
    goto skip_run;
  }

  # figure out start, stop and skip scet
  $CenterYdoyfr = $intervals[$nint]->{"Center"};
  $NumCycleBracket = $intervals[$nint]->{"Bracket"};
  ($StartScet,$StopScet,$SkipScet) = 
    findRunRange($CenterYdoyfr, $NumCycleBracket);
  print "$thisprog -I- running from scet=($StartScet,$StopScet), skipping $SkipScet\n";

#    $StartScet = 986386707;
#    $StopScet = 986401110;
#    $SkipScet = 986393908;

    print RS <<PERLEOF;
#!/bin/bash

tag=$StartYdoy      # add text here to tag plots

cat > axlv2.in <<EOF
3.5                # Enter input sequence version number: 
0		   # Load Measurement Array (true or false)? 
0		   # Save Measurement Array when finished (true or false)? 
7                  # Enter PHA filter flag:
0.3                # Enter velocity filter value (0.0 for none):
2                  # Use which FM (-1..4, 2 is standard):
0		   # Output E-T slices?
0		   # Output MMQ data for MA?
1.0                # Enter MMQ data mass *lower* limit: 
100.0              # Enter MMQ data mass *upper* limit: 
1.0                # Enter MMQ data m/q *lower* limit: 
20.0               # Enter MMQ data m/q *upper* limit: 
axlv2		   # Enter filename base (for all files): 
${StartYdoy}	   # Enter start date (yyyydoy): 
${StopYdoy}	   # Enter stop date (yyyydoy): 
${StartScet}       # Enter start SCET (ss1970):
${StopScet}        # Enter stop SCET (ss1970):
${SkipScet}        # Enter SCET (ss1970) to skip: 
1		   # Enter number of cycles to load into RAM at once:
5		   # Enter number of cycles to accum. per timestep (-1=>inf):
1		   # Enter global debugging level (0-5): 
/shrg1/ace/LV1     # Enter directory containing LV1 data
1		   # Do boxrates calculation? 
1		   # Do spillrates calculation?
0.01               # SpillRates cutoff:
5                  # SpillRates max. iterations:
1		   # Do probrates calculation? 
0                  # Output P slices?
0		   # Load probrates? 
0		   # Save probrates? 
3.0                # Enter PR gauss cutoff:
1                  # Enter state of first high-state Fe:
1.0                # Enter PR gauss cutoff for high-state Fe:
1      	           # Do distribution function calculations? 
EOF

# -------------------------------------------------------------------
# Run axlv2
# -------------------------------------------------------------------
# note: set dir to '.', e.g. amlv2_exe_dir=., to avoid use executable
# already resident in current working directory
# -------------------------------------------------------------------
if [ $AXLV2_EXE_DIR != '.' ]; then cp -v $AXLV2_EXE_DIR/$AXLV2_EXE .; fi
sleep 1
time ./$AXLV2_EXE < axlv2.in
#rm -f ./axlv2

# -------------------------------------------------------------------
# Build IDL input files
# -------------------------------------------------------------------
ln -fs $axlv2/tools/axlv2_rates_template.save ./axlv2_rates_template.save
cat > axlv2_rates.idl << EOF
.run $axlv2/tools/axlv2_rates.pro

file='axlv2_br_${CurYdoy}.dat'
if (file_exists(file)) then $
  axlv2_rates, file=file,rate_type='Box',data=dbr, tag='ydoy=${CurYdoy}'

file='axlv2_sr_${CurYdoy}.dat'
if (file_exists(file)) then $
  axlv2_rates, file=file,rate_type='Spill', data=dsr, tag='ydoy=${CurYdoy}'

file='axlv2_pr_${CurYdoy}.dat'
if (file_exists(file)) then $
  axlv2_rates, file=file, rate_type='Prob',data=dpr, tag='ydoy=${CurYdoy}'
EOF

ln -fs $axlv2/tools/fmcomp_template.save ./fmcomp_template.save
cat > fmcomp.idl << EOF
.run $axlv2/tools/read_fmc.pro
.run $axlv2/tools/read_ets.pro
.run $axlv2/tools/plot_ets.pro
.run $axlv2/tools/fmcomp.pro   
file='axlv2_fmcomp.dat'
if (file_exists(file)) then $
  fmcomp, fmcfile=file, etsfile='axlv2_et_slices.dat',\$
        tag='ydoy=${CurYdoy}',fmcdata=fmc
EOF

cat > plot_p_slices.idl <<EOF
.run $axlv2/tools/read_slices.pro
.run $axlv2/tools/read_fmc.pro
.run $axlv2/tools/plot_ets.pro
.run $axlv2/tools/plot_p_slices.pro
!p.multi = [0,2,2]
file='axlv2_p_slices.dat'
if (file_exists(file)) then $
  plot_p_slices, file=file, slices=s, tag='ydoy=${CurYdoy}'
EOF

# using the pipe removes the need for an 'exit' which is useful when
# re-running the IDl processing
#cat axlv2_rates.idl fmcomp.idl plot_p_slices.idl | idl
cat axlv2_rates.idl | idl

PERLEOF
    close(RS);

    # make script executable
    $cmd = "chmod a+x $run_script";
    mysystem($cmd,0,0);

    # run script
    $cmd = "$run_script";
    mysystem($cmd,0,0);

    $cmd = "rm $run_script";
    #mysystem($cmd, 0,0);
  
  skip_run:

    close OUTFILE;

} # loop over intervals


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

# ----------------------------------------------------------------------------
# findRunRange -- scan file to find cycles to include based on given center
# ----------------------------------------------------------------------------
#     findRunRange($CenterYdoyfr, $NumCycleBracket);
sub findRunRange($$){
  local($center_ydoyfr) = $_[0];
  local($num_bracket)   = $_[1];

  local($thisprog) = "findRunRange";

  my @scets;

  print "$thisprog -I- pre-scanning cycle times to find one to skip\n";

  # -- actually open input file --
  if ($center_ydoyfr =~ /(\d{4})(\d{3})\./) {
    $year = $1;
    $doy = $2;
    $yeardoy = "$year$doy";
  }

  $infile  = sprintf("%s/%s/%s.nc",$LV1DIR,$year,$yeardoy);
  $res = libhef::a3opencyclefile($infile);
  if( $res ) {
    print "$thisprog -- fatal- cannot open $infile\n";
    exit(1);
  }

  # convert center_ydoyfr to ss1970
  
  $tc_str = `/shrg1/ace/sw/bin/tc $year $doy`;
  chomp $tc_str;
  @tc = split(/\s+/,$tc_str);
  $seconds = $center_ydoyfr - $year*1000 - $doy;
  $seconds = $seconds*86400.;
  $center_scet = $tc[0] + $seconds;
  #$center_scet = 986393908;

  $ncycle = 0;
  $a3rcresult = 0;
  $skip_cycle = 0;
  while($a3rcresult == 0){

    # read cycle
    $a3rcresult = libhef::a3readcycle();
    if( $a3rcresult !=0) {last};

    # expand cycle
    libhef::a3expand();

    # print cycle time
    printf("$thisprog: cycle[%03d] time is %s\n",$ncycle,libhef::a3zrecid());

    $scet = libhef::a3gtime();
    push @scets, $scet;

    if ($skip_cycle == 0 && $scet > $center_scet){
      $skip_cycle = $ncycle - 1;
      print "+++++ just passed shock center -- will skip $skip_cycle +++++\n";
    }

    $ncycle++;
  } # loop over cycles

  libhef::a3closecyclefile();

  # determine start and stop scet
  $SkipScet = $scets[$skip_cycle];
  $StartScet = $scets[$skip_cycle - $num_bracket];
  $StopScet = $scets[$skip_cycle + $num_bracket];
  # + 1 accounts for the skipped cycle
  # - 1 shifts to last scet to keep (req'd by axlv2_shock logic

  undef @scets;

  return($StartScet,$StopScet,$SkipScet);
}

# enables inclusion in other code by require
1;
