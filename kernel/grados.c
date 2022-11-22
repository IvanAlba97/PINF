#include <math.h>
#include "constant.h"

void horaminu ( double dia, int *hor, double *min, double err )
{
  *min = 24.*dia;
  *hor = (int) *min;
  *min = 60.*(*min - *hor);
  if( (60. - *min) <= err ) {
	(*hor)++;
	*min = 0.;
	}
}


void grami ( double rad, int* gr, double* mi, double err )
{ int sgn;
  double gra;

  if(rad < 0.) sgn = -1;
  else sgn = 1;
  gra = sgn*(rad/GRADOS);
  *gr = sgn*( (int) gra );
  *mi = (gra - ( (int) gra ))*60.;
  if( (60. - *mi) <= err ){
	*gr = *gr + sgn;
	*mi = 0.;
  };
}


void sigrmi ( double rad, char* sgn, int* gra, double* min, double err )
{ int sig;
  double gr;

  if (rad > 0) {
	sig = 1;
	*sgn = '+';}
  else {
	sig = -1;
	*sgn = '-';
  }
  gr = sig * (rad/GRADOS);
  *gra = (int) gr;
  *min = (gr - *gra) * 60.;
  if(60. - *min <= err ){
	*gra = *gra + 1;
	*min = 0.;
  }
}


void hodobfen ( double ut[2], double dj, double huso, int *h, double *m,
				double err)
{
  if ( ut[0] == -1. ) {
	*h = -1;
	*m = 0.;
	*(++h) = -1;
	*(++m) = 0.;
	}
  else {
	horaminu (ut[0]+huso-dj, h, m, err);
	if ( ut[1] == -1 ) {
	  *(++h) = -1;
	  *(++m) = 0.;
	  }
	else
	  horaminu (ut[1]+huso-dj, ++h, ++m, err);
	}
}
