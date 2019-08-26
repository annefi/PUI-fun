// File: hefutil.i
// $Id: hefutil.i,v 1.1.1.1 2000/06/02 13:37:25 jraines Exp $

%text %{
hefutil.i --- Compilation of tools.
%}


// complain
//extern int perr(FILE *fp, int ilevel, char *fmt, ...);

// set level of complaints (number of error messages)
// Possible values:
// 0 PEEYORE complain about everything
// 1 PNOVICE errors and not-so-obvious problems
// 2 PEXPERT severe errors only
extern int perr_setlevel(int ilevel);
