#include <math.h>
#include "constant.h"

#define J_2000 2451545.0


static void nutaprox ( double ut, double *dpsi, double *deps ) {
  double rp, rv, t = ut - J_2000;

  rp = (125.0 - 0.05295*t)*GRADOS;
  rv = (200.9 + 1.97129*t)*GRADOS;
  *dpsi = -( 0.0048*sin(rp) + 0.0004*sin(rv) )*GRADOS; // ! лн
  *deps =  ( 0.0026*cos(rp) + 0.0002*cos(rv) )*GRADOS; // ! ло
}


static double oblecl ( double x )
{// oblicuidad media de la ecliptica cuando x se expresa en SJ
  return AS_RAD*( 84381.448 - (46.8150 + (0.00059 - 0.001813*x)*x)*x );
}


double tocent ( double jd )
{// SJ desde J2000.0 hasta la fecha t=jd
   return (jd - J_2000)/36525.; // J_2000 = 2451545.0;
}

static void preceang (double t, double *set, double *z, double *the)
{
  *set = AS_RAD*(2306.2181 + (0.30188 + 0.017998*t)*t)*t;
  *z =   AS_RAD*(2306.2181 + (1.09468 + 0.018203*t)*t)*t;
  *the = AS_RAD*(2004.3109 - (0.42665 + 0.041833*t)*t)*t;
}


void prenut ( double t, double *mpn ) {
  int i, j, k;
  double dps, dep;
  double set, z, the, ep0, eps, se0, pre[3][3], nut[3][3], pn[3][3];
  double cse, sse, cth, sth, cz, sz, cdp, sdp, cep, sep, ce0;

  nutaprox (t, &dps, &dep);
  t = tocent (t);
  preceang (t, &set, &z, &the);
  ep0 = oblecl (t);
  cse = cos(set);
  sse = sin(set);
  cth = cos(the);
  sth = sin(the);
  cz = cos(z);
  sz = sin(z);
  pre[0][0] = cse*cth*cz - sse*sz;
  pre[0][1] = -(cth*cz*sse + cse*sz);
  pre[0][2] = -(cz*sth);
  pre[1][0] = cz*sse + cse*cth*sz;
  pre[1][1] = cse*cz - cth*sse*sz;
  pre[1][2] = -(sth*sz);
  pre[2][0] = cse*sth;
  pre[2][1] = -(sse*sth);
  pre[2][2] = cth;
  eps = ep0 + dep;
  cdp = cos(dps);
  sdp = sin(dps);
  cep = cos(eps);
  sep = sin(eps);
  ce0 = cos(ep0);
  se0 = sin(ep0);
  nut[0][0] = cdp;
  nut[0][1] = -(sdp*ce0);
  nut[0][2] = -(sdp*se0);
  nut[1][0] = sdp*cep;
  nut[1][1] = cdp*cep*ce0 + sep*se0;
  nut[1][2] = cdp*cep*se0 - sep*ce0;
  nut[2][0] = sdp*sep;
  nut[2][1] = cdp*sep*ce0 - cep*se0;
  nut[2][2] = cdp*sep*se0 + cep*ce0;
  for (i = 0; i < 3; i++) // producto de matrices
	for (j = 0; j < 3; j++) {
	  pn[i][j] =0.;
	  for (k = 0; k < 3; k++)
		pn[i][j] += nut[i][k] * pre[k][j];
	  }
  for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	  *(mpn+3*i+j) = pn[i][j];
}


static double dsol2sid ( double sj )
{// dia solar medio en dias sidereos medios; sj = siglos jul. desde J2000
  return 1.002737909350795 + (5.9006e-11 - 5.9e-15*sj)*sj;
}


static double gmst0hut ( double sj )
{// seg. de TS medio en Greenwich a 0 h. UT; sj = siglos jul. desde J2000
  return 24110.54841 + (8640184.812866 + (0.093104 - 6.2e-6*sj)*sj)*sj;
}


static double tsmut ( double ut ) {// tiempo sidereo medio de un UT (dias julianos)
  double sj, a1, a2, fra = (ut - 0.5) - (long) (ut - 0.5); //fraccion de dia

  sj = tocent (ut - fra); // siglos julianos (0h) desde J2000.0
  a1 = ( 15.*gmst0hut (sj) )*AS_RAD; // rad. de TSM Greenwich a 0 horas UT
  a2 = fra*dsol2sid (sj); // fracc. de dia solar medio en dias sidereos medios
  a1 += (2.*M_PI)*a2; // radianes de TSM en Greenwich a la hora pedida

  return fmod(a1, 2.*M_PI);
}


double tsvut ( double ut ) {
  double dps, dep, e0 = oblecl ( tocent (ut) );

  nutaprox ( ut, &dps, &dep );
  return tsmut (ut) + dps*cos (e0 + dep);
}


double diajul ( int giorno, int mese, int anno, double ora ) {
  long iy, im, ib, k1, k2, k3;

  if(mese <= 2){
	iy = anno - 1;
	im = mese + 12;}
  else{
	iy = anno;
	im = mese;}
  if(anno > 1582)
	ib = iy/400 - iy/100;
  else{
	ib = -2;
	if(anno == 1582)
	  if(mese > 10)
		ib = iy/400 - iy/100;
	  else if( (mese == 10) && (giorno >= 15) )
		ib = iy/400 - iy/100;
	}
  k1 = (long) (365.25*iy);
  k2 = (long) ( 30.6001*(im + 1) );
  k3 = k1 + k2 + ib - 679004 + giorno;

  return 2400000.5 + k3 + ora/24.;
}


//******** solo las usa la funcion edadluna() en ORTOCALU.CPP

void ardr2ecl ( double ut, double a, double d, double *la, double *lo ) {
  double dps, dep, e;
// de (AR,declinacion) a (latitud, longitud) eclipticas
  nutaprox ( ut, &dps, &dep );
  e = oblecl ( tocent (ut) ) + dep;
  *lo = atan2 ( cos(e)*cos(d)*sin(a) + sin(e)*sin(d), cos(d)*cos(a) );
  *la = asin ( -sin(e)*cos(d)*sin(a) + cos(e)*sin(d) );
}


void djadia ( double dj, int *dia, int *mes, int *anno, double *hora ) {
  long ia, ib, ik, id, ie, ig;

  *hora = dj + 0.5;
  ia = (long) *hora;
  *hora = (*hora - ia)*24.;
  if(ia < 2299161L)
	ik = ia + 1524;
  else{
	ib = (long) ( (ia - 1867216.25)/36524.25 );
	ik = 1525 + ia + ib - (long) (ib/4.);
  }
  id = (long) ( (ik - 122.1)/365.25 );
  ie = (long) ( 365.25*id );
  ig = (long) ( (ik - ie)/30.6001 );
  *dia = ik - ie - (long) (30.6001*ig);
  *mes = ig - 1 - 12*( (long) (ig/14.) );
  *anno = id - 4715 - (long) ( (7 + *mes)/10. );
}
