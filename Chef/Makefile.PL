use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    'NAME'	=> 'Text::Chef',
    'VERSION_FROM' => 'Chef.pm', # finds $VERSION
    'LIBS'	=> [''],   # e.g., '-lm' 
    'DEFINE'	=> '',     # e.g., '-DHAVE_SOMETHING' 
    'INC'	=> '',     # e.g., '-I/usr/include/other' 
'MYEXTLIB' => 'cheflib/libcheflib$(LIB_EXT)'	
);

sub MY::postamble {
        '
$(MYEXTLIB): cheflib/Makefile
	cd cheflib && $(MAKE)
        ';
}
