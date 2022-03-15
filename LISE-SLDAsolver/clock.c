#include "vars_nuclear.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// Contains functions used for keeping track of time.
// Codes developed by Kenny Roche.

void b_it( double *itgtod, clock_t *it_clock )
{
  struct timeval is;
  gettimeofday( &is , NULL ) ;
  *it_clock = clock() ;
  *itgtod = is.tv_sec + 1e-6 * is.tv_usec ;
}

double e_it( int type, double *itgtod, clock_t *it_clock )
{
  struct timeval is;
  clock_t itclock1;
  switch ( type )
    {
    case 0 :
      itclock1 = clock() ;
      gettimeofday( &is , NULL ) ;
      *it_clock = itclock1 - *it_clock;
      *itgtod = is.tv_sec + 1e-6 * is.tv_usec - *itgtod ;
      return *itgtod ;
    case 2 :
      return *it_clock / ( double ) CLOCKS_PER_SEC ;
    }
  return *itgtod ;
}
