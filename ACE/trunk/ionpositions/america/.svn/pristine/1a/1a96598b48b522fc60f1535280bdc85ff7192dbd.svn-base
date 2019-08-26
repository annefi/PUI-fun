#! /usr/bin/perl
# for figuring out subcommutation of SEPICA HK block
# JR, 25Sep2003

for ($nedb = 0; $nedb < 60; $nedb++){
  $offset = ($nedb % 5)*22;

  printf("%d_mod_5=%d offset=%d pos=", $nedb, $nedb % 5, $offset);

  for ($i = 0; $i < 22; $i++){
    $pos = $offset + $i;
    print "$pos ";
  }
  print "\n";
}

