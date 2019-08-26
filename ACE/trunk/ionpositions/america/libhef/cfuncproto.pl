#!/usr/bin/perl

while(<>) {

  chop;

  #void date_time(long alltime[14], long *mday, long *mon, long *year)

  if( $_ =~ m|^(\S)([^\(]*)(\ )*\(([^\)]*)\)|) {
    print "$_\n";
  }
}
