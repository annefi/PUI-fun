/* $Id: att_orbit.h,v 1.1 1996/01/26 23:05:11 jeff Exp $ */

typedef struct
{
  float x;              /* J2000 X of Angular Momentum Vector */
  float y;              /* J2000 Y of Angular Momentum Vector */
  float z;              /* J2000 Z of Angular Momentum Vector */
} J2000AMV;             /* J2000 Angular Momentum Vector */

typedef struct
{
  float r;              /* RTN R of Angular Momentum Vector */
  float t;              /* RTN T of Angular Momentum Vector */
  float n;              /* RTN N of Angular Momentum Vector */
} RTNAMV;               /* RTN Angular Momentum Vector */

typedef struct
{
  float x;              /* J2000 X of Spin Rate Vector */
  float y;              /* J2000 Y of Spin Rate Vector */
  float z;              /* J2000 Z of Spin Rate Vector */
} J2000SRV;             /* J2000 Spin Rate Vector */

typedef struct
{
  float r;              /* RTN R of Spin Rate Vector */
  float t;              /* RTN T of Spin Rate Vector */
  float n;              /* RTN N of Spin Rate Vector */
} RTNSRV;               /* RTN Spin Rate Vector */

enum state_stat
{
  BEG_PASS, END_PASS, BEG_MANVR, END_MANVR
};

struct SC_DAS           /* Spacecraft Definitive Attitude State */
{
  int sc_clock;         /* Spacecraft Clock */
  char utc_time[18];    /* UTC Time in YYYY-DD.hhmmssfff format */
  enum state_stat stat; /* State Status */
  J2000AMV j2000_amv;   /* J2000 Angular Momentum Vector */
  J2000SRV j2000_srv;   /* J2000 Spin Rate Vector */
  RTNAMV rtn_amv;       /* RTN Angular Momentum Vector */
  RTNSRV rtn_srv;       /* RTN Spin Rate Vector */
  float p2b[3][3];      /* Principle to body axis transform matrix */
  float nut_angle;      /* Magnitude of Nutation Angle */
};

/*--------------------------------------------------------------------*/

typedef struct
{
  float x;              /* Spacecraft Position X */
  float y;              /* Spacecraft Position Y */
  float z;              /* Spacecraft Position Z */
} SCPOS;

typedef struct
{
  float x;              /* Spacecraft Velocity X */
  float y;              /* Spacecraft Velocity Y */
  float z;              /* Spacecraft Velocity Z */
} SCVEL;

typedef struct
{
  float x;              /* GSE Spacecraft Position X */
  float y;              /* GSE Spacecraft Position Y */
  float z;              /* GSE Spacecraft Position Z */
} SCPOSGSE;

typedef struct
{
  float x;              /* GSE Spacecraft Velocity X */
  float y;              /* GSE Spacecraft Velocity Y */
  float z;              /* GSE Spacecraft Velocity Z */
} SCVELGSE;

struct SC_DOS           /* Spacecraft Definitive Orbit State */
{
  char utc_time[18];    /* UTC Time in YYYY-DD.hhmmssfff format */
  SCPOS sc_pos;         /* Spacecraft Position Vector */
  SCVEL sc_vel;         /* Spacecraft Velocity Vector */
  SCPOSGSE scpos_gse;   /* Spacecraft Position Vector in GSE */
  SCVELGSE scvel_gse;   /* Spacecraft Velocity Vector in GSE */
};

/*--------------------------------------------------------------------*/
