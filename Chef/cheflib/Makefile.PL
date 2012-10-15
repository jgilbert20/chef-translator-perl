
use ExtUtils::MakeMaker;
$Verbose = 1;
WriteMakefile(
     'NAME' => 'Text::Chef::cheflib',
     'clean'     => {'FILES' => 'libcheflib.a'},
);

sub MY::postamble {
                '
all :: static
static ::       libcheflib$(LIB_EXT)
libcheflib$(LIB_EXT): $(O_FILES)
	$(AR) cr libcheflib$(LIB_EXT) $(O_FILES)
	$(RANLIB) libcheflib$(LIB_EXT)
        ';
}
