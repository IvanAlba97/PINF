#include "../kernel/externos.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

int fecha_valida(int ano, int mes, int dia);
void rellenarListaSol (struct TFecha *fecIni, struct TFecha *fecFin);
void strcatSol (char* dest,struct TFecha f, struct Tcomsol* sol);
TFecha& operator++ (TFecha& f, int);
int operator<= (TFecha& fi, TFecha& ff);
int operator- (TFecha& ff, TFecha& fi);
void strcatHora (char* dest, int hor, double min, int siDec=0);

struct TFecha *fecIni, *fecFin;

int main(void){

   int latgra, latmin, latseg, longra, lonmin, lonseg, horut, anoi,mesi,diai, anof, mesf, diaf;
   double minutos_lat, minutos_lon;
   char latsig, lonsig;
   char *data = (char *) calloc(sizeof(char), 40);

   printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
   printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n");
   printf("<meta content=\"BEA Weblogic Portal 9.2.2\" name=\"GENERATOR\">\n");
   printf("<meta content=\"BEA Weblogic Portal 9.2.2\" name=\"CODE_LANGUAGE\">\n");
   printf("<meta name=\"title\" content=\"Real Instituto y Observatorio de la Armada\">\n");
   printf("<meta name=\"DC.title\" content=\"Real Instituto y Observatorio de la Armada\">\n");
   printf("<meta http-equiv=\"title\" content=\"Real Instituto y Observatorio de la Armada\">\n");

   printf("<meta name=\"keywords\" content=\"armada espa&ntilde;ola, armada, marina espa&ntilde;ola, www.armada.mde.es," \
   " la armada, armada espanola, real instituto y observatorio, hora real, hora oficial, armada.mde.es, real observatorio," \
   " roa, marina, san fernando, cadiz, mde, magnetismo, gps, astronom&iacute;a, utc, sismolog&iacute, hora utc, horario de" \
   " verano, efem&erides, orto, ocaso, biblioteca, museo, libros, jorge juan, archivo hist&oacute;rico, instrumentos antiguos," \
   " boletines, exposiciones virtuales, incunables, geof&iacute;sica, l&aacute;ser, fen&oacute;menos astron&oacute;micos," \
   " eclipse, ocultaci&oacute;n, tr&ansito\">\n");

   printf("<meta name=\"dc.keywords\" content=\"armada espa&ntilde;ola, armada, marina espa&ntilde;ola, www.armada.mde.es," \
   " la armada, armada espanola, real instituto y observatorio, hora real, hora oficial, armada.mde.es, real observatorio," \
   " roa, marina, san fernando, cadiz, mde, magnetismo, gps, astronom&iacute;a, utc, sismolog&iacute, hora utc, horario de" \
   " verano, efem&erides, orto, ocaso, biblioteca, museo, libros, jorge juan, archivo hist&oacute;rico, instrumentos antiguos," \
   " boletines, exposiciones virtuales, incunables, geof&iacute;sica, l&aacute;ser, fen&oacute;menos astron&oacute;micos," \
   " eclipse, ocultaci&oacute;n, tr&ansito\">\n");

   printf("<meta http-equiv=\"keywords\" content=\"armada espa&ntilde;ola, armada, marina espa&ntilde;ola, www.armada.mde.es," \
   " la armada, armada espanola, real instituto y observatorio, hora real, hora oficial, armada.mde.es, real observatorio," \
   " roa, marina, san fernando, cadiz, mde, magnetismo, gps, astronom&iacute;a, utc, sismolog&iacute, hora utc, horario de" \
   " verano, efem&erides, orto, ocaso, biblioteca, museo, libros, jorge juan, archivo hist&oacute;rico, instrumentos antiguos," \
   " boletines, exposiciones virtuales, incunables, geof&iacute;sica, l&aacute;ser, fen&oacute;menos astron&oacute;micos," \
   " eclipse, ocultaci&oacute;n, tr&ansito\">\n");
   
   printf("<meta name=\"description\" content=\"Real Instituto y Observatorio de la Armada\">\n");
   printf("<meta name=\"DC.description\" content=\"Real Instituto y Observatorio de la Armada\">\n");
   printf("<meta http-equiv=\"description\" content=\"Real Instituto y Observatorio de la Armada\">\n");

   printf("<meta name=\"language\" content=\"es\">\n");
   printf("<meta name=\"DC.language\" content=\"SPANISH\">\n");
   printf("<meta http-equiv=\"language\" content=\"es\">\n");
   printf("<meta name=\"distribution\" content=\"global\">\n");
   printf("<meta name=\"resource-type\" content=\"document\">\n");
   printf("<meta name=\"robots\" content=\"all | index | follow\">\n");
   printf("<meta name=\"REVISIT-AFTER\" content=\"3 days\">\n");
   printf("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">\n");
   printf("<meta http-equiv=\"Pragma\" content=\"no-cache\">\n");
   printf("<meta http-equiv=\"Expires\" content=\"0\">\n");
   printf("<meta http-equiv=\"Date\" content=\"Mon Oct 27 08:28:28 CEST 2008\">\n");
   printf("<meta name=\"author\" content=\"Armada Española.\">\n");
   printf("<meta name=\"DC.Creator\" content=\"Armada Española.\">\n");
   printf("<meta http-equiv=\"Creator\" content=\"Armada Española.\">\n");
 
   printf("<TITLE>Fen&oacute;menos de Sol en un intervalo</TITLE>\n");
   
   printf("<link rel=\"stylesheet\" TYPE=\"text/css\" HREF=\"../estilo_roa.css\">\n");

   printf("<link rel=\"alternate\" type=\"application/rss+xml\" title=\"RSS\" href=\"http://www.armada.mde.es/ArmadaPortal/page/Portal/ArmadaEspannola/_inicio_rss/\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/body.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/armadaShell.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/book.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/button.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/form.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/layout.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/portlet.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/simpleShell.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/simpleMenu.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/templates.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/estilo_imprimir.css\" rel=\"stylesheet\" type=\"text/css\" media=\"print\">\n");
   printf("<link href=\" http://www.armada.mde.es /ArmadaPortal/framework/skins/Armada92/css/window.css\" rel=\"stylesheet\" type=\"text/css\" media=\"screen\">\n");
   
   printf("<body>\n");

   data = getenv("QUERY_STRING");
     if(data == NULL) {
      printf("<BR><BR><p class=\"errores\">Los datos introducidos no son v&aacute;lidos.</p>\n");
      exit(EXIT_FAILURE);
      }     
   else if(sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&horut=%i&anoi=%i&mesi=%i&diai=%i&anof=%i&mesf=%i&diaf=%i",&latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &horut, &anoi, &mesi, &diai, &anof, &mesf, &diaf) != 15)
   {	printf("<BR><BR><BR><BR><p class=\"errores\">Los datos introducidos no son v&aacute;lidos.</p>\n");
	exit(EXIT_FAILURE);
    }
   else{
      if ((latgra < 0) || (latgra > 90)) {
	printf("<BR><BR><BR><BR><p class=\"errores\">Los grados deben estar entre 0º y 90º.</p>\n");
	 exit(EXIT_FAILURE);
      }
      if ((latmin < 0) || (latmin > 59)) {
         printf("<BR><BR><BR><BR><p class=\"errores\">Los minutos deben estar entre 0' y 59'.</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((latseg < 0) || (latseg > 59)) {
         printf("<BR><BR><BR><BR><p class=\"errores\">Los segundos deben estar entre 0'' y 59''.</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((longra < 0) || (longra > 180)) {
         printf("<BR><BR><BR><BR><p class=\"errores\">Los grados deben estar entre 0º y 180º.</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((lonmin < 0) || (lonmin > 59)) {
         printf("<BR><BR><BR><BR><p class=\"errores\">Los minutos deben estar entre 0' y 59'.</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((lonseg < 0) || (lonseg > 59)) {
         printf("<BR><BR><BR><BR><p class=\"errores\">Los segundos deben estar entre 0'' y 59''.</p>\n");
	 exit(EXIT_FAILURE);
	 }   
      if ((latsig != 'N') && (latsig != 'S')) {
         printf("<BR><BR><BR><BR><p class=\"errores\">La latitud debe ser Norte o Sur.</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((lonsig != 'W') && (lonsig != 'E')) {
         printf("<BR><BR><BR><BR><p class=\"errores\">La longitud debe ser Este u Oeste.</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((latgra == 90) && ((latmin > 0) || (latseg > 0))) {
         printf("<BR><BR><BR><BR><p class=\"errores\">La latitud debe ser menor o igual a 90º</p>\n");
	 exit(EXIT_FAILURE);
	 } 
      if ((longra == 180) && ((lonmin > 0) || (lonseg > 0))) {
         printf("<BR><BR><BR><BR><p class=\"errores\">La longitud debe ser menor o igual a 180º</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((anof - anoi) > 1) {
         printf ("<BR><BR><BR><BR><p class=\"errores\">No debe haber dos a&ntilde;os o m&aacute;s para realizar los c&aacute;lculos</p>\n");
	 exit(EXIT_FAILURE);
         }
      if (!(fecha_valida(anoi, mesi, diai)) || !(fecha_valida(anof, mesf, diaf))) {
	 printf("<BR><BR><BR><BR><p class=\"errores\">La fecha debe estar dentro del intervalo de fechas v&aacute;lidas</p>\n");
	 exit(EXIT_FAILURE);
	 }
      if ((anoi*366+31*mesi+diai) > (anof*366+31*mesf+diaf)) {
	printf("<BR><BR><BR><BR><p class=\"errores\">La fecha inicio debe ser menor que la fecha fin.</p>\n");
	exit(EXIT_FAILURE);
	}
     if ((horut < -11) || (horut > 12)) {
        printf("<BR><BR><BR><BR><p class=\"errores\">La diferencia horaria (Hora - UT) debe estar entre -11 y 12</p>\n");
	exit(EXIT_FAILURE);
     }
   }
   printf("<center><TABLE BORDER=0 WIDTH=580><TR><TD>\n");
   
   printf("<br><p class=\"titulo\">Fen&oacute;menos de Sol<br>desde %i/%i/%i hasta %i/%i/%i</p>\n", diai,mesi,anoi,diaf,mesf,anof);

   minutos_lat = latmin + latseg/60.;
   minutos_lon = lonmin + lonseg/60.;

   fecIni = (struct TFecha*) calloc(sizeof(struct TFecha), 1);
   fecFin = (struct TFecha*) calloc(sizeof(struct TFecha), 1);

   fecIni->dia = diai;
   fecIni->mes = mesi;
   fecIni->ano = anoi;
   fecFin->dia = diaf;
   fecFin->mes = mesf;
   fecFin->ano = anof;
   preferen(latgra, minutos_lat, latsig, longra, minutos_lon, lonsig, horut);
   printf("<BR><BR><CENTER><TABLE summary=\"Datos de hora oficial-UT y posici&oacute;n\">\n");
   printf("<caption>Hora oficial-UT y posici&oacute;n</caption>");
   printf("<THEAD>\n");
   printf("<TR><TD width=170>Hora oficial - UT</TD><TD width=120>Latitud</TD><TD width=120>Longitud</TD></TR>");
   printf("</THEAD>\n");
   printf("<TBODY class=\"fondo_tabla\">\n");
   printf("<TR><TD ALIGN=left> %i</TD>\n", horut);
   printf("<TD ALIGN=left> %i. %4.1lf' %c</TD>\n", latgra, minutos_lat, latsig);
   printf("<TD ALIGN=left> %i. %4.1lf' %c</TD></TR></TBODY>\n",longra, minutos_lon, lonsig);
   printf("</TABLE><br><br>\n");
				
   rellenarListaSol(fecIni, fecFin);
   printf("</TD></TR></TABLE>\n");
   printf("</BODY>\n");
   free(fecIni);
   free(fecFin);
   return 0;
}

int fecha_valida(int ano, int mes, int dia){
  
  int ain = 2010, afi = 2020;

  if((ano < ain) || (ano > afi)){ 
    return 0;
    }
  if((mes < 1) || (mes > 12))
    return 0;
  if((dia < 1) || (dia > 31))
    return 0;
  switch(mes){
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:  
  case 12: 
      return (dia<=31);
  case 4:
  case 6:
  case 9:
  case 11:
      return (dia<=30);
  case 2: if ((ano%4) != 0)
    return (dia <= 28);
  else if ((ano%100) != 0)
    return (dia <= 29);
  else if ((ano%400) != 0)
    return (dia <= 28);
  else
    return (dia <= 29);
  }
  return EXIT_FAILURE;
}
  
/***********************************************\
|*** Rellenar la lista con los datos         ***|
\***********************************************/

void rellenarListaSol (struct TFecha *fecIni, struct TFecha *fecFin) {

	struct Tcomsol* sol;
	struct TPosicion posIni, pos;
	struct TFecha fec;
	char* cad = (char *) calloc(sizeof(char), 70);

	/*mostrarMsgEsperar ();*/
	fec = *fecIni;
	leerPosicionCommon (&posIni);  // Leer situacion inicial
	printf("<TABLE summary=\"Fen&oacute;menos de Sol para cada fecha\" COLS=4 WIDTH=\"580\">\n");
	printf("<caption>Fen&oacute;menos de Sol para cada fecha</caption>");
	printf("<THEAD><TR><TD>FECHA</TD><TD>ORTO</TD><TD>MERIDIANO</TD><TD>OCASO</TD></TR>\n");
	printf("</THEAD>\n");
	printf("<TBODY class=\"fondo_tabla\">\n");
	while (fec <= *fecFin) {
		leerPosicionCommon (&pos);
		pos.dia = fec.dia;
		pos.mes = fec.mes;
		pos.ano = fec.ano;
		escribirPosicionCommon (&pos);
		trad_ker ();
		sol = c_fensol ();
		printf("<TR>");
		strcatSol (cad, fec, sol);
		strcpy(cad, "");
		fec++;		// Pasar al siguiente d¡a
		printf("</TR>");
	};
	printf("</TBODY></TABLE>\n");

	/*	borrarMsgEsperar ();
		listBox->newList (lista);
	escribirPosicionCommon (&posIni);  // Escribir situaci¢n inicial
	trad_ker();
	msgSol->setState (sfVisible, siMsgSol);*/
	free(cad);
}


/**********************************************************\
|*** Copia en 'dest' los datos del fen¢meno de sol.     ***|
|*** Corresponde a cada una de las l¡neas del listBox.  ***|
\**********************************************************/

void strcatSol (char* dest, TFecha f, Tcomsol* sol) {
	sprintf (dest, "%2i/%02i/%4i", f.dia, f.mes, f.ano);
	printf("<TD>%s</TD>\n", dest);
	
	// Si paso por el meridiano visible
	if (sol->bpm)
	  if (sol->hss[0] == 99) { // siempre sobre el horizonte
		char cad[60];
		sprintf (cad, "***");
		printf("<TD>%s</TD>\n", cad);
		strcpy(cad, "");
		sprintf(cad,"%2ih %4.1lfm", sol->hpm, sol->mpm);
		printf("<TD>%s</TD>\n", cad);
		sprintf (cad, "***");
		printf("<TD>%s</TD>\n", cad);
		/*strcat (dest, cad);*/
		/*	siMsgSol = True;*/
	  }
	  else {
		// Escribir salida
		if (sol->hss[1] == -1) {
			strcpy(dest,"");
			/*strcat (dest, "    ");*/
			strcatHora (dest, sol->hss[0], sol->mss[0]);
			printf("<TD>%s</TD>\n", dest);
			/*strcat (dest, "     ");*/
		}
		else {
			strcpy(dest,"");
			strcatHora (dest, sol->hss[0], sol->mss[0]);
			strcatHora (dest, sol->hss[1], sol->mss[1]);
			printf("<TD>%s</TD>\n", dest);
		}

		strcpy(dest, "");
		// Escribir paso meridiano
		strcatHora (dest, sol->hpm,    sol->mpm, 1);
		printf("<TD>%s</TD>\n", dest);
		// Escribir puesta
		if (sol->hps[1] == -1) {
		/*	strcat (dest, "    ");*/
			strcpy(dest, "");
			strcatHora (dest, sol->hps[0], sol->mps[0]);
		/*	strcat (dest, "     ");*/
			printf("<TD>%s</TD>\n", dest);
		}
		else {
			strcpy(dest,"");
			strcatHora (dest, sol->hps[0], sol->mps[0]);
			strcatHora (dest, sol->hps[1], sol->mps[1]);
			printf("<TD>%s</TD>\n", dest);
		}
	  }
	else {
	  strcpy(dest, "");
	  strcat (dest, "Sol siempre por debajo del horizonte");
	  printf("<TD>%s</TD>\n", dest);
       }
}

/********************************************************\
|*** Operaciones con fechas                           ***|
\********************************************************/

TFecha& operator++ (TFecha& f, int) {
	const int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int max;

	if (f.mes == 2 && bisiesto(f.ano) )
		max = 29;
	else
		max = dias[f.mes-1];

	if (++f.dia > max) {	// Pasar al d¡a siguiente
	  f.dia = 1;
	  f.mes++;				// Pasar al mes siguiente
	  if (f.mes > 12) {
		f.mes = 1;
		f.ano++;			// Pasar al a¤o siguiente
	  }
	}

	return f;
}

int operator<= (TFecha& fi, TFecha& ff) {
	int siMenor = 0;
	if (fi.ano < ff.ano)
	  siMenor = 1;
	else if (fi.ano == ff.ano)
	  if (fi.mes < ff.mes)
		siMenor = 1;
	  else if (fi.mes == ff.mes)
		if (fi.dia <= ff.dia)
		  siMenor=1;

	return siMenor;
}

int operator- (TFecha& ff, TFecha& fi) {
	struct tm tmi, tmf;
	time_t timei, timef;
	double dif;

	tmi.tm_year = fi.ano - 1900;
	tmi.tm_mon = fi.mes - 1;
	tmi.tm_mday = fi.dia;
	tmi.tm_hour = 0;
	tmi.tm_min  = 0;
	tmi.tm_sec  = 1;
	tmi.tm_isdst = -1;

	tmf.tm_year = ff.ano - 1900;
	tmf.tm_mon = ff.mes - 1;
	tmf.tm_mday = ff.dia;
	tmf.tm_hour = 0;
	tmf.tm_min  = 0;
	tmf.tm_sec  = 1;
	tmf.tm_isdst = -1;

	timei = mktime (&tmi);
	timef = mktime (&tmf);
	dif = difftime (timef, timei);

	// Convertir a d¡as
	return int (dif / (60L*60L*24L));
}


/**********************************************************\
|*** Copia en 'dest' los datos de la hora 'hor' y 'min' ***|
\**********************************************************/

void strcatHora (char* dest, int hor, double min, int siDec) {
	char cad[80];
	if (hor == -1)
	  strcat (dest, "  -------");
	else {
	  if (siDec)
		sprintf (cad, "  %2ih %4.1lfm", hor, min);
	  else
		sprintf (cad, "  %2ih %2.0lfm", hor, min);
	  strcat (dest, cad);
	}
}



