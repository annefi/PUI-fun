#! /bin/bash 
# keep this first
/bin/bash <<ENDOFJOB >& axlv2.out

echo program starting at `date`

#time ./axlv2 <<EOF >& axlv2.out
time ./axlv2 <<EOF
1		   # Load Measurement Array (true or false)? 
0		   # Save Measurement Array when finished (true or false)? 
2                  # Enter PHA filter flag:
axlv2		   # Enter filename base (for all files): 
2000158		   # Enter start date (yyyydoy): 
2001158		   # Enter stop date (yyyydoy): 
5		   # Enter number of cycles to load at once (5-10 works well): 
0		   # Enter maximum number of these groups to process
1		   # Enter global debugging level (0-5): 
/home/acedata/LV1  # Enter directory containing LV1 data (DNW)
1		   # Do boxrates calculation? 
1		   # Do spillrates calculation? 
0		   # Do probrates calculation? 
0		   # Load probrates? 
0		   # Save probrates? 
0		   # Do distribution function calculations? 
EOF

echo program finished at `date`

# keep this last
ENDOFJOB

