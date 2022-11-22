#include <math.h>    // fabs()
#include "variasfu.h"// horlug(), distce(), angpol()
#include "polis.h"   // evaluapo(), enum {astros} (usa: ah, dh)
// ah, dh, rh, al, dl, rl, av, dv, rv, am, dm, rm, aj, dj, mj, as, ds, ms, ee
#include "constant.h"// NAUTICO, CIVIL, ORTO_H, AS_RAD, MIN_DIA

enum { pcn, pcc, ort, ori, oci, oca, fcc, fcn };

static double distzsol ( double ut, double fi, double la) {
  double de = evaluapo (dh, ut);
  double ar = evaluapo (ah, ut);
  return distce ( fi, de, horlug (ut, ar, la) );
}


static double dzfensol ( int fen, double dho )
{
  if      ( fen == pcn || fen == fcn) return dho + NAUTICO;
  else if ( fen == pcc || fen == fcc) return dho + CIVIL;
  else if ( fen == ort || fen == oca) return dho + ORTO_H;
  else // if (fen == ori || fen == oci)
	return dho + ORTO_H - (32./60.)*GRADOS; // 32' de diametro solar
}


static int tipofenH ( double dec, double fi, double dz) {
  int s1, s2, s3, s4; // dec = declinacion Sol al mediodia en el huso
// Condiciones groseras para determinar SI/NO/CRITICO
  if (fi > 0.) { // los posibles valores dec. sol => s3 siempre 0 (.FALSE.)
	s1 = dec >= (M_PI - dz - fi + 0.5*GRADOS); // SI=> sol por encima
	s3 = dec <= (fi - dz - 0.5*GRADOS); // SI=> astro (no sol) por debajo
	if ( !(s1 || s3) ) {
	  s2 = dec >= (M_PI - dz - fi - 0.5*GRADOS); // SI=> critico
	  s4 = dec <= (fi - dz + 0.5*GRADOS); // SI=> critico
	  }
	}
  else {
	s1 = dec <= (dz - fi - M_PI - 0.5*GRADOS);
	s3 = dec >= (dz + fi + 0.5*GRADOS);
	if ( !(s1 || s3) ) {
	  s2 = dec <= (dz - fi - M_PI + 0.5*GRADOS); // SI=> critico
	  s4 = dec >= (dz + fi - 0.5*GRADOS); // SI=> critico
	  }
	}
  if (s1 || s3)
	return -1; // Claramente NO hay fenomeno
  else if (s2 || s4) // casos criticos
	return 0;
  else // Claramente SI hay fenomeno
	return 1;
}


static double almucant ( int j, double ut,
						 double lat, double lon, double dz0 )
{
  if (j == 105)
	return dz0 - distzsol (ut, lat, lon);
  else
	return 0.; // incompleta. Solo para el sol
}


static double secAlmuc ( double x0, double f0, double x1, double f1, int j,
						 double lat, double lon, double dz0,
						 const double err) {
  double x, f; // Secante

  do {
	x = x1 - f1*(x1 - x0)/(f1 - f0); // Secante
	f = almucant (j, x, lat, lon, dz0);
	if (f*f1 < 0.) { // para garantizar el corte en el dia
	  x0 = x1;
	  f0 = f1;
	}
	x1 = x;
	f1 = f;
	} while ( fabs (f) > err );
  return x;
}


static double iterasol ( double jd, double fi, double la, double dec,
						 int sgn, double dz) { // Nunca es critico
  double u0, u1, u3, a0, a1;

  u0 = jd + 0.5 + (sgn*angpol (fi, dec, dz) - la)/(2.*M_PI);
  a0 = almucant (105, u0, fi, la, dz);
  if ( a0 == 0. ) // poco probable
	u3 = u0;
  else { // Nunca es critico; u0 es buena aproximacion del fenomeno
	u1 = u0 + 1./60./60./24.; // cerquita, para 1a. secante ~= tangente
	a1 = almucant (105, u1, fi, la, dz);
	u3 = secAlmuc (u0, a0, u1, a1, 105, fi, la, dz, AS_RAD);
	}
  return u3;
}


static void buscasol ( double u0, double fi, double la, int sgn, double dz,
					   double *ut) { // casos criticos. Busqueda al min
  const double st = 0.85*MIN_DIA; // st < 1/60/24
  double dif0, u1, t0 = 0., dif1 = -1.; // para la primera comprobacion

  do {
	u1 = u0 + t0;
	dif0 = dif1;
	dif1 = sgn*almucant (105, u1, fi, la, dz);// sgn sistematiza busqueda
	if (dif1 == 0.) { // casualidad poco probable
	  *(ut++) = u1;
	  t0 += 22./24.; // por si hay doble
	  }
	else if (dif1 < 0. && dif0 > 0.) { // cambio de signo. Hay corte
	  *(ut++) = secAlmuc (u1-st, dif0, u1, dif1, 105, fi, la, dz, AS_RAD);
	  t0 += 22./24.; // por si hay doble
	  }
	else
	  t0 += st;
	} while (t0 < 1.); // buscamos solo un dia
}


void fenosol ( double di, double fi, double la, double zh, double dho,
			   int fen, double *ut) {
  int hoy, sgn; // sgn permite buscar igual ortos y ocasos
  double t, jd, u0, d0, dz = dzfensol (fen, dho);

  *ut = -1.;
  *(ut+1) = -1.;
  if ( fen < 4 ) sgn = -1; // pcn, pcc, ort, ori
  else           sgn =  1; // oci, oca, fcc, fcn
  d0 = evaluapo (dh, di+0.5-zh); // decl. Sol al mediodia en el huso
  switch ( tipofenH (d0, fi, dz) ) { // Estimacion grosera SI/NO/critico
	case (-1): break; // Claramente NO hay fenomeno
	case (0): buscasol (di-zh, fi, la, sgn, dz, ut); // Caso critico
			  break; // Puede haber 0, 1 o 2 fenomenos
	default: // Claramente SI hay fenomeno
	  jd = di; // para no machacar di
	  hoy = 2; // contador de oscilacion, que puede darse con un huso absurdo
	  do { //while (hoy): por si nos salimos del dia al meter zona horaria
		t = iterasol (jd, fi, la, d0, sgn, dz);//no considera zona horaria
		u0 = t + zh - di; // vemos si, con la zona horaria, estamos en el dia
		if ( u0 < 0. || u0 > 1.) { // fuera del dia oficial
		  jd = di - u0/fabs(u0); // nos vamos al dia correcto
		  d0 = evaluapo (dh, jd+0.5-zh); // decl. Sol al mediodia en el huso
		  hoy--; // repetimos el calculo
		}
		else { // ha habido fenomeno
		  *ut = t;
		  if (u0 < 1./24. || u0 > 23./24.) {// ?doble por zona horaria?
			if (u0 < 1./24.)
			  jd += 1.; // miro al dia siguiente al que acabo de mirar
			else // u0 > 23./24.
			  jd -= 1.; // miro al dia anterior al que acabo de mirar
			d0 = evaluapo (dh, jd+0.5-zh); // decl. Sol al mediodia en el huso
			t = iterasol (jd, fi, la, d0, sgn, dz);
			u0 = t + zh - di; // para ver si, con el huso, estamos en el dia
			if ( u0 > 0. && u0 < 1.) // en del dia
			  *(++ut) = t;
		  }
		  hoy = 0; // .FALSE.
		}
	  } while (hoy);
	} // fin switch
}
