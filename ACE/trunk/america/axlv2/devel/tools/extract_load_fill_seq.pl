#! /usr/bin/perl
# Extract load/fill sequence from axlv2 output (sent to stdin)

while (<STDIN>){
#  if (/AceSwicsData::load/ || /::fill/){print $_}
  if (/Cycle: rec/ || /calc. box/ || /NumCycLoaded/) {print $_}
}
