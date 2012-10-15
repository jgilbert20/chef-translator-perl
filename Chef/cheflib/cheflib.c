#include <stdlib.h>
#include "cheflib.h"
#include "streamhack.h"
        
char *
chef(c)
     const char *    c;
{
  sh_setreadbuffer( c );
  sh_clearwritebuffer();

/*  printf( "Readbuffer [%s]\n", c ); */

  chef();

/*  printf( "Outbuffer [%s]\n", sho_buffer ); */

  return sho_buffer;
}

