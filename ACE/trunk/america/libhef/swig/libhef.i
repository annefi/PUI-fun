// File : libhef.i
// $Id: libhef.i,v 1.2 2003/11/09 12:50:27 jraines Exp $

%title "Interface to libhef", before, pre

%module libhef

%{
#include "decoded.h"
%}

%text %{
Some rules to remember when using this library:
%}
%text %{
(1) There are no multi-dimensional arrays. Array indexing
    of more-dimensional arrays is achieved by the "index" routines
    I and I3.
    Exception: The "cyc" data structure containing the
               decoded ACE/S3 data uses C-style multi-dimensional
               arrays. The a3 routines give transparent access
               to this data without the need of (multi-dimensional)
               arrays.
%}
%text %{
(2) Accessing SWICS/ACE data:
    The data is stored in binary format in a netCDF file (stored
    are the EDBs, grouped to cycles, plus some ancillary information
    like quality and time).
    If data is accessed with a3readcycle, the data is read and
    stored in static memory within the a3dif routine. The same is
    true for the "expanded" data. 

    The other a3 routines then use simple look-up of that static
    memory, sometimes storing it by themselfs into static memory.

    Make sure that you get the newest value for each variable of
    interest whenever a new cycle has been read.
%}

%text %{
(3) Routines return the number of errors, if not otherwise
    stated. Thus, a routine returning 0 completed successfully.
    Example: reading cycles with a3readcycle() will return
             0 until the last cycle has been read. At this time,
             it will return 1.
%}

%text %{
(4) ACE/SWICS and SWIMS data are sectored (ACE is a spinning
    spacecraft). The routines to access rates therefore provide
    the possibility to access data from one specific sector.
    In addition, the sum over all sectors is available. Internally,
    the rates are stored in an array of length 9. Elements 0-7
    contain the rates in the individual sectors, while
    element 9 contains the sum.
%}

%text %{
(5) The routine names are cryptic. Sometimes however, they carry a little
    information:
    memno indicates                  memno indicates
    a3    ACE/S3 (that is:           eq    E/q
          SWICS,SWIMS and SEPICA)    eoq   E/q
    x     SWICS                      moq   m/q
    m     SWIMS                      mass  m
    tab   table
%}

%text %{
Note that this documentation covers a large part of the
routines of libhef, but not all of them. Typically, the
most often used routines are documented here. There are
some low-level routines the user never has to use directly,
which are omitted. I am afraid that the source code will
not be of big help, but you are free to have a look at it
at: pooh://home/acedata/software/src.
 4-Feb-1999/Hefti
%}


%section "Access and handling of ACE data"
%text %{
(a3dif.i)
%}
%include a3dif.i

%section "Utilities for ACE (DPU classification)"
%text %{
(ace.i)
%}
%include ace.i

%section "my numerical routines"
%text %{
(hefnum.i)
%}
%include hefnum.i

%section "Memory handling/array indexing"
%text %{
(csys.i)
%}
%include csys.i

%include libtim.i

%include hefutil.i
