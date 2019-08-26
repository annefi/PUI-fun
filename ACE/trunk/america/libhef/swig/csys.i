// File: csys.i
// $Id: csys.i,v 1.1.1.1 2000/06/02 13:37:24 jraines Exp $

%subsection "Indexing"
// index function (2 D) (row,col)
extern int I(int ir, int Nc, int ic);

// index function for arrays with 3 dim (row,col,plane)
extern int I3(int ir, int Nc, int ic, int ip, int Nr);

%subsection "Memory allocation"
// allocate memory for (vec)tor of type (d)ouble
extern double *dvec_get(long n);

// free memory allocated by dvec_get.
extern void dvec_free(double *v);

// revision string
extern char *libhefrev(void);
