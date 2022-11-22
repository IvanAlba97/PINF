#include <math.h>
#include <stdlib.h> // exit()
#include "polis.h" // evaluapo(), leepolin(), enum {astros}
#include "funj2000.h" // ardr2ecl(), djadia()
#include "variasfu.h" // horlug(), distce()
#include "constant.h" // GRADOS, R_L_UA, R_T_UA, AS_RAD
#include "pasomeri.h" // pasmersu(), pasmerin()

double dzoroclu ( double ut, double dh ) // dh = depresion del horizonte
{ // dist. cenit. cuando la salida/puesta Luna es a UT (dias);
  ut = evaluapo (rl, ut); // auxiliar, distancia a la luna en UA
  return (90. + 34./60.)*GRADOS + dh + atan(R_L_UA/ut) - asin(R_T_UA/ut);
}


static double diszelun ( double ut, double fi, double la ) {
  double de, hl;
// distancia cenital Luna a UT (dias); fi = latitud, la = longitud
  de = evaluapo (dl, ut);
  hl = evaluapo (al, ut); // AR Luna
  hl = horlug (ut, hl, la); // HL
  return distce (fi, de, hl);
}


static double secspLun ( double x0, double f0, double x1, double f1,
						 double dho, double fi, double la,
						 const double err) {
  double x, f; // Secante; salida/puesta de la Luna

  if (f0*f1 < 0.) { // cambio de signo, luego hay corte
	do {
	  x = x1 - f1*(x1 - x0)/(f1 - f0); // Secante
	  f = dzoroclu (x, dho) - diszelun (x, fi, la);
	  if (f*f1 < 0.) {
		x0 = x1;
		f0 = f1;
	  }
	  x1 = x;
	  f1 = f;
	  } while ( fabs (f) > err );
  } else x = -1.;

  return x;
}


static double fenolun2 ( double dj, double fi, double la,
						 int fen, double dho )
{// dj = UT correspondiente a 0h Oficiales
  double dz1, dz2, de1, de2, h, pmi, pms, aux, de, dz;
//paso meridiano superior
  pms = pasmersu (104, dj, la); // entre UT=dj y UT=dj+1(+epsilon)
  dz1 = dzoroclu (pms, dho); // devuelve dz al Orto/ocaso si fuera en pms
  de1 = diszelun (pms, fi, la); // dz de la Luna en pms
  pmi = pasmerin (104, dj, la); // paso meridiano inferior
  dz2 = dzoroclu (pmi, dho); // devuelve dz al Orto/ocaso si fuera en pms
  de2 = diszelun (pmi, fi, la); // dz de la Luna en pms
  if ( fen == 1 ) { //orto
	if (pms < pmi) {// miro (pmi-1,pms) y (pmi,pms+1)
	  aux = pasmerin (104, dj-1., la);
	  dz = dzoroclu (aux, dho); // devuelve dz al Orto/ocaso si fuera en pms
	  de = diszelun (aux, fi, la); // dz de la Luna en pms
	  h = secspLun (aux, dz-de, pms, dz1-de1, dho, fi, la, AS_RAD);
	  if (h == -1. || h < dj || h > dj + 1.) { // no es en el dia
		aux = pasmersu (104, dj+1., la);
		dz = dzoroclu (aux, dho); // devuelve dz al Orto/ocaso si fuera en pms
		de = diszelun (aux, fi, la); // dz de la Luna en pms
		h = secspLun (pmi, dz2-de2, aux, dz-de, dho, fi, la, AS_RAD);
		if (h < dj || h > dj + 1.) // no es en el dia
		  h = -1.;
	  }
	}
	else // pmi < pms
	  h = secspLun (pmi, dz2-de2, pms, dz1-de1, dho, fi, la, AS_RAD);
  }
  else { // ocaso
	if (pms < pmi) {
	  h = secspLun (pms, dz1-de1, pmi, dz2-de2, dho, fi, la, AS_RAD);
	}
	else { // pmi < pms; miro (pms-1,pmi) y (pms,pmi+1)
	  aux = pasmersu (104, dj-1., la);
	  dz = dzoroclu (aux, dho); // devuelve dz al Orto/ocaso si fuera en pms
	  de = diszelun (aux, fi, la); // dz de la Luna en pms
	  h = secspLun (aux, dz-de, pmi, dz2-de2, dho, fi, la, AS_RAD);
	  if (h == -1. || h < dj || h > dj + 1.) { // no es en el dia
		aux = pasmerin (104, dj+1., la);
		dz = dzoroclu (aux, dho); // devuelve dz al Orto/ocaso si fuera en pms
		de = diszelun (aux, fi, la); // dz de la Luna en pms
		h = secspLun (pms, dz1-de1, aux, dz-de, dho, fi, la, AS_RAD);
		if (h < dj || h > dj + 1.) // no es en el dia
		  h = -1.;
	  }
	}
  }
  return h;
}


