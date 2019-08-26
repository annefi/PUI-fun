#! /bin/bash 
# File:  run-axlv2.sh
#
# Description:
#   Script for running *hourly* ACE Level II version 2 data processor 
#   and associated IDL code.
#
# Author(s):  Jim Raines (jmr)
#
# Method:
#
# Revision controlled by CVS:
# $Id: run-axlv2.sh,v 1.21 2005/03/24 15:53:43 jraines Exp $
#
# REVISION WARNING:  This code is meant to be edited and as such, care 
# should be exercised when using a version not found in the axlv2/tools tree.
# It may be modified from the official revision.
#
# Major (Structural) Modification History:
#     Apr2001   jmr   initial coding
#   15Nov2004   jmr   Put auto-reset of directories to devel. for user jraines

# $Id: run-axlv2.sh,v 1.21 2005/03/24 15:53:43 jraines Exp $
echo run starting at `date`

# -------------------------------------------------------------------
# Set date, tags and locations
# -------------------------------------------------------------------
# axlv2 source directory
axlv2_dir=/shrg1/ace/sw/src/axlv2

# axlv2 executable directory
# note: set this to '.' to use executable already in this directory
axlv2_exe_dir=/shrg1/ace/sw/bin

# axlv2 executable name
axlv2_exe=axlv2

start_date=2003302
stop_date=${start_date}

# text tag for some IDL plots
tag="${start_date}"

# reset run directories for development version
# PLEASE IGNORE THIS if you are not developing axlv2 code directly
if [ $USER == 'jraines' ]; then
    axlv2_dir=/home/jraines/ace/axlv2
    axlv2_exe_dir=$axlv2_dir;
fi

# -------------------------------------------------------------------
# Take snapshots of actively developed portions to facilitate tracking
# -------------------------------------------------------------------
swindal=$axlv2_dir/../swindal
(d=`pwd`; cd $swindal/src; make DistFunc.ps; cp DistFunc.ps $d)

# -------------------------------------------------------------------
# Build input file
# -------------------------------------------------------------------
cat > axlv2.in <<EOF
3.6                # Enter input sequence version number: 
0		   # Load Measurement Array (true or false)? 
0		   # Save Measurement Array when finished (true or false)? 
7                  # Enter PHA filter flag:
0.3                # Enter velocity filter value (0.0 for none):
2                  # Use which FM (-1..4, 2 is standard):
0		   # Output E-T slices?
1		   # Output MMQ data for MA?
1.0                # Enter MMQ data mass *lower* limit: 
100.0              # Enter MMQ data mass *upper* limit: 
1.0                # Enter MMQ data m/q *lower* limit: 
20.0               # Enter MMQ data m/q *upper* limit: 
axlv2		   # Enter filename base (for all files): 
${start_date}	   # Enter start date (yyyydoy): 
${stop_date}	   # Enter stop date (yyyydoy): 
5		   # Enter number of cycles to load into RAM at once:
5		   # Enter number of cycles to accum. per timestep (-1=>inf):
1		   # Enter global debugging level (0-5): 
/shrg1/ace/LV1     # Enter directory containing LV1 data
/shrg1/ace/calib/swics/eff/ux-ax-hybrid   # Enter efficiency directory: 
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
1		   # Do distribution function calculations? 
EOF

# -------------------------------------------------------------------
# Run axlv2
# -------------------------------------------------------------------
cp -v $axlv2_exe_dir/$axlv2_exe .
sleep 1
time ./$axlv2_exe < axlv2.in

# put RCS IDs into output file
./$axlv2_exe --versions

#rm -f ./axlv2

# -------------------------------------------------------------------
# Build rate plot input file
# -------------------------------------------------------------------
cat > axlv2_rates.idl << EOF
\$ ln -fs $axlv2_dir/tools/axlv2_rates_template.save ./axlv2_rates_template.save
.run $axlv2_dir/tools/axlv2_rates.pro

file='axlv2_br_${start_date}.dat'
if (file_exists(file)) then $
axlv2_rates, file=file, rate_type='Box',$ 
	data=dbr, tag='$tag'

file='axlv2_sr_${start_date}.dat'
if (file_exists(file)) then $
axlv2_rates, file=file, $
    rate_type='Spill', data=dsr, tag='$tag'

file='axlv2_pr_${start_date}.dat'
if (file_exists(file)) then $
axlv2_rates, file=file, rate_type='Prob',$
        data=dpr, tag='$tag'
EOF

# -------------------------------------------------------------------
# Build forward model comparison input file
# -------------------------------------------------------------------
cat > fmcomp.idl << EOF
\$ ln -fs $axlv2_dir/tools/axlv2_fmcomp_template.save .
\$ ln -fs $axlv2_dir/tools/axlv2_pccomp_template.save .
.run $axlv2_dir/tools/read_fmc.pro
.run $axlv2_dir/tools/read_pcc.pro   
.run $axlv2_dir/tools/read_ets.pro
.run $axlv2_dir/tools/plot_ets.pro
.run $axlv2_dir/tools/fmcomp.pro   
file='axlv2_et_slices.dat'
if (file_exists(file)) then $
  fmcomp, fmcfile='axlv2_fmcomp.dat', etsfile=file,$
    tag='$tag',fmcdata=fmc
EOF

# -------------------------------------------------------------------
# Run IDL on all input files
# -------------------------------------------------------------------
# using the pipe removes the need for an 'exit' which is useful when
# re-running the IDl processing
cat axlv2_rates.idl fmcomp.idl | idl


