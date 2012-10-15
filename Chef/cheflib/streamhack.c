/*******************
 * Stream Hack
 * By Jeremy Gilbert
 * grath@cs.brandeis.edu
 *
 * Replacements for some stream-handling routines to make it quicker
 * to switch programs from using streams to using memory buffers.
 *
 * This is an utter embarrasment, and was coded in less than 30
 * minutes. Error handling is negligble -- my strategy is to just
 * return nothing if there is a problem. The nice thing is, the task
 * is simple enough that there shouldn't be any major problems. (Where
 * have I heard that before? :))
 *
 *******************/

#include <stdio.h>
#include <stdlib.h>

#include "streamhack.h"

/* Stuff for the input stream hack */

char *sh_buffer = NULL;
int sh_pos = 0;
int sh_size = 0;

/* Stuff for the output stream hack */

char *sho_buffer = NULL;
int sho_pos = 0;
int sho_size = 0;

void sh_clearwritebuffer()
{

#ifdef SH_DEBUG
  printf( "Clearwrite\n");
#endif

  if( sho_buffer != NULL )
    free( sho_buffer );

  sho_buffer = malloc( SH_CHUNKSIZE );
  if( sho_buffer == NULL )
      return;  

  sho_buffer[0] = '\0';  

  sho_size = SH_CHUNKSIZE;
  sho_pos = 0;
}

void sh_growbuffer()
{

#ifdef SH_DEBUG
  printf( "Growing buffer by %d\n", SH_CHUNKSIZE );
#endif

  if( sho_buffer == NULL )
    return;

  sho_size += SH_CHUNKSIZE;

  sho_buffer = realloc( sho_buffer, sho_size );
}

void sh_putchar(char c)
{
#ifdef SH_DEBUG
  printf("PUT: [[%s]] size %d pos %d\n", sho_buffer, sho_size, sho_pos);
#endif

    sho_buffer[sho_pos] = c;
    sho_buffer[sho_pos + 1 ] = '\0';
    sho_pos++;

    if( (sho_pos + 2) >= sho_size )
	sh_growbuffer();
}


void sh_setreadbuffer( char *newbuffer )
{

#ifdef SH_DEBUG
  printf( "Set Read Buffer\n");
#endif

  sh_buffer = newbuffer;
  sh_pos = 0;
  sh_size = sh_getbuffersize( sh_buffer );
}

int sh_getbuffersize( char *buff )
{
  int i;

  for( i = 0 ; i < SH_MAX_LENGTH && buff[i] != 0 ; i++ )
    ;

  return i;
}

char sh_getchar()
{
#ifdef SH_DEBUG
  printf("GET: [[%s]] size %d pos %d\n", sh_buffer, sh_size, sh_pos); 
#endif

  return sh_pos >= sh_size ? EOF : sh_buffer[sh_pos++];
}

char sh_printf( char *stuff)
{
  /* A VERY poor implementation of printf, don't you think? */
  
  int i;

  for( i = 0 ; i < SH_MAX_LENGTH && stuff[i] != 0 ; i++ )
      sh_putchar( stuff[i] );

}
 


