#include <math.h> // fabs()
#include "reduc.h" // qalcuerp()
#include "variasfu.h" // horlug()
#include "polis.h" // evaluapo(), enum {astros} (usa: ah, al, av, am, aj, as)
// ah, dh, rh, al, dl, rl, av, dv, rv, am, dm, rm, aj, dj, mj, as, ds, ms, ee
#include "constant.h" // AS_RAD


static double horlugar ( double ut, int j, double longitud )
{ // HL entre -PI y PI
  char nom[16], mag[6]; // Reservamos memoria
  double alfa, delta;

  switch (j) {
	case (100): alfa = evaluapo (av, ut); break;
	case (101): alfa = evaluapo (am, ut); break;
	case (102): alfa = evaluapo (aj, ut); break;
	case (103): alfa = evaluapo (as, ut); break;
	case (104): alfa = evaluapo (al, ut); break;
	case (105): alfa = evaluapo (ah, ut); break;
	default: qalcuerp (j, ut, nom, mag, &alfa, &delta);
	}
  ut = horlug (ut, alfa, longitud); // 0 <= HL < 2 PI
  if (ut > M_PI) ut -= 2.*M_PI;

  return ut;
}


static double secHLpms ( double x0, double f0, double x1, double f1,
				  int j, double lon, const double err) {
  double x; // Secante; paso por el meridiano superior del lugar

  do {
	x = x1 - f1*(x1 - x0)/(f1 - f0); // Secante
	x0 = x1;
	f0 = f1;
	x1 = x;
	f1 = horlugar (x, j, lon);
	} while ( fabs (f1) > err );
  return x;
}


static double secHLpmi ( double x0, double f0, double x1, double f1,
				  int j, double lon, const double err) {
  double x; // Secante; paso por el meridiano inferior del lugar

  do {
	x = x1 - f1*(x1 - x0)/(f1 - f0); // Secante
	x0 = x1;
	f0 = f1;
	x1 = x;
	if ( ( f1 = horlugar (x, j, lon) ) > 0.) // -PI < horlugar <= PI
	  f1 -= M_PI;
	else
	  f1 += M_PI;
	} while ( fabs (f1) > err );
  return x;
}


double pasmerin ( int j, double ut, double lon) {
  double t, ut1, hL1, ut0, hL0 = horlugar (ut, j, lon);
// el horario del lugar aumenta aprox. linealmente con el tiempo
  t = (M_PI - hL0)/(2.*M_PI); // PI = HL0 + (2*PI/1dia)*(t dias)
  ut0 = ut + t; // dia juliano aprox. paso meridiano inferior
  if ( ( hL0 = horlugar (ut0, j, lon) ) > 0.) // -PI < horlugar <= PI
	hL0 -= M_PI;
  else
	hL0 += M_PI;
  ut1 = ut0 + MIN_DIA;
  if ( ( hL1 = horlugar (ut1, j, lon) ) > 0.) // -PI < horlugar <= PI
	hL1 -= M_PI;
  else
	hL1 += M_PI;
  return secHLpmi (ut0, hL0, ut1, hL1, j, lon, AS_RAD);
}

// calcula paso meridiano entre ut y ut+1. Para la Luna puede dar >ut+1
double pasmersu ( int j, double ut, double lon) {
  double t1, hL1, t0, hL0 = horlugar (ut, j, lon);
// el horario del lugar aumenta aprox. linealmente con el tiempo
  if (hL0 < 0.) // HL = 0 = HL0 + (2*PI/1dia)*(t dias)
	t0 = ut  - hL0/(2.*M_PI);
  else // HL = 2*PI = HL0 + (2*PI/1dia)*(t dias)
	t0 = ut + 1. - hL0/(2.*M_PI);
  hL0 = horlugar (t0, j, lon);
  t1 = t0 + MIN_DIA;
  hL1 = hL0 + (2.*M_PI)*MIN_DIA;
  return secHLpms (t0, hL0, t1, hL1, j, lon, AS_RAD);
}
