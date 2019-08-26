#! /usr/bin/perl
# Extract load/fill sequence from axlv2 output (sent to stdin)

while (<STDIN>){
  if (/calc. box rates for (\d{3})_(\d{2,3})/ ){
    print $_;
    $doyfr = $1 + $2/1000.;
    $doy = $1;
    $diff = $doyfr - $last_doyfr;
    $doy_diff = $doy - $last_doy;
    $last_doyfr = $doyfr;
    $last_doy = $doy;
    $diff = sprintf("%4.3f",$diff);
    print "====================>diff since last doyfr: $diff\n";

    if ( abs($diff - 0.04) > 0.005 && $doy_diff < 0.1 ) {
      print "                                           IRREGULAR\n";
      $num_irregular++;
    }
  }
}

print "Number of irregular intervals: $num_irregular\n";
