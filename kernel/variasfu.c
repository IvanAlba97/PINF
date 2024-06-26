#include <math.h>
#include "funj2000.h" // tsvut()
#include "polis.h" // evaluapo(), enum {astros} (usa: rh, rl)
// ah, dh, rh, al, dl, rl, av, dv, rv, am, dm, rm, aj, dj, mj, as, ds, ms, ee
#include "constant.h" // R_H_UA, R_L_UA, GRADOS
#include <stdlib.h> // exit()

double semidesol ( double jd ) // semidiametro del Sol en minutos
{
  return 60.*asin( R_H_UA / evaluapo(rh, jd) )/GRADOS;
}


double semidelun ( double jd ) // semidiametro de la Luna en minutos
{
  return 60.*asin( R_L_UA / evaluapo (rl, jd) )/GRADOS;
}


double distce ( double fi, double de, double ho )
{ // dist. cenital de astro con decl. DE y horario lugar HO en latitud FI
  return acos( sin(fi)*sin(de) + cos(fi)*cos(de)*cos(ho) );
}


double angpol ( double fi, double de, double dz )
{
  dz = (cos(dz) - sin(fi)*sin(de) ) / (cos(fi)*cos(de) );
  if( fabs(dz) > 1.) // ?es posible?
	exit (1);
  return acos(dz);
}


void ardr2xyz ( double a, double d, double r,
				double *x, double *y, double *z )
{
  *x = r*cos(d)*cos(a);
  *y = r*cos(d)*sin(a);
  *z = r*sin(d);
}


static void hor2azal ( double hor, double d, double lat, double *z, double *a ) {
  double coh, sih, cod, sid, col, sil;
// de (HL, declinacion) -> (acimut astronomico, altura)
  coh = cos (hor);
  sih = sin (hor);
  cod = cos (d);
  sid = sin (d);
  col = cos (lat);
  sil = sin(lat);
  *z = atan2 ( cod*sih, sil*cod*coh-col*sid ) + M_PI; // del N hacia el E
  *a = atan2 ( col*cod*coh+sil*sid, cod*sih / sin(*z - M_PI) );
}


double horlug ( double ut, double ar, double lon ) {
// desde el meridiano superior hacia el W. Aumenta con UT
  ut = (tsvut (ut) - ar) + lon; //aux: HL = HG + long. = (TS-AR) + long.
  return fmod (40.*M_PI+ut, 2.*M_PI); // 2*PI > HL >= 0
// al ir ''demodulada'' la AR de la Luna, ut puede ser < 0 y grande
}


void ard2azalt ( double ut, double ar, double d, double lat, double lon,
				 double *az, double *a )
{// de (AR, declinacion) -> (acimut, altura)
  ut = horlug (ut, ar, lon); // aux.: ut = HL
  hor2azal (ut, d, lat, az, a); //(HL,�,latitud) -> (acimut,altura,latitud)
}// la altura A es verdadera, no tiene en cuenta la depresion del horizonte


double circunmeridiana (double ut, double lat, double lon,
								   double ar, double dec, double av) {
  double p = horlug (ut, ar, lon); // horario del lugar

  if (p > M_PI) p = 2.*M_PI - p;
  p = sin(av) + ( 1. - cos(p) )*cos(lat)*cos(dec);
  if (p > 1.)
	return 1000.;
  else
	return asin (p);
}
