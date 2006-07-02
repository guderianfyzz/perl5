/*  -*- buffer-read-only: t -*-
 *
 *    perlapi.c
 *
 *    Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 1999,
 *    2000, 2001, 2002, 2003, 2004, 2005, 2006, by Larry Wall and others
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 * !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
 * This file is built by embed.pl from data in embed.fnc, embed.pl,
 * pp.sym, intrpvar.h, perlvars.h and thrdvar.h.
 * Any changes made here will be lost!
 *
 * Edit those files and run 'make regen_headers' to effect changes.
 *
 *
 * Up to the threshold of the door there mounted a flight of twenty-seven
 * broad stairs, hewn by some unknown art of the same black stone.  This
 * was the only entrance to the tower.
 *
 */

#include "EXTERN.h"
#include "perl.h"
#include "perlapi.h"

#if defined (MULTIPLICITY)

/* accessor functions for Perl variables (provides binary compatibility) */
START_EXTERN_C

#undef PERLVAR
#undef PERLVARA
#undef PERLVARI
#undef PERLVARIC
#undef PERLVARISC

#define PERLVAR(v,t)	t* Perl_##v##_ptr(pTHX)				\
			{ dVAR; PERL_UNUSED_CONTEXT; return &(aTHX->v); }
#define PERLVARA(v,n,t)	PL_##v##_t* Perl_##v##_ptr(pTHX)		\
			{ dVAR; PERL_UNUSED_CONTEXT; return &(aTHX->v); }

#define PERLVARI(v,t,i)	PERLVAR(v,t)
#define PERLVARIC(v,t,i) PERLVAR(v, const t)
#define PERLVARISC(v,i)	PL_##v##_t* Perl_##v##_ptr(pTHX)		\
			{ dVAR; PERL_UNUSED_CONTEXT; return &(aTHX->v); }

#include "thrdvar.h"
#include "intrpvar.h"

#undef PERLVAR
#undef PERLVARA
#define PERLVAR(v,t)	t* Perl_##v##_ptr(pTHX)				\
			{ dVAR; PERL_UNUSED_CONTEXT; return &(PL_##v); }
#define PERLVARA(v,n,t)	PL_##v##_t* Perl_##v##_ptr(pTHX)		\
			{ dVAR; PERL_UNUSED_CONTEXT; return &(PL_##v); }
#undef PERLVARIC
#undef PERLVARISC
#define PERLVARIC(v,t,i)	\
			const t* Perl_##v##_ptr(pTHX)		\
			{ PERL_UNUSED_CONTEXT; return (const t *)&(PL_##v); }
#define PERLVARISC(v,i)	PL_##v##_t* Perl_##v##_ptr(pTHX)	\
			{ dVAR; PERL_UNUSED_CONTEXT; return &(PL_##v); }
#include "perlvars.h"

#undef PERLVAR
#undef PERLVARA
#undef PERLVARI
#undef PERLVARIC
#undef PERLVARISC

#ifndef PERL_GLOBAL_STRUCT
/* A few evil special cases.  Could probably macrofy this. */
#undef PL_ppaddr
#undef PL_check
#undef PL_fold_locale
Perl_ppaddr_t** Perl_Gppaddr_ptr(pTHX) {
    static Perl_ppaddr_t* const ppaddr_ptr = PL_ppaddr;
    PERL_UNUSED_CONTEXT;
    return (Perl_ppaddr_t**)&ppaddr_ptr;
}
Perl_check_t**  Perl_Gcheck_ptr(pTHX) {
    static Perl_check_t* const check_ptr  = PL_check;
    PERL_UNUSED_CONTEXT;
    return (Perl_check_t**)&check_ptr;
}
unsigned char** Perl_Gfold_locale_ptr(pTHX) {
    static unsigned char* const fold_locale_ptr = PL_fold_locale;
    PERL_UNUSED_CONTEXT;
    return (unsigned char**)&fold_locale_ptr;
}
#endif

END_EXTERN_C

#endif /* MULTIPLICITY */

/* ex: set ro: */
