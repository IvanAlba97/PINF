#include <math.h> // sin(), cos(), tan(), asin()
#include "reduc.h" // qalcuerp()
#include "variasfu.h" // semidesol(), semidelun(), horlug()
#include "polis.h" // evaluapo() + enum {astros} (usa: rh, rl, rv, rm)
// ah, dh, rh, al, dl, rl, av, dv, rv, am, dm, rm, aj, dj, mj, as, ds, ms, ee
#include "constant.h" // GRADOS, AS_RAD, R_T_UA


double refracci ( double a ) { // a = altura aparente
  double cot;

  if ( a >= 5.*GRADOS) {
	cot = 1./tan(a);
	return AS_RAD*(58.32 - 0.0668*cot*cot)*cot;
	}
  else
	return (34./60.)*GRADOS; // estandar: 34'
}


double paralaje ( int n, double ut, double a ) { // a = altura aparente
  double dis;

  if (n == 1)
	dis = 0.;
  else {
	if (n == 2)
	  dis = evaluapo (rv, ut); // Venus
	else if (n == 3)
	  dis = evaluapo (rm, ut); // Marte
	else if (n <= 5)
	  dis = evaluapo (rh, ut); // Sol
	else
	  dis = evaluapo (rl, ut); // Luna
	dis = cos(a)*asin( R_T_UA / dis );
	}
  return dis;
}


double semidiam ( int n, double jd) {
  double au;

  if (n == 4)
	au = (semidesol (jd) /60.)*GRADOS;
  else if (n == 5)
	au = -(semidesol (jd) /60.)*GRADOS;
  else if (n == 6)
	au = (semidelun (jd) /60.)*GRADOS;
  else if (n == 7)
	au = -(semidelun (jd) /60.)*GRADOS;
  else
	au = 0.;
  return au;
}


double latpolar ( double ut, double a, double lon ) {
  char mg[6], nom[16]; // reservamos memoria: qalcuerp() los modifica
  int n;
  double fi, ar, de, t, c;

  qalcuerp (11, ut, nom, mg, &ar, &de); // 11 == Polaris
  t = horlug (ut, ar, lon); // horario del lugar
  if (t != 0.) {
	if ( cos(t) == 0. )
	  t += AS_RAD; // evita denominador 0 en el polo
	fi = a;
	do {
	  c = ( sin(a) - sin(fi)*sin(de) - cos(fi)*cos(de)*cos(t) ) /
		  ( cos(fi)*sin(de) - sin(fi)*cos(de)*cos(t) );
	  fi += c;
	} while (fabs(c) > 3.e-06); // a la centesima de minuto de arco
  }
  else
	fi = de + a - M_PI/2.; // paso meridiano
  return fi;
}


double circunmeridiana2 (double ut, double lat, double lon,
								   double ar, double dec, double av) {
  double c, cfi, cp;
  double sfi = sin (lat);
  double sde = sin (dec);
  double cde = cos (dec);
  double sav = sin (av);
  double p = horlug (ut, ar, lon); // horario del lugar

  if (p > M_PI) p = 2.*M_PI - p;
  cp = cos (p);
  do {
	cfi = cos (lat);
	c = -(sfi*sde - sav + cfi*cde*cp)/(cfi*sde - sfi*cde*cp);
	sfi += c;
	lat = asin (sfi);
  } while (fabs(c) > 5.e-08); // a la centesima de segundo de arco

  return lat;
}
