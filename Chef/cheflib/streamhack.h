/*******************
 * Stream Hack
 * By Jeremy Gilbert
 * grath@cs.brandeis.edu
 *
 * Header file
 *******************/
 

#define SH_MAX_LENGTH 100000
#define SH_CHUNKSIZE 512

/* Uncomment this line if you want to see all the gory details of the
   library as it executes. */

/* #define SH_DEBUG	    */

/* Stuff for the input stream hack */

extern char *sh_buffer;
extern int sh_pos;
extern int sh_size;

/* Stuff for the output stream hack */

extern char *sho_buffer;
extern int sho_pos;
extern int sho_size;
