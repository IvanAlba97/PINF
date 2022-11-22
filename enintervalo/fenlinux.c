/********************************************************************\

|***           Real Instituto y Observatorio de la Armada         ***|

\********************************************************************/


#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <math.h>


struct Tcomsol {

	int    hpm;			// hora paso meridiano

	int    hpn[2];

	int    hpc[2];

	int    hss[2];

	int    hps[2];

	int    hsi[2];

	int    hpi[2];

	int    hfc[2];

	int    hfn[2];

	double ssd;

	double mpm;          // minutos paso meridiano

	double mpn[2];

	double mpc[2];

	double mss[2];

	double mps[2];

	double msi[2];

	double mpi[2];

	double mfc[2];

	double mfn[2];

	int    ssg[2];

	int    sig[2];

	int    psg[2];

	int    pig[2];

	double ssm[2];

	double sim[2];

	double psm[2];

	double pim[2];

	int    bpm;			// bandera de paso por el meridiano

	int    gra;

	double mia;

	char   cul;

};

static void strcatAcimut (char*, int, float, int, float);
static void lineaAcimut (char*, char*, int, float, int, float, int, float, int, float);
void inicializar (int latgra, int latmin, int latseg, int longra, int lonmin, int lonseg, int horut, double elev, char latsig, char lonsig);
struct TMeridiano* pasoMeridiano (int nas);
static void solybari ( double ut, double *b_e );
double derivapo ( int qal, double ut );
static double dehorn ( double s[], int j, double t );
static void qalestre ( int i, double ut, char *nom, char *mag, double *ar, double *de );
void ardr2xyz ( double a, double d, double r, double *x, double *y, double *z );
static double magnitud ( int j, double ut );
void qalcuerp ( int i, double ut, char *nom, char *mag, double *ar, double *de );
static double horlugar ( double ut, int j, double longitud );
double pasmersu ( int j, double ut, double lon);
static double horner ( double s[], int j, double t );
double evaluapo ( int qal, double ut );
double semidesol ( double jd );
struct Tcomsol* c_fensol ( void );
void prenut ( double t, double *mpn );
static void nutaprox ( double ut, double *dpsi, double *deps );
static double oblecl ( double x );
static void preceang (double t, double *set, double *z, double *the);
double tocent ( double jd );
static void redaprox ( double *ar, double *de, double arp, double dep, double arv, double dev, double *pn, double *b,double dt);
double tsvut ( double ut );                                           
static double tsmut ( double ut );
static double gmst0hut ( double sj );
static double dsol2sid ( double sj );
double horlug ( double ut, double ar, double lon );
void acimaltu ( int i, double ut, double lat, double lon, char *nom, char *mag, double *az, double *a );
static void hor2azal ( double hor, double d, double lat, double *z, double *a );                                
void ard2azalt ( double ut, double ar, double d, double lat, double lon, double *az, double *a );
void horaminu ( double dia, int *hor, double *min, double err );                                 
void fenosol ( double di, double fi, double la, double zh, double dho, int fen, double *ut);
static double dzfensol ( int fen, double dho );
static int tipofenH ( double dec, double fi, double dz);
static void buscasol ( double u0, double fi, double la, int sgn, double dz, double *ut);
static double almucant ( int j, double ut, double lat, double lon, double dz0 );
static double distzsol ( double ut, double fi, double la);
double distce ( double fi, double de, double ho );
static double secAlmuc ( double x0, double f0, double x1, double f1, int j, double lat, double lon, double dz0, const double err);
static double iterasol ( double jd, double fi, double la, double dec, int sgn, double dz);
double angpol ( double fi, double de, double dz );                                                                      void hodobfen ( double ut[2], double dj, double huso, int *h, double *m, double err);
static void igualahm ( int *h, double *m, int *hora, double *minuto );
static void acimusol ( int ho[2], double ut[2], int *ssg, double *ssm);
void grami ( double rad, int* gr, double* mi, double err );
          
/*  Para tener acceso siempre a los fenomenos, aun si no hay que calcularlos */

static Tcomsol* comsol;



/*****************************************************\

|*** Opcion 'Fenomenos de Sol'                     ***|

\*****************************************************/


