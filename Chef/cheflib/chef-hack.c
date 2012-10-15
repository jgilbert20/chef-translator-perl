/*
    chef.c
    ------
    This program will convert English from stdin or file to Mock Swedish,
    or Mock Chinese as the Swedes insist, on stdout.

    This program is a C conversion of the lex source by John Hagerman.

    Arjan Kenter, 16 Dec 1994
                  19 Dec 1994 LaTeX related bugs fixed (forgot to test...)


    Jeremy Gilbert -- November 11, 1996 (grath@cs.brandeis.edu)
                  Modified this stuff to use my streamhack library
		  so it could be incorperated into a perl module.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "streamhack.h"

#define INWORD "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'"

#define BUFLEN 100 /* max number of chars to match + trailing context. */
                   /* chosen safely for future extensions, needs only be 5. */

char buf[BUFLEN];
int  head = 0;
int  tail = 0;
int  mtch = 0;
int  eofl = 0;

int nextchar (void)
  {
    int c;
    if (mtch == head)
      {
        if (eofl || (c = sh_getchar ()) == EOF)
          {
            eofl = 1;
            return EOF;
          }
        buf[head++] = c;
        if (head == BUFLEN) head = 0;
        if (head == tail)
          {
            fprintf (stderr, "Chef internal error: buffer overflowed.\n");
            exit (1);
          }
      }
    c = buf[mtch++];
    if (mtch == BUFLEN) mtch = 0;
    return c;
  }

int back (int c)
  {
    if (c != EOF && --mtch < 0) mtch = BUFLEN-1;
    return c;
  }

int match (char *str)
  {
    int c;
    unsigned char *s = (unsigned char *) str;

    mtch = tail;
    while (*s && *s == nextchar ()) s++;
    if (*s) mtch = tail;
    return !*s;
  }

int eof (void)
  {
    back (nextchar ());
    return eofl && head == tail;
  }

int eow (void)
  {
    return strchr (INWORD, back (nextchar ())) == NULL;
  }

int eol (void)
  {
    return back (nextchar ()) == '\n';
  }

int eotex (void)
  {
    int c = back (nextchar ());
    return c == ' ' || c == '\n';
  }

void accept (void)
  {
    tail = mtch;
  }

void echo (void)
  {
    int c;
    mtch = tail;
    if ((c = nextchar ()) != EOF)
      {
        accept ();
        sh_putchar (c);
      }
  }

void chef (void)
  {
    int c, icount = 0;
    int beginword, inword = 0;
    int bork = 1;

    /* Have to put this stuff here since the original author did not
       assume that chef() would be called more than once inbetween
       initilization of its global variables. */
    
    head = 0;
    tail = 0;
    mtch = 0;
    eofl = 0;

    while (!eof ())
      {
        /* Determine if we are at beginning of word, within word or
           outside word.
        */
        mtch = tail;
        beginword = strchr (INWORD, c = nextchar ()) && !inword;

        if (match ("\\"))
          {
            do {echo ();} while (!eof () && !eotex ());
            inword = 0;
            continue;
          }

        /* Suppress "Bork bork bork!" after a line with '%' in it to
           avoid problems with comments in LaTeX files.
        */

        if (match ("%")) {echo (); bork = 0; continue;}
        if (eol ())      {echo (); bork = 1; continue;}

        if (beginword)
          {
            icount = 0;
            if (match ("e"))    {accept (); inword = 1; sh_printf ("i"); continue;}
            if (match ("E"))    {accept (); inword = 1; sh_printf ("I"); continue;}
            if (match ("o"))    {accept (); inword = 1; sh_printf ("oo"); continue;}
            if (match ("O"))    {accept (); inword = 1; sh_printf ("Oo"); continue;}
            if (match ("bork")) {accept (); inword = 1; sh_printf ("bork"); continue;}
            if (match ("Bork")) {accept (); inword = 1; sh_printf ("Bork"); continue;}
          }

        if (inword)
          {
            if (match ("ew"))   {accept (); inword = 1; sh_printf ("oo"); continue;}
            if (match ("f"))    {accept (); inword = 1; sh_printf ("ff"); continue;}
            if (match ("ir"))   {accept (); inword = 1; sh_printf ("ur"); continue;}
            if (match ("ow"))   {accept (); inword = 1; sh_printf ("oo"); continue;}
            if (match ("o"))    {accept (); inword = 1; sh_printf ("u");  continue;}
            if (match ("u"))    {accept (); inword = 1; sh_printf ("oo"); continue;}
            if (match ("U"))    {accept (); inword = 1; sh_printf ("Oo"); continue;}
            if (match ("tion")) {accept (); inword = 1; sh_printf ("shun"); continue;}
            if (match ("i"))    {accept (); inword = 1; sh_printf (icount++ ? "i" : "ee"); continue;}
            if (match ("e")  && eow ()) {accept (); inword = 0; sh_printf ("e-a"); continue;}
            if (match ("en") && eow ()) {accept (); inword = 0; sh_printf ("ee"); continue;}
            if (match ("th") && eow ()) {accept (); inword = 0; sh_printf ("t"); continue;}
          }

        if (match ("an"))  {accept (); inword = 1; sh_printf ("un");  continue;}
        if (match ("An"))  {accept (); inword = 1; sh_printf ("Un");  continue;}
        if (match ("au"))  {accept (); inword = 1; sh_printf ("oo");  continue;}
        if (match ("Au"))  {accept (); inword = 1; sh_printf ("Oo");  continue;}
        if (match ("the")) {accept (); inword = 1; sh_printf ("zee"); continue;}
        if (match ("The")) {accept (); inword = 1; sh_printf ("Zee"); continue;}
        if (match ("v"))   {accept (); inword = 1; sh_printf ("f");   continue;}
        if (match ("V"))   {accept (); inword = 1; sh_printf ("F");   continue;}
        if (match ("w"))   {accept (); inword = 1; sh_printf ("v");   continue;}
        if (match ("W"))   {accept (); inword = 1; sh_printf ("V");   continue;}
        if (match ("a") && !eow ()) {accept (); inword = 1; sh_printf ("e"); continue;}
        if (match ("A") && !eow ()) {accept (); inword = 1; sh_printf ("E"); continue;}
        if (match (".") &&  eol () && bork)
          {
            accept (); inword = 0; sh_printf (".\nBork Bork Bork!");
            continue;
          }

        inword = strchr (INWORD, c) != NULL;
        echo ();
      }
  }


