#! /usr/bin/perl -I/shrg1/local/lib

use libace_ancil;


print "libancil was successfully loaded.\n";

$result = libancil::a3goa_read("/shrg1/ace/sw/src/acetest/anciltest/ACE_ANCIL.HDF");
print "result of call to 'a3goa_read()': $result\n";

#$result = libancil::a3goa(1054252800);
libancil::print_aosr(libancil::a3goa(1054252800));

$attx = libancil::a3goa_att_GSE_x(1054252800);
$atty = libancil::a3goa_att_GSE_y(1054252800);
$attz = libancil::a3goa_att_GSE_z(1054252800);
print "Attitude:\n   X: $attx\n   Y: $atty\n   Z: $attz\n";

$posx = libancil::a3goa_pos_GSE_x(1054252800);
$posy = libancil::a3goa_pos_GSE_y(1054252800);
$posz = libancil::a3goa_pos_GSE_z(1054252800);
print "Position:\n   X: $posx\n   Y: $posy\n   Z: $posz\n";

$velx = libancil::a3goa_vel_GSE_x(1054252800);
$vely = libancil::a3goa_vel_GSE_y(1054252800);
$velz = libancil::a3goa_vel_GSE_z(1054252800);
print "Velocity:\n   X: $velx\n   Y: $vely\n   Z: $velz\n";

exit(0);
