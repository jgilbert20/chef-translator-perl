#ifdef __cplusplus
extern "C" {
#endif
#include "cheflib/cheflib.h"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#ifdef __cplusplus
}
#endif

static int
not_here(s)
char *s;
{
    croak("%s not implemented on this architecture", s);
    return -1;
}

static double
constant(name, arg)
char *name;
int arg;
{
    errno = 0;
    switch (*name) {
    }
    errno = EINVAL;
    return 0;

not_there:
    errno = ENOENT;
    return 0;
}


MODULE = Text::Chef		PACKAGE = Text::Chef


double
constant(name,arg)
	char *		name
	int		arg


char *
chef(c)
	const char *    c
	OUTPUT:
	RETVAL