double fenolun ( double dj, double fi, double la, int fen, double dho ) {
  double aux = fenolun2 (dj, fi, la, fen, dho);

  if (aux > 0.) {
	if (aux < dj) // fenomeno en dia anterior
	  aux = fenolun2 (dj+1., fi, la, fen, dho); // miramos en el dia
	else if (aux > dj + 1.) // fenomeno dia siguiente
	  aux = fenolun2 (dj-1., fi, la, fen, dho); // miramos en dia
	if (aux < dj || aux >= dj + 1.)
	  aux = -1.;
	}
  return aux;
}


double edadluna ( double dj, double lunDic, int ano1, double huso) {
  int si, i, dia, me, an, mes, me0, me1, ano, an0; // lee
  double ho, ut, er, er0, lh, ll, pas, la;

  i = 0;
  si = 1; // True
//  lee = 0; // False
  djadia (dj, &dia, &me, &an, &ho);
  ut = dj - huso; // ut corresp. a 0h. oficiales (dj)
  pas = 1.; // un dia
  djadia (ut, &dia, &me0, &an0, &ho);
  leepolin (me0, an0, ano1); // por el huso, pueden no ser los que habia
  me1 = me0; // por febrero
  ardr2ecl (ut, evaluapo(ah,ut), evaluapo(dh,ut), &la, &lh);
  ardr2ecl (ut, evaluapo(al,ut), evaluapo(dl,ut), &la, &ll);
  er = fmod(2.*M_PI+lh-ll, 2.*M_PI);
  er0 = er;
  while (si) {
	if (fabs(er) <= 1.e-03) // < dia/100 (30 dias -> 360 grados)
	  si = 0; // False
	else if (fabs(er-er0) > 3.) { // cambio de signo -> iteraciones
	  ut = ut + pas;
	  pas = pas/24.;
	  er = er0;
	  i = 0;
	  }
	else {
	  i = i + 1;
	  if (i > 30) exit (1); // llamar a msg de error en la edad de la Luna
	  ut -= pas; //  ut - pas;
	  er0 = er;
	  djadia (ut, &dia, &mes, &ano, &ho);
	  if (ano >= ano1) {
		if (mes != me1) { // si cambiamos de mes, leemos polinomios
//		  lee = 1; // TRUE
		  leepolin (mes, ano, ano1);
		  me1 = mes;
		  }
		ardr2ecl (ut, evaluapo(ah,ut), evaluapo(dh,ut), &la, &lh);
		ardr2ecl (ut, evaluapo(al,ut), evaluapo(dl,ut), &la, &ll);
		er = fmod(2.*M_PI+lh-ll, 2.*M_PI);
		}
	  else {
		ut = lunDic; // ult. luna nuev. dic97
		si = 0; // FALSE
		}
	  }
	}
//  if (lee)
	leepolin (me, an, ano1); // los mismos que habia
  return (dj - huso) - ut;
}

