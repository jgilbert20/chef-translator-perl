package Text::Chef;

use strict;
use Carp;
use vars qw($VERSION @ISA @EXPORT_OK $AUTOLOAD);

require Exporter;
require DynaLoader;
require AutoLoader;

@ISA = qw(Exporter DynaLoader);
# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.
@EXPORT_OK = qw(
	chef
);
$VERSION = '1.00';

sub AUTOLOAD {
    # This AUTOLOAD is used to 'autoload' constants from the constant()
    # XS function.  If a constant is not found then control is passed
    # to the AUTOLOAD in AutoLoader.

    my $constname;
    ($constname = $AUTOLOAD) =~ s/.*:://;
    my $val = constant($constname, @_ ? $_[0] : 0);
    if ($! != 0) {
	if ($! =~ /Invalid/) {
	    $AutoLoader::AUTOLOAD = $AUTOLOAD;
	    goto &AutoLoader::AUTOLOAD;
	}
	else {
		croak "Your vendor has not defined Text::Chef macro $constname";
	}
    }
    eval "sub $AUTOLOAD { $val }";
    goto &$AUTOLOAD;
}

bootstrap Text::Chef $VERSION;

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is the stub of documentation for your module. You better edit it!

=head1 NAME

Chef - Perl extension for converting stuff into Chef-speak

=head1 SYNOPSIS

  use Text::Chef;
  &Chef::chef($stuff);

=head1 DESCRIPTION

This Perl module embeds the 'chef.c' program by John Hagerman
and released in the eighties to USENET.  It converts a scalar
containing regular text into text that might be spoken by the Swedish
Chef of the Muppet Show.

Invocation is simple. The module defines a function called
&Chef::chef() that takes a single argument and returns a scalar
value containing the new text. Here is the output of the program on
the previous paragraph:

	Thees Perl mudoole-a imbeds zee 'cheff.c' 
	prugrem by Juhn Hegermun und releesed in zee 
	ieeghties tu USENET.  It cunferts a sceler
	cunteeening regooler text intu text thet 
	meeght be-a spukee by zee Svedeesh Cheff ooff
	zee Mooppet Shoo.

	Bork Bork Bork!

I think this all should be fairly simple and straightforward.

=head1 DISCLAIMER

This is my first Perl module. I appologize for any incompleteness or
problems it may have. Please e-mail me with any way I can make it
better.

=head1 AUTHOR

Jeremy Gilbert (I<jgilbert@world.std.com>) wrote the Perl wrapper to this
script. According to the original chef.c file, the code was a
conversion of the original lex code by John Hagerman, produced by Arjan
Kenter in 1994.

John Hagerman has granted me permission to redistribute this as a Perl
module. His email address appears to be (I<hagerman@chrysalis.com>).

=head1 SEE ALSO

perl(1).

=cut
