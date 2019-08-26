/* $Id: anci.h,v 1.1 1996/01/26 19:14:32 jeff Exp $ */

/*--------------------------------------------------------------------*/
#define VECTSIZ 3
#define SECTSIZ 8

/*--------------------------------------------------------------------*/
typedef struct
{
  char isotm[22];                 /* YYYY-DDDThh:mm:ss.fffZ  */
  unsigned int sctime;            /* 32 bit spacecraft clock */
} TimeGm;

typedef struct
{
  float rotation[VECTSIZ][VECTSIZ]; /* ratation matrix (3x3)   */
  float angular[VECTSIZ];           /* angular momentum vector */
  float nutation;                   /* nutation angle, degree/radius ?? */
} AttGm;

typedef struct
{
  float GSE[VECTSIZ];               /* GSE corrdinator system  */
  float J2000[VECTSIZ];             /* J2000 corrdinator system */
} PosGm;

typedef struct
{
  /* use formula phi(t)=a+b(t-t0)                            */
  /* where t0 is the beginning time of the game              */

  float a;                          /* parameter #1            */
  float b;                          /* parameter #2            */
  float phi1[SECTSIZ];              /* sector boundary #1      */
  float phi2[SECTSIZ];              /* sector boundary #2      */
} SpinGm;

struct AnciSet                      /* setkey=aA               */
{
  TimeGm time;
  AttGm attitude;
  PosGm position;
  SpinGm spin_phase;
};

/*--------------------------------------------------------------------*/




