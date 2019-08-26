#! /usr/bin/perl
# extract duty cycle and aspect angle info from axlv2 run log
# Jim Raines, 16Aug2004

while (<STDIN>) {
  if ($_ =~ /AspectAngle = (\d+)/){
    print $_;
  }

  if ($_ =~ /AceSwicsDutyCycle::/){
    print $_;
  }
}

