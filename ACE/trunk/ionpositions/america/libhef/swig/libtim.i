// File: libtim.i
// $Id: libtim.i,v 1.1.1.1 2000/06/02 13:37:25 jraines Exp $

%title "Interface to libtim", before, pre

%text %{
Time handling based on time in seconds since 1-1-1970:00:00
%}

// convert seconds to array with format:
// sec70 julian secs DOY day month year hr min sec week-day (0 for sunday)
extern void sec70_time (long alltime[14], long *sec70);

// convert [year,doy] to seconds since 1-1-1970
extern void doy_time   (long alltime[14], long *doy, long *year);

// convert [day,month,year] to seconds since 1-1-1970
extern void date_time  (long alltime[14], long *mday, long *mon, long *year);

// text with date from seconds since 1-1-1970
extern char *timstr    (long sec70);


%text %{
Toolbox
%}

// julian --> date
extern void ltcaldat   (long *julian, long *mm, long *id, long *iyyy);

// date --> julian
extern void ltjulday   (long *mm, long *id, long *iyyy,long *julday);

// test for leap year
extern int  is_leap    (int iyear);