int main(void)
{
   int latgra, latmin, latseg, longra, lonmin, lonseg, horut;
   double elev;
   char latsig, lonsig;
   
   char *data = (char *) calloc(sizeof(char), 40);
   
   printf("%s%c%c\n","Content-Type/html;charset=iso-8859-1",13,10);
   printf("<TITLE>Resultados de orto y ocaso</TITLE>\n");
   printf("<H3>Resultados de orto y ocaso</H3>\n");
   data = getenv("QUERY_STRING");
   if(data == NULL)
      printf("<P>Error al pasar los datos al programa.");
   else if(sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&elev=%lf&horut=%i",&latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &elev, &horut) != 10)
   	printf("<P>Error al pasar los datos al programa.");
   else
      if ((latgra < 0) || (latgra > 90))
         printf("<P>Los grados deben estar entre 0º y 90º.");
      if ((latmin < 0) || (latmin > 59))
         printf("<P>Los minutos deben estar entre 0' y 59'.");
      if ((latseg < 0) || (latseg > 59))
         printf("<P>Los segundos deben estar entre 0'' y 59''.");
      if ((longra < 0) || (longra > 180))
         printf("<P>Los grados deben estar entre 0º y 180º.");
      if ((lonmin < 0) || (lonmin > 59))
         printf("<P>Los minutos deben estar entre 0' y 59'.");
      if ((lonseg < 0) || (lonseg > 59))
         printf("<P>Los segundos deben estar entre 0'' y 59''.");   
      if ((latsig != 'N') || (latsig != 'S'))
         printf("<P>La latitud debe ser Norte o Sur.");
      if ((lonsig != 'O') || (lonsig != 'E'))
         printf("<P>La longitud debe ser Este u Oeste.");
      if ((elev < 0) || (elev > 9999.9))
         printf("<P>La elevacion debe estar entre 0 m y 9999.9 m");
      if ((latgra == 90) && ((latmin > 0) || (latseg > 0)))
         printf("<P>La latitud debe ser menor o igual a 90º"); 
      if ((longra == 180) && ((lonmin > 0) || (lonseg > 0)))
         printf("<P>La longitud debe ser menor o igual a 180º");
   
      inicializar(latgra, latmin, latseg, longra, lonmin, lonseg, horut, elev, latsig, lonsig); 
      
      free(data);
      
      return 0;
}



void inicializar (int latgra, int latmin, int latseg, int longra, int lonmin, int lonseg, int horut, double elev, char   		latsig, char lonsig) {

	char *cad = (char *) calloc(sizeof(char, 80);

	
        int acimutes = 0;	/* por defecto, tomamos que no hay acimutes*/



        /* Recalcular datos si es necesario*/


		comsol = c_fensol ();





        /* Si se observa el paso por el meridiano*/

	if (comsol->bpm) {

		printf("<H5>Horas oficiales de:</H5>");



		sprintf (cad, "-Paso meridiano lugar: %2ih %4.1lfm", comsol->hpm, comsol->mpm);

		printf("<P>%s", cad);



		sprintf (cad, "     Altura verdadera: %2iº %4.1lfm", comsol->gra, comsol->mia);

                printf("<P>%s", cad);



		sprintf (cad, "     Culminacion.....: %s",

				 comsol->cul == 'N' ? "Norte" : "Sur");

                printf("<P>%s", cad);



		sprintf (cad, " Semidiametro........: %4.1lf'", comsol->ssd);

                printf("<P>%s", cad);


	}



        /* Comenzamos a chequear los casos negativos*/



	if (comsol->hss[0] == 99) {

           printf("<P>          No hay fenomenos.");

           printf( "<P>Sol siempre por encima del horizonte.");

	}

	else if (comsol->hpc[0] == 99) {

           printf("<P>     No hay fenomenos.");

           printf("<P>Crepusculo civil continuo.");

	}

	else if (comsol->hpn[0] == 88) {

           printf("<P>             No hay fenomenos.");

           printf("<P>Sol siempre con distancia cenital z > 102º.");

	}

	else if (comsol->hpn[0] == 99) {

           printf("<P>      No hay fenomenos.");

           printf("<P>Crepusculo nautico continuo.");

	}

        /********** Fin de los casos negativos *************/

	else {



        /* Si antes no puse este texto, lo pongo ahora*/

		if (!comsol->bpm)

			printf("<P>Horas oficiales de:");



		strcatHora (cad, "-Principio crep. nautico: ", comsol->hpn, comsol->mpn, 2);

                printf("<P>%s", cad);



		strcatHora (cad, "-Principio crep. civil..: ", comsol->hpc, comsol->mpc, 2);

		printf("<P>%s", cad);



		strcatHora (cad, "-Salida.................: ", comsol->hss, comsol->mss, 2);

                printf("<P>%s", cad);



		strcatHora (cad, "-Puesta.................: ", comsol->hps, comsol->mps, 2);

                printf("<P>%s", cad);



		strcatHora (cad, "-Fin crepusculo civil...: ", comsol->hfc, comsol->mfc, 2);

                printf("<P>%s", cad);



		strcatHora (cad,"-Fin crepusculo nautico.: ", comsol->hfn, comsol->mfn, 2);

                printf("<P>%s", cad);



		// Si hay salida o puesta, muestro el boton 'acimutes'

		if (comsol->hss[0] != -1 || comsol->hps[0] != -1)

			acimutes = 1;

	}



	if (acimutes) {

           	printf("\n<H5>Acimutes al orto y al ocaso</H5>\n");
                printf( "            <U>Limbo superior</U>          <U>Limbo inferior</U>\n");
                lineaAcimut (cad, "Salida:   ", comsol->ssg[0], comsol->ssm[0], comsol->hss[0], comsol->mss[0], comsol->sig[0], comsol->sim[0], comsol->hsi[0], comsol->msi[0]);

   		printf("<P>%s", cad);
                if ((comsol->hss[0] != -1 && comsol->hss[1] != -1) || (comsol->hsi[0] != -1 && comsol->hsi[1] != -1)){

                   lineaAcimut (cad, "     y    ", comsol->ssg[1], comsol->ssm[1], comsol->hss[1], comsol->mss[1],

			  comsol->sig[1], comsol->sim[1], comsol->hsi[1], comsol->msi[1]);

                          printf("<P>%s", cad);

                }
                // Acimutes de puesta 1er fenomeno

                lineaAcimut (cad, "Puesta:   ", comsol->psg[0], comsol->psm[0], comsol->hps[0], comsol->mps[0],

		  comsol->pig[0], comsol->pim[0], comsol->hpi[0], comsol->mpi[0]);

                  printf("<P>%s",cad);
         
          	// Acimutes de puesta 2º fenomeno, si los hay

                if ((comsol->hps[0] != -1 && comsol->hps[1] != -1) || (comsol->hpi[0] != -1 && comsol->hpi[1] != -1)){

                   lineaAcimut (cad, "     y    ", comsol->psg[1], comsol->psm[1], comsol->hps[1], comsol->mps[1],

			  comsol->pig[1], comsol->pim[1], comsol->hpi[1], comsol->mpi[1]);

                   printf("<P>%s", cad);

                }

	}

        free(cad);

}


/*****************************************************\

|*** Para escribir cada una de las l¡neas del      ***|

|*** di logo de acimutes.                          ***|

\*****************************************************/



void lineaAcimut (char* dest, char* cad, int gas, float mas, int hos, float mhs,

										 int gai, float mai, int hoi, float mhi)

{	// Limbo superior

	strcpy (dest, cad);

	strcatAcimut (dest, gas, mas, hos, mhs);



	// Limbo inferior

	strcat (dest, "      ");

	strcatAcimut (dest, gai, mai, hoi, mhi);

}



/*****************************************************\

|*** Para escribir un acimut y una hora.           ***|

\*****************************************************/



void strcatAcimut (char* cad, int gra, float mig, int hor, float mih) {

	char *aux = (char *) calloc(sizeof(char), 25);



	// Si hay fenomeno

	if (hor != -1) {

		sprintf (aux, "%3iº%4.1f' a %2ih %2.0fm", gra, mig, hor, mih);

		strcat (cad, aux);

	}

	// Si no hay fenomeno

	else

		strcat (cad, "       -----       ");

        free(aux);

}

/****************************************************/
/*       c_fensol()                                */
/***************************************************/

struct Tcomsol* c_fensol ( void ) {

  int i, hof[2];

  double dz, mif[2], ut[2] = {-1., -1.}; //am, al, az

  struct TMeridiano* meri; // espacio para el puntero meri



if (bandesol) {

  meri = pasoMeridiano (105);

  comsol.hpm = meri->hor;

  comsol.mpm = meri->min;

  comsol.gra = meri->gra;

  comsol.mia = meri->ming;

  comsol.cul = meri->cul[0];

  comsol.ssd = semidesol (comdj);

  if (meri->sig == '+') // alturas positivas

	dz = M_PI/2. - (comsol.gra+comsol.mia/60.)*GRADOS; // distancia cenital

  else

	dz = M_PI/2. + (comsol.gra+comsol.mia/60.)*GRADOS; // distancia cenital

  if ( dz <= (ORTO_H + comdho) )//para front end; ORTO_H = (90 +50/60)*PI/180

	comsol.bpm = 1; //.TRUE. sol por encima del horizonte en el meridiano

  else

	comsol.bpm = 0; //.FALSE.

  for (i = 0; i < 8; i++) {

	fenosol (comdj, comrla, comrlo, cohuso, comdho, i, &ut[0]);

	hodobfen (ut, comdj, cohuso, &hof[0], &mif[0], 10.*erroan); // DJ -> (h,m) de la fecha

	switch (i) {

	  case (0): igualahm (&comsol.hpn[0], &comsol.mpn[0], &hof[0], &mif[0]);

	  break;

	  case (1): igualahm (&comsol.hpc[0], &comsol.mpc[0], &hof[0], &mif[0]);

	  break;

	  case (2):

		igualahm (&comsol.hss[0], &comsol.mss[0], &hof[0], &mif[0]);

		acimusol (hof, ut, &comsol.ssg[0], &comsol.ssm[0]);

	  break;

	  case (3):

		igualahm (&comsol.hsi[0], &comsol.msi[0], &hof[0], &mif[0]);

		acimusol (hof, ut, &comsol.sig[0], &comsol.sim[0]);

	  break;

	  case (4):

		igualahm (&comsol.hpi[0], &comsol.mpi[0], &hof[0], &mif[0]);

		acimusol (hof, ut, &comsol.pig[0], &comsol.pim[0]);

	  break;

	  case (5):

		igualahm (&comsol.hps[0], &comsol.mps[0], &hof[0], &mif[0]);

		acimusol (hof, ut, &comsol.psg[0], &comsol.psm[0]);

	  break;

	  case (6): igualahm (&comsol.hfc[0], &comsol.mfc[0], &hof[0], &mif[0]);

	  break;

	  case (7): igualahm (&comsol.hfn[0], &comsol.mfn[0], &hof[0], &mif[0]);

	}

  }

  bandesol = 0; //.FALSE.

  haynohay (dz); // claves para pintar carteles en el front end

}

  return &comsol;

}


/*==============================

   CALCULA HORA DE PASO DE UN ASTRO POR EL MERIDIANO SUPERIOR

================================*/



struct TMeridiano* pasoMeridiano (int nas) {

  double az, al, ut;



  ut = pasmersu (nas, comdj-cohuso, comrlo);

  if (ut == -1. || ut+cohuso-comdj >= 1.)

	mer.hor = -1;

  else {

	acimaltu (nas, ut, comrla, comrlo, mer.nom, mer.mag, &az, &al);

	horaminu (ut+cohuso-comdj, &mer.hor, &mer.min, erroan); // a 1'/10

	sigrmi (al, &mer.sig, &mer.gra, &mer.ming, erroan);

	if ( fabs(az-M_PI) < 1 )

	  strcpy (mer.cul, "Sur");

	else

	  strcpy (mer.cul, "Norte");

	if (mer.hor < 1) { // puede haber doble paso

//	  ut = pasmersu (nas, ut-cohuso+1./24., comrlo);

	  ut = pasmersu (nas, ut-cohuso+23./24., comrlo);

	  if (ut == -1. || ut+cohuso-comdj >= 1)

		mer.ho2 = -1;

	  else {

		acimaltu (nas, ut, comrla, comrlo, mer.nom, mer.mag, &az, &al);

		horaminu (ut+cohuso-comdj, &mer.ho2, &mer.mi2, erroan); // a 1'/10

		sigrmi (al, &mer.si2, &mer.gr2, &mer.ma2, erroan);

		if ( fabs(az-M_PI) < 1 )

		  strcpy (mer.cu2, "Sur");

		else

		  strcpy (mer.cu2, "Norte");

		}

	  }

	else

	  mer.ho2 = -1;

	}

  return &mer;

}

/*************************************/
/*       semidesol()                 */
/************************************/

double semidesol ( double jd ) // semidiametro del Sol en minutos

{

  return 60.*asin( R_H_UA / evaluapo(rh, jd) )/GRADOS;

}


/*************************************/
/*       evaluapo()                  */
/*************************************/

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

/****************************************/
/*     horner()                         */
/****************************************/

 
static double horner ( double s[], int j, double t ) {

  int i;

  double au = s[j]*t;



  for (i = j-1; i > 0; i--)

	au = (au + s[i])*t;

  return au + s[0];

}

/**************************************************/
/*   pasmersu()                                   */
/**************************************************/

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

/**************************************************/
/*               horlugar()                       */
/**************************************************/

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

/***********************************************/
/*      qalcuerp()                             */
/***********************************************/

void qalcuerp ( int i, double ut,

				char *nom, char *mag, double *ar, double *de )

{

  if (i == 100) {

	strcpy (nom, "Venus");

	sprintf (mag, "%4.1f ", magnitud (2, ut) );

	*ar = evaluapo (av, ut); // AR

	*de = evaluapo (dv, ut); // ë

	}

  else if (i == 101) {

	strcpy (nom, "Marte");

	sprintf (mag, "%4.1f ", magnitud (3, ut) );

	*ar = evaluapo (am, ut); // AR

	*de = evaluapo (dm, ut); // ë

	}

  else if (i == 102) {

	strcpy (nom, "J£piter");

	sprintf (mag, "%4.1f ", evaluapo (mj, ut)-0.15);//ojo, chapuza temporal

	*ar = evaluapo (aj, ut); //  AR

	*de = evaluapo (dj, ut); //  ë

	}

  else if (i == 103) {

	strcpy (nom, "Saturno");

	sprintf (mag, "%4.1f ", evaluapo (ms, ut)-1.69);//ojo, chapuza temporal

	*ar = evaluapo (as, ut); //  AR

	*de = evaluapo (ds, ut); // ë

	}

  else if (i == 104) {

	strcpy (nom, "Luna");

	strcpy (mag, "");

	*ar = evaluapo (al, ut); // AR

	*de = evaluapo (dl, ut); // ë

	}

  else if (i == 105) {

	strcpy (nom, "Sol");

	strcpy (mag, "");

	*ar = evaluapo (ah, ut); // AR

	*de = evaluapo (dh, ut); // ë

	}

  else

	qalestre (i, ut, nom, mag, ar, de);

}

/****************************************/
/*            magnitud()                */
/****************************************/

static double magnitud ( int j, double ut ) {// para Venus y Marte

  double a, d, r, s, xh, yh, zh, x, y, z, hp, i;



  a = evaluapo (ah, ut);

  d = evaluapo (dh, ut);

  r = evaluapo (rh, ut);

  ardr2xyz (a, d, r, &xh, &yh, &zh); // cartesianas del sol

  a = evaluapo (5 + j*j, ut); // av = 6, am = 9

  d = evaluapo (6 + j*j, ut); // dv = 7, dm = 10

  s = evaluapo (7 + j*j, ut); // rv = 8, rm = 11

  ardr2xyz (a, d, s, &x, &y, &z);

  hp = sqrt( pow(x - xh, 2) + pow(y - yh, 2) + pow(z - zh, 2) );

  i = acos( (s*s + hp*hp - r*r)/(2.*s*hp) );

  if (j == 2) {

	i = (i/GRADOS)/100.;

	i = i*( 0.09 + i*(2.39 - i*0.65) ) - 4.4;

	}

  else if (j == 3)

	i = 0.016*i/GRADOS - 1.52;



  return 5.*log10(s*hp) + i;

}

/*************************************************/
/*        ardr2xyz()                             */
/*************************************************/

void ardr2xyz ( double a, double d, double r,

				double *x, double *y, double *z )

{

  *x = r*cos(d)*cos(a);

  *y = r*cos(d)*sin(a);

  *z = r*sin(d);

}

/*****************************************/
/*         qalestre()                    */
/*****************************************/

static void qalestre ( int i, double ut,

					   char *nom, char *mag, double *ar, double *de ) {

  double aa, ap, dd, dp;

  static double dt, pn[3][3], b_t[3]; //, sol[3], b_e[7];

  extern int bandprnu;// externa: no tiene depende algoritmo, es para acelerar

//  double ar2, de2;



  if (bandprnu) {// para acelerar en ordenadores lentos

//	solybari2 (ut, &sol[0], &b_e[0]); // sol + baricentro (geocentricos)

	solybari (ut, &b_t[0]); // vel. geocentrica del baricentro

	prenut (ut, &pn[0][0]); // --- matriz de precesion y nutacion

	dt = tocent (ut);

	bandprnu = 0;

	}

  stardata (i, nom, mag, &aa, &ap, &dd, &dp);

//  redaprox2 (&ar2, &de2, aa, dd, ap, dp, &pn[0][0], &b_e[0], &sol[0], dt);

  redaprox (ar, de, aa, dd, ap, dp, &pn[0][0], &b_t[0], dt);

}

/*******************************/
/*    solybari()               */
/*******************************/
 
static void solybari ( double ut, double *b_e ) {

  int i;

  double ap, dp, rp, a, d, r, coa, sia, cod, sid, b[3];



  ap = evaluapo (ah, ut);

  dp = evaluapo (dh, ut);

  rp = evaluapo (rh, ut);

  coa = cos(ap);

  sia = sin(ap);

  cod = cos(dp);

  sid = sin(dp); // --- (x/r, y/r, z/r)_sol_Tierra = -Tierra_sol

  a = derivapo (ah, ut);

  d = derivapo (dh, ut);

  r = derivapo (rh, ut);

// --- (x',y',z')_baricentro ÷ sol '! ƒ_b/c = -0.0057755 b_e(5,6,7)

  b[0] = -0.0057755*(r*cod*coa - rp*(cod*sia*a + sid*coa*d));

  b[1] = -0.0057755*(r*cod*sia + rp*(cod*coa*a - sid*sia*d));

  b[2] = -0.0057755*(r*sid + rp*cod*d);

  for (i = 0; i < 3; i++) *(b_e+i) = b[i];

}

/*****************************/
/*     derivapo()            */
/*****************************/

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


/*****************************************/
/*        dehorn()                       */
/*****************************************/

static double dehorn ( double s[], int j, double t ) {

  int i;

  double au = j*s[j]*t;



  for (i = j - 1; i > 1; i--)

	au = (au + i*s[i])*t;

  return au + s[1];

}


/***************************/
/*   prenut()              */
/***************************/


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

/*********************************************/
/*       nutaprox()                          */
/*********************************************/


static void nutaprox ( double ut, double *dpsi, double *deps ) {

  double rp, rv, t = ut - J_2000;



  rp = (125.0 - 0.05295*t)*GRADOS;

  rv = (200.9 + 1.97129*t)*GRADOS;

  *dpsi = -( 0.0048*sin(rp) + 0.0004*sin(rv) )*GRADOS; // ! ëí

  *deps =  ( 0.0026*cos(rp) + 0.0002*cos(rv) )*GRADOS; // ! ëî

}

/***********************************/
/*           tocent()              */
/***********************************/


double tocent ( double jd )

{// SJ desde J2000.0 hasta la fecha t=jd

   return (jd - J_2000)/36525.; // J_2000 = 2451545.0;

}

/************************************/
/*           preceang()             */
/************************************/


static void preceang (double t, double *set, double *z, double *the)

{

  *set = AS_RAD*(2306.2181 + (0.30188 + 0.017998*t)*t)*t;

  *z =   AS_RAD*(2306.2181 + (1.09468 + 0.018203*t)*t)*t;

  *the = AS_RAD*(2004.3109 - (0.42665 + 0.041833*t)*t)*t;

}

/*********************************/
/*         oblecl()              */
/*********************************/

static double oblecl ( double x )

{// oblicuidad media de la ecliptica cuando x se expresa en SJ

  return AS_RAD*( 84381.448 - (46.8150 + (0.00059 - 0.001813*x)*x)*x );

}

/******************************************/
/*              stardata()                */
/******************************************/


void  stardata ( int i, char* nom, char* mag,

				 double *ar, double *ap, double *de, double *dp) {



  strcpy (nom, estran.noe[i-1]);

  strcpy (mag, estran.mve[i-1]);

  *ar = estran.are[i-1];

  *de = estran.dee[i-1];

  *ap = estran.ape[i-1];

  *dp = estran.dpe[i-1];

}

/********************************/
/*         redaprox()           */
/********************************/


static void redaprox ( double *ar, double *de,

					   double arp, double dep, double arv, double dev,

					   double *pn, double *b, double dt) {

  int j, k;

  double mpn[3][3], b_e[3], cart[3], vel[3], coa, sia, cod;

// sin paralaje ni vel. radial ni deflexion de la luz ni aberr. relativista

  for (k = 0; k < 3; k++)

	for (j = 0; j < 3; j++)

	  mpn[k][j] = *(pn+3*k+j);

  for (j = 0; j < 3; j++)

	b_e[j] = *(b+j);

  coa = cos(arp);

  sia = sin(arp);

  cod = cos(dep);

  cart[0] = coa*cod;

  cart[1] = sia*cod;

  cart[2] = sin(dep);

  vel[0] = -cart[1]*arv - cart[2]*coa*dev;

  vel[1] = cart[0]*arv - cart[2]*sia*dev;

  vel[2] = cod*dev;

  cart[0] = cart[0] + dt*vel[0];

  cart[1] = cart[1] + dt*vel[1];

  cart[2] = cart[2] + dt*vel[2];

  sia = sqrt( cart[0]*cart[0] + cart[1]*cart[1] + cart[2]*cart[2] );// aux

  for(j = 0; j < 3; j++)// aberracion

	vel[j] = cart[j]/sia + b_e[j];// vel == aux.

  coa = sqrt( vel[0]*vel[0] + vel[1]*vel[1] + vel[2]*vel[2] );

  for(j = 0; j < 3; j++)// vector unitario

	vel[j] = vel[j]/coa; // vel == aux.

  for(j = 0; j < 3; j++) { // producto (cart) = (mpn).(vel)

	cart[j] = 0.;

	for(k = 0; k < 3; k++) cart[j] += mpn[j][k]*vel[k];

	}

  *ar = atan2( cart[1], cart[0] );

  *de = asin( cart[2] );

}

/************************************/
/*        horlug()                  */
/************************************/

double horlug ( double ut, double ar, double lon ) {

// desde el meridiano superior hacia el W. Aumenta con UT

  ut = (tsvut (ut) - ar) + lon; //aux: HL = HG + long. = (TS-AR) + long.

  return fmod (40.*M_PI+ut, 2.*M_PI); // 2*PI > HL >= 0

// al ir ''demodulada'' la AR de la Luna, ut puede ser < 0 y grande

}

/**************************************/
/*           tsvut()                  */
/**************************************/

double tsvut ( double ut ) {

  double dps, dep, e0 = oblecl ( tocent (ut) );



  nutaprox ( ut, &dps, &dep );

  return tsmut (ut) + dps*cos (e0 + dep);

}

/*********************************/
/*         tsmut()               */
/*********************************/

static double tsmut ( double ut ) {// tiempo sidereo medio de un UT (dias julianos)

  double sj, a1, a2, fra = (ut - 0.5) - (long) (ut - 0.5); //fraccion de dia



  sj = tocent (ut - fra); // siglos julianos (0h) desde J2000.0

  a1 = ( 15.*gmst0hut (sj) )*AS_RAD; // rad. de TSM Greenwich a 0 horas UT

  a2 = fra*dsol2sid (sj); // fracc. de dia solar medio en dias sidereos medios

  a1 += (2.*M_PI)*a2; // radianes de TSM en Greenwich a la hora pedida



  return fmod(a1, 2.*M_PI);

}

/************************************/
/*         gmstOhut()               */
/************************************/

static double gmst0hut ( double sj )

{// seg. de TS medio en Greenwich a 0 h. UT; sj = siglos jul. desde J2000

  return 24110.54841 + (8640184.812866 + (0.093104 - 6.2e-6*sj)*sj)*sj;

}

/************************************/
/*          dsol2sid()              */
/************************************/

static double dsol2sid ( double sj )

{// dia solar medio en dias sidereos medios; sj = siglos jul. desde J2000

  return 1.002737909350795 + (5.9006e-11 - 5.9e-15*sj)*sj;

}

/***************************************/
/*          secHLpms()                 */
/***************************************/

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

/***************************************/
/*        acimaltu()                   */
/***************************************/

void acimaltu ( int i, double ut, double lat, double lon,

				char *nom, char *mag, double *az, double *a ) {

  double ar, d;



  qalcuerp (i, ut, nom, mag, &ar, &d);

  ard2azalt (ut, ar, d, lat, lon, az, a);

}

/****************************************/
/*        ard2azalt()                   */
/****************************************/

void ard2azalt ( double ut, double ar, double d, double lat, double lon,

				 double *az, double *a )

{// de (AR, declinacion) -> (acimut, altura)

  ut = horlug (ut, ar, lon); // aux.: ut = HL

  hor2azal (ut, d, lat, az, a); //(HL,ë,latitud) -> (acimut,altura,latitud)

}// la altura A es verdadera, no tiene en cuenta la depresion del horizonte


/****************************************/
/*          hor2azal()                  */
/****************************************/

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

/****************************************/
/*               horaminu()             */
/****************************************/

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

/******************************************/
/*             sigrmi()                   */
/******************************************/

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

/*****************************************/
/*         fenosol()                     */
/*****************************************/

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

/***********************************/
/*         dzfensol()              */
/***********************************/

static double dzfensol ( int fen, double dho )

{

  if      ( fen == pcn || fen == fcn) return dho + NAUTICO;

  else if ( fen == pcc || fen == fcc) return dho + CIVIL;

  else if ( fen == ort || fen == oca) return dho + ORTO_H;

  else // if (fen == ori || fen == oci)

	return dho + ORTO_H - (32./60.)*GRADOS; // 32' de diametro solar

}

/*********************************/
/*        tipofenH()             */
/*********************************/

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

/*******************************/
/*      buscasol()             */
/*******************************/

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

/******************************/
/*      almucant()            */
/******************************/

static double almucant ( int j, double ut,

						 double lat, double lon, double dz0 )

{

  if (j == 105)

	return dz0 - distzsol (ut, lat, lon);

  else

	return 0.; // incompleta. Solo para el sol

}

/******************************/
/*      distzsol()            */
/******************************/

static double distzsol ( double ut, double fi, double la) {

  double de = evaluapo (dh, ut);

  double ar = evaluapo (ah, ut);

  return distce ( fi, de, horlug (ut, ar, la) );

}

/*****************************/
/*       distce()            */
/*****************************/

double distce ( double fi, double de, double ho )

{ // dist. cenital de astro con decl. DE y horario lugar HO en latitud FI

  return acos( sin(fi)*sin(de) + cos(fi)*cos(de)*cos(ho) );

}

/********************************/
/*         secAlmuc()           */
/********************************/

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

/*********************************/
/*          iterasol()           */
/*********************************/

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


/****************************************/
/*            angpol()                  */
/****************************************/

double angpol ( double fi, double de, double dz )

{

  dz = (cos(dz) - sin(fi)*sin(de) ) / (cos(fi)*cos(de) );

  if( fabs(dz) > 1.) // ?es posible?

	exit (1);

  return acos(dz);

}

/**********************************/
/*        hodobfen()              */
/**********************************/

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


/********************************************/
/*          igualahm()                      */
/********************************************/


static void igualahm ( int *h, double *m, int *hora, double *minuto )

{

  *(h++) = *(hora++);

  *(m++) = *(minuto++);

  *h = *hora;

  *m = *minuto;

}


/**********************************/
/*       acimusol()               */
/**********************************/


static void acimusol ( int ho[2], double ut[2],

					   int *ssg, double *ssm ) {

  double az, al;



  if (ho[0] != -1) { // hay un fenomeno

	acimaltu (105, ut[0], comrla, comrlo, nom, mag, &az, &al);

	grami (az, ssg, ssm, erroan);

	if (ho[1] != -1) { // hay doble fenomeno

	  acimaltu (105, ut[1], comrla, comrlo, nom, mag, &az, &al);

	  grami (az, ssg+1, ssm+1, erroan);

	  }

	}

}

/************************************/
/*         grami()                  */
/************************************/

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

/**********************************/
/*         haynohay()             */
/**********************************/

static void haynohay ( double dz )

{

  if (comsol.hss[0] == -1) // no hay salida

	if (comsol.hps[0] == -1) // ni puesta

	  if ( dz < (ORTO_H + comdho) ) // siempre encima horizonte

		comsol.hss[0] = 99;

	  else if (comsol.hpc[0] == -1) // no hay principio civil

		if (comsol.hfc[0] == -1) // no hay fin civil

		  if ( dz < (CIVIL + comdho) ) // entre -6 y horizonte

			comsol.hpc[0] = 99;

		  else if (comsol.hpn[0] == -1) // no hay principio nautico

			if (comsol.hfn[0] == -1) // no hay fin nautico

			  if ( dz < (NAUTICO + comdho) ) // entre -12 y -6

				comsol.hpn[0] = 99;

			  else // siempre por debajo de -12

				comsol.hpn[0] = 88;

}


/*****************************************************\

|*** Opcion 'Fenomenos de Luna'                    ***|

\*****************************************************/



/*TDialogLuna::TDialogLuna () :

	TDialog (TRect(10, 8, 70, 22), "Fen¢menos de Luna"),

	TWindowInit (&TDialogLuna::initFrame)

{

	static Tcomfel* comfel;



	options  |= ofCenterX;

	dragMode |= dmLimitAll;



	// Calcular datos si es necesario

//	if (siCalcular (opLuna)) {

		mostrarMsgEsperar();

		comfel = c_fenlun ();

		borrarMsgEsperar();

//	}



	TEtiqueta* pe, *pe2, *pe3;



	// Empezamos a mostrar los datos en el di logo

//	insert (pe = new TEtiqueta(TRect(3, 2, 57, 3), " Semidi metro.........: %.1lf'", 1));

//	pe->setData (&comfel->lsd);



	insert (pe = new TEtiqueta(TRect(3, 2, 57, 3), " Edad (a 0h oficiales): %.1lf d¡as", 1));

	pe->setData (&comfel->eda);



	if (comfel->bpm != -99 && (comfel->bpm != 99 || comfel->hpm != -1)) {

	   insert (new TStaticText(TRect(3, 4, 22, 5), "Horas oficiales de:"));



	   insert (pe  = new TEtiqueta (TRect (3,  5, 57, 6),

									" Paso meridiano lugar.: %ih %.0lfm",

									2

								   )

			   );

	   insert (pe2 = new TEtiqueta (TRect (3,  6, 57, 7),

									"     Altura verdadera.: %iø %.1lf'",

									2

								   )

			  );

	   insert (pe3 = new TEtiqueta (TRect (3,  7, 57, 8), "     Culminaci¢n......: %s", 1));



//	   e1 = pe;

//	   e2 = pe3;



	   // Si hay paso por el meridiano del lugar mandamos los datos

	   if (comfel->hpm != -1) {

		  horaPasoMer.hor = comfel->hpm;

		  horaPasoMer.min = comfel->mpm;

		  pe->setData (&horaPasoMer);



		  altPasoMer.gra = comfel->gam;

		  altPasoMer.min = comfel->mam;

		  pe2->setData (&altPasoMer);



		  if (comfel->cul == 'N')

			 cadCul = "Norte";

		  else

			 cadCul = "Sur";

		  pe3->setData (&cadCul);

	   }

	   // Si no hay, escribimos una l¡nea

	   else {

		  pe->estado  = stLinea;

		  pe2->estado = stLinea;

		  pe3->estado = stLinea;

	   }



	   if (comfel->bpm != 99) {/////////////********

		 insert (pe  = new TEtiqueta (TRect(3,  8, 34, 9), " Salida...............: %2ih %2.0lfm", 2));

		 insert (pe2 = new TEtiqueta (TRect(34, 8, 57, 9), "    Acimut: %3iø %4.1lf'", 2));



		 // Si hay salida de la luna mandamos los datos

		 if (comfel->hsa != -1) {

			horaSalida.hor = comfel->hsa;

			horaSalida.min = comfel->msa;

			pe->setData (&horaSalida);



			aciSalida.gra = comfel->gzs;

			aciSalida.min = comfel->mzs;

			pe2->setData (&aciSalida);

		 }

		 else {

			pe->estado  = stLinea;

			pe2->estado = stLinea;

		 }



		 insert (pe  = new TEtiqueta (TRect(3, 9, 34,10), " Puesta...............: %2ih %2.0lfm", 2));

		 insert (pe2 = new TEtiqueta (TRect(34,9, 57,10), "    Acimut: %3iø %4.1lf'", 2));



		 // Si hay puesta de la luna mandamos los datos

		 if (comfel->hpu != -1) {

			horaPuesta.hor = comfel->hpu;

			horaPuesta.min = comfel->mpu;

			pe->setData (&horaPuesta);



			aciPuesta.gra = comfel->gzp;

			aciPuesta.min = comfel->mzp;

			pe2->setData (&aciPuesta);

		 }

		 else {

			pe->estado  = stLinea;

			pe2->estado = stLinea;

		 }

	   }

	   else {

	   TStaticText* ps;

	   ps = new TStaticText (TRect (1, 10, 39, 11), "Luna siempre por encima del horizonte.");

	   ps->options |= ofCenterX;

	   insert (ps);

	   }

  }



	// Si no hay fen¢menos, indicar la causa

	else {

	   TStaticText* ps;



	   ps = new TStaticText (TRect (1,  6, 18, 7), "No hay fen¢menos.");

	   ps->options |= ofCenterX;

	   insert (ps);

	   if (comfel->bpm == 99)

		 ps = new TStaticText (TRect (1, 7, 39, 8),

							   "Luna siempre por encima del horizonte.");

	   else

		 ps = new TStaticText (TRect (1, 7, 39, 8),

							   "Luna siempre por debajo del horizonte.");

	   ps->options |= ofCenterX;

	   insert (ps);

	}



	insert (new TButton(TRect(22, 11, 39, 13), "~A~ceptar", cmOK, bfDefault));

	selectNext (False);

}
*/
ÿ