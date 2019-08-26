#! /bin/bash 
# keep these first
/bin/bash <<ENDOFJOB >& axlv2.out
echo run starting at `date`

time ./axlv2 <<EOF
1		   # Load Measurement Array (true or false)? 
0		   # Save Measurement Array when finished (true or false)? 
2                  # Enter PHA filter flag:
axlv2		   # Enter filename base (for all files): 
2000158		   # Enter start date (yyyydoy): 
2000158		   # Enter stop date (yyyydoy): 
5		   # Enter number of cycles to load at once (5-10 works well): 
0		   # Enter maximum number of these groups to process
1		   # Enter global debugging level (0-5): 
/home/acedata/LV1  # Enter directory containing LV1 data (DNW)
1		   # Do boxrates calculation? 
1		   # Do spillrates calculation? 
1		   # Do probrates calculation? 
0		   # Load probrates? 
1		   # Save probrates? 
1		   # Do distribution function calculations? 
EOF

# keep these last
echo run finished at `date`
ENDOFJOB

