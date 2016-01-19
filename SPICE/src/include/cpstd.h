/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1986 Wayne A. Christopher, U. C. Berkeley CAD Group
**********/

/*
 * Standard definitions. This file serves as the header file for std.c and
 * wlist.c
 */

#define _STD_H_

typedef int bool;

#include "misc.h"

#include <stdio.h>


/* Double linked lists of words. */

// A Double linked list which is used to dynamical allocation
struct wordlist {
    char *wl_word;// The actual data
    struct wordlist *wl_next;// Points to the next word list struct
    struct wordlist *wl_prev;// Points to the previous word list struct
} ;

typedef struct wordList wordlist;// This creates wordlist as a type

/* Complex numbers. */
/*
struct _Complex {   // IBM portability... 
    double cx_real;
    double cx_imag;
} ;
*/
typedef struct _Complex complex;

#define realpart(cval)  ((struct _Complex *) (cval))->cx_real
#define imagpart(cval)  ((struct _Complex *) (cval))->cx_imag

/* Externs defined in std.c */
extern char *getusername();
extern char *gethome();
extern char *tildexpand();
extern char *printnum();
extern int cp_numdgt;
extern void fatal();
extern void setenv();
extern void cp_printword();

/* Externs from wlist.c */

extern char **wl_mkvec();
extern char *wl_flatten();
extern int wl_length();
extern void wl_free();
extern void wl_print();
extern void wl_sort();
extern wordlist *wl_append();
extern wordlist *wl_build();
extern wordlist *wl_copy();
extern wordlist *wl_range();
extern wordlist *wl_nthelem();
extern wordlist *wl_reverse();
extern wordlist *wl_splice();

