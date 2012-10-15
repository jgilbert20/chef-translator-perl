# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl test.pl'

######################### We start with some black magic to print on failure.

# Change 1..1 below to 1..last_test_to_print .
# (It may become useful if the test is moved to ./t subdirectory.)

BEGIN { $| = 1; print "1..5\n"; }
END {print "not ok 1\n" unless $loaded;}
use Text::Chef qw( chef );
$loaded = 1;
print "ok 1\n";

######################### End of black magic.

### Test if null input works

print &chef( "" ) eq "" ? "ok 2\n" : "not ok 2\n";

### Test a simple word

$sample = "Changes";
$answer = "Chunges";
$output = &chef( $sample );
print $output eq $answer ? "ok 3\n" : "not ok 3\n";

### Be sure we can do it again

$output = &chef( $sample );
print $output eq $answer ? "ok 4\n" : "not ok 4\n";

### Go all out and feed it something crazy

$sample = "sdpfoj dff023s sdf sd;flk234==2 sdf23 sfkcmmdei 23[;'==90 234
sdfk sdfnndnnsne sdfgope0922 xdlfkj sd wl; this is a stupid test";

$answer = "sdpffuj dffff023s sdff sd;flk234==2 sdff23 sffkcmmdeee 23[;'==90 234
sdffk sdffnndnnsne-a sdffgupe-a0922 xdlffkj sd vl; thees is a stoopeed test";

$output = &chef( $sample );
print $output eq $answer ? "ok 5\n" : "not ok 5\n";







