#include <stdio.h>  // ficheros...
#include <stdlib.h> // exit()
/*#include <conio.h>*/  // getch()
#include "polis.h" // enum {astros}
/*#include <Dialogs.hpp>*/
//----------------------- GRADO+1 DE LOS POLINOMIOS ---------------------
const int gee = 4;
const int gah = 6; const int gdh = 5; const int grh = 2;
const int gal =28; const int gdl =28; const int grl =12;
const int gav = 8; const int gdv = 8; const int grv = 3;
const int gam = 7; const int gdm = 6; const int grm = 3;
const int gaj = 5; const int gdj = 5; const int gmj = 2;
const int gas = 5; const int gds = 4; const int gms = 2;
//---------------------------------------------------------------------

static struct {
  double jdP, ee[gee],
		 ah[gah], dh[gdh], rh[grh],
		 al[gal], dl[gdl], rl[grl],
		 av[gav], dv[gdv], rv[grv],
		 am[gam], dm[gdm], rm[grm],
		 aj[gaj], dj[gdj], mj[gmj],
		 as[gas], ds[gds], ms[gms];
} r;
static double dT0, dT, pen, ord;
static int lor;


static double horner ( double s[], int j, double t ) {
  int i;
  double au = s[j]*t;

  for (i = j-1; i > 0; i--)
	au = (au + s[i])*t;
  return au + s[0];
}


static double dehorn ( double s[], int j, double t ) {
  int i;
  double au = j*s[j]*t;

  for (i = j - 1; i > 1; i--)
	au = (au + i*s[i])*t;
  return au + s[1];
}


static int numregis ( int mes, int ano, int ano0 )
{
  dT = (ano - ano0) + dT0; // global: por si cambia el ano
// --- OJO, 1er registro con preferencias, luego ENE98
  return 1 + mes + (ano - ano0)*12;
}


void leepoli0 ( double *lunDic, int *ano0, int *anofin ) {
  FILE *fic; // estructura definida en stdio.h

  pen = 2./32.; // (1 - (-1))/(31 + 1); 32 dias proyectados en [-1,1]
// ------ Longitud del registro
  lor = 8*(gee + gah + gdh + grh + gal + gdl + grl + gav + gdv + grv +
		   gam + gdm + grm + gaj + gdj + gmj + gas + gds + gms + 1    );
  if ( (fic = fopen ("_efemeri.des", "rb") ) == NULL ) { // rb = read binary
    printf("Error al abrir archivo _efemeri.des");
        exit(EXIT_FAILURE);
	}
  fseek (fic, 0, SEEK_SET); // posicionamos el registro a leer
  fread (&r, lor, 1, fic); // lee 'lor' bytes a partir de &jdP
  fclose (fic);
  *ano0 = (int) r.ee[0];
  *anofin = (int) r.ee[1];
  dT0 = r.ah[1];
  *lunDic = r.jdP; // edad Luna ENE necesita DIC ano anterior
}


void leepolin ( int mes, int ano, int ano0 ) {
  long pos;
  FILE *fic;

  pos = lor; // para no pasarme en la multiplicacion posterior
  pos = pos*( numregis (mes, ano, ano0) - 1 );
  if ( ( fic = fopen ("_efemeri.des", "rb") ) == NULL ) { // rb = read binary
    /*ShowMessage("Error al abrir archivo _efemeri.des");*/
        exit (EXIT_FAILURE);
  }
  fseek (fic, pos, SEEK_SET); // posicionamos el registro desde el origen
  fread (&r, lor, 1, fic); // lee 'lor' bytes a partir de &jdP
  fclose (fic);
  ord = -(1. + pen*r.jdP);
}


double evaluapo ( int qal, double ut ) {
  double x, tt = pen*(ut + dT/86400.) + ord; // dias jul. TT en [-1,1]

  if      (ah == qal) x = horner (r.ah, gah-1, tt);
  else if (dh == qal) x = horner (r.dh, gdh-1, tt);
  else if (rh == qal) x = horner (r.rh, grh-1, tt);
  else if (al == qal) x = horner (r.al, gal-1, tt);
  else if (dl == qal) x = horner (r.dl, gdl-1, tt);
  else if (rl == qal) x = horner (r.rl, grl-1, tt);
  else if (av == qal) x = horner (r.av, gav-1, tt);
  else if (dv == qal) x = horner (r.dv, gdv-1, tt);
  else if (rv == qal) x = horner (r.rv, grv-1, tt);
  else if (am == qal) x = horner (r.am, gam-1, tt);
  else if (dm == qal) x = horner (r.dm, gdm-1, tt);
  else if (rm == qal) x = horner (r.rm, grm-1, tt);
  else if (aj == qal) x = horner (r.aj, gaj-1, tt);
  else if (dj == qal) x = horner (r.dj, gdj-1, tt);
  else if (mj == qal) x = horner (r.mj, gmj-1, tt);
  else if (as == qal) x = horner (r.as, gas-1, tt);
  else if (ds == qal) x = horner (r.ds, gds-1, tt);
  else if (ms == qal) x = horner (r.ms, gms-1, tt);
  else                x = horner (r.ee, gee-1, tt);
  return x;
}


double derivapo ( int qal, double ut ) {
  double x, tt = pen*(ut + dT/86400.) + ord; // dias jul. TT en [-1,1]

  if      (ah == qal) x = pen*dehorn (r.ah, gah-1, tt);
  else if (dh == qal) x = pen*dehorn (r.dh, gdh-1, tt);
  else if (rh == qal) x = pen*dehorn (r.rh, grh-1, tt);
  else if (al == qal) x = pen*dehorn (r.al, gal-1, tt);
  else if (dl == qal) x = pen*dehorn (r.dl, gdl-1, tt);
  else if (rl == qal) x = pen*dehorn (r.rl, grl-1, tt);
  else if (av == qal) x = pen*dehorn (r.av, gav-1, tt);
  else if (dv == qal) x = pen*dehorn (r.dv, gdv-1, tt);
  else if (rv == qal) x = pen*dehorn (r.rv, grv-1, tt);
  else if (am == qal) x = pen*dehorn (r.am, gam-1, tt);
  else if (dm == qal) x = pen*dehorn (r.dm, gdm-1, tt);
  else if (rm == qal) x = pen*dehorn (r.rm, grm-1, tt);
  else if (aj == qal) x = pen*dehorn (r.aj, gaj-1, tt);
  else if (dj == qal) x = pen*dehorn (r.dj, gdj-1, tt);
  else if (mj == qal) x = pen*dehorn (r.mj, gmj-1, tt);
  else if (as == qal) x = pen*dehorn (r.as, gas-1, tt);
  else if (ds == qal) x = pen*dehorn (r.ds, gds-1, tt);
  else if (ms == qal) x = pen*dehorn (r.ms, gms-1, tt);
  else                x = pen*dehorn (r.ee, gee-1, tt);
  return x;
}
