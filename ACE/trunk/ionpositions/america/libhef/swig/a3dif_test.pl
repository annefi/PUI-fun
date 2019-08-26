#!/usr/bin/perl

use a3dif;

$res = a3dif::a3opencyclefile("/home/hefti/data/ace/aswxres/98141.nc");
print "$res\n";

$res = a3dif::a3readcycle();
print "$res\n";

$res = a3dif::a3expand();
print "$res\n";

$cnq = a3dif::a3gcnq();
for($i = 0; $i < 12; $i++) {
  $res = a3dif::aval($cnq,$i);
  printf("%2d %10.3f\n",$i,$res);
}
for($i = 12; $i < 15; $i++) {
  $res = a3dif::aval($cnq,$i);
  printf("%2d %10.6f\n",$i,$res/34.59577);
}

$cnm = a3dif::a3gcnm();
for($i = 0; $i < 10; $i++) {
  $res = a3dif::aval($cnm,$i);
  printf("%2d %10.3f\n",$i,$res);
}
for($i = 10; $i < 16; $i++) {
  $res = a3dif::aval($cnm,$i);
  printf("%2d %10.6f\n",$i,$res/25.50089);
}

$res = a3dif::a3closecyclefile();
print "$res\n";
