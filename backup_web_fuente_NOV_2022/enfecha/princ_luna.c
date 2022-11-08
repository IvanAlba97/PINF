#include "../kernel/externos.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>



int fecha_valida(int ano, int mes, int dia);
void rellenarListaLuna(struct TFecha *fecIni);
TFecha& operator++ (TFecha& f, int);
int operator<= (TFecha& fi, TFecha& ff);
int operator- (TFecha& ff, TFecha& fi);
void strcatHora (char* dest, const char* msg, int* hora, double* min, int num=1);
void fase(int edad);

struct TFecha *fecIni;


int main(void){

   int latgra, latmin, latseg, longra, lonmin, lonseg, horut, anoi,mesi,diai;
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

   printf("<TITLE>Fen&oacute;menos de Luna para una fecha</TITLE>\n");

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
   else if(sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&horut=%i&anoi=%i&mesi=%i&diai=%i",&latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &horut, &anoi, &mesi, &diai) != 12)
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
      if (!(fecha_valida(anoi, mesi, diai))) {
        printf("<BR><BR><BR><BR><p class=\"errores\">La fecha debe estar dentro del intervalo de fechas v&aacute;lidas</p>\n");
	exit(EXIT_FAILURE);
	}
      if ((horut < -11) || (horut > 12)) {
        printf("<BR><BR><BR><BR><p class=\"errores\">La diferencia horaria (Hora - UT) debe estar entre -11 y 12</p>\n");
	exit(EXIT_FAILURE);
     }
   }

   printf("<center><table border=0 width=580><TR><TD>");
   //printf("<br><font size=+2><font color=\"#000099\"><font face=\"Arial\"><B>Fen&oacute;menos de Luna para %i/%i/%i</B></font></font></b><br>",diai,mesi,anoi);
   printf("<br><p class=\"titulo\">Fen&oacute;menos de Luna<br>para %i/%i/%i</p>\n", diai,mesi,anoi);

   minutos_lat = latmin + latseg/60.;
   minutos_lon = lonmin + lonseg/60.;

   fecIni = (struct TFecha*) calloc(sizeof(struct TFecha), 1);

   fecIni->dia = diai;
   fecIni->mes = mesi;
   fecIni->ano = anoi;

   preferen(latgra, minutos_lat, latsig, longra, minutos_lon, lonsig, horut);

   //printf("<BR><CENTER><TABLE BORDER=0 CELLSPACING=0 BGCOLOR=\"#CCFFFF\">");

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

   rellenarListaLuna(fecIni);

   printf("</TD></TR></TABLE>");
   printf("</BODY>");
   free(fecIni);
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
|*** Copia en 'dest' la cadena 'msg' seguida de una o   ***|
|*** dos hora, segun se especifique en 'num'.           ***|
\**********************************************************/

void strcatHora (char* dest, const char* msg, int* hora, double* min, int num) {
	char cad[80];

	strcpy (dest, msg);
	if (hora[0] == -1)
		strcat (dest, "-------");
	else {
		sprintf (cad, "%2ih %2.0fm", hora[0], float (min[0]));
		strcat (dest, cad);

		if (num == 2 && hora[1] != -1) {
			sprintf (cad, "  y  %2ih %2.0fm", hora[1], float (min[1]));
			strcat (dest, cad);
		}
	}
}

void rellenarListaLuna(struct TFecha *fecIni){


  struct Tcomfel* comfel;
  struct TPosicion posIni, pos;
  struct TFecha fec;

  fec = *fecIni;
  leerPosicionCommon (&posIni);  // Leer situacion inicial
  leerPosicionCommon (&pos);
  pos.dia = fec.dia;
  pos.mes = fec.mes;
  pos.ano = fec.ano;
  escribirPosicionCommon (&pos);
  trad_ker ();

  comfel = c_fenlun ();

  printf("<TABLE>");
  printf("<TBODY class=\"fondo_tabla\">\n");
  printf("<TR><TD><B>Edad (a 0h):</B> %.1lf d&iacute;as</TD>", comfel->eda);
  //printf("<TABLE><TR><TD><B>Edad (a 0h):</B> %.1lf d&iacute;as</TD>", comfel->eda);

  fase((int) comfel->eda);
  printf("</TR>");
  if (comfel->bpm != -99 && (comfel->bpm != 99 || comfel->hpm != -1)) {
//    printf("<TR><TD  COLSPAN=2><B><font face=\"Arial\"><font size=-1>Horas oficiales de:</font></font></B></TD></TR>");

    // Si hay paso por el meridiano del lugar mandamos los datos

    if (comfel->hpm != -1) {
      printf("<TR><TD COLSPAN=2><B>Paso meridiano lugar.:</B> %ih %.0lfm", comfel->hpm, comfel->mpm);
      printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Altura verdadera.:</B> %iº %.1lf'", comfel->gam, comfel->mam);

      if (comfel->cul == 'N')
	printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Culminaci&oacute;n......:</B> Norte</TD></TR>");
      else
	printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Culminaci&oacute;n......:</B> Sur</TD></TR>");
    }
    // Si no hay, escribimos una l¡nea
    else {
      printf("<TR><TD COLSPAN=2><B>Paso meridiano lugar.:</B> --------- ");
      printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Altura verdadera.:</B> --------- ");
      printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Culminaci&oacute;n......:</B> --------- </TD></TR>");
    }

    if (comfel->bpm != 99) {/////////////********

      // Si hay salida de la luna mandamos los datos
      if (comfel->hsa != -1) {
	printf("<TR><TD><B>Salida...............:</B> %2ih %2.0lfm</TD>", comfel->hsa, comfel->msa);
	printf("<TD><B>Acimut:</B> %3iº %4.1lf'</TD></TR>", comfel->gzs, comfel->mzs);

      }
      else {
	printf("<TR><TD><B>Salida...............:</B> --------- </TD>");
	printf("<TD><B>Acimut:</B> --------- </TD></TR>");
      }

      // Si hay puesta de la luna mandamos los datos
      if (comfel->hpu != -1) {
	printf("<TR><TD><B>Puesta...............:</B> %2ih %2.0lfm</TD>", comfel->hpu, comfel->mpu);
	printf("<TD><B>Acimut:</B> %3iº %4.1lf'</TD></TR>", comfel->gzp, comfel->mzp);
      }
      else {
	printf("<TR><TD><B>Puesta...............:</B> ---------- </TD>");
	printf("<TD><B>Acimut:</B> --------- </TD></TR>");
      }
    }
    else {
      printf("<TR><TD>Luna siempre por encima del horizonte.</TR></TD>");
    }
  }
  // Si no hay fenomenos, indicar la causa
  else {
    printf("<TR><TD><B>No hay fen&oacute;menos.</B></TD></TR>");

    if (comfel->bpm == 99)
      printf("<TR><TD><B>Luna siempre por encima del horizonte.</B></TD></TR>");
    else
      printf("<TR><TD><B>Luna siempre por debajo del horizonte.</B></TD></TR>");
  }
  printf("</TABLE>");
  printf("</TBODY>");
}

void fase(int edad){
  if (edad == 0)
    printf("<TD><IMG SRC=\"../../fases/e0.gif\"></TD>");
  if (edad == 1)
    printf("<TD><IMG SRC=\"../../fases/e1.gif\"></TD>");
  if (edad == 2)
    printf("<TD><IMG SRC=\"../../fases/e2.gif\"></TD>");
  if (edad == 3)
    printf("<TD><IMG SRC=\"../../fases/e3.gif\"></TD>");
  if (edad == 4)
    printf("<TD><IMG SRC=\"../../fases/e4.gif\"></TD>");
  if (edad == 5)
    printf("<TD><IMG SRC=\"../../fases/e5.gif\"></TD>");
  if (edad == 6)
    printf("<TD><IMG SRC=\"../../fases/e6.gif\"></TD>");
  if (edad == 7)
    printf("<TD><IMG SRC=\"../../fases/e7.gif\"></TD>");
  if (edad == 8)
    printf("<TD><IMG SRC=\"../../fases/e8.gif\"></TD>");
  if (edad == 9)
    printf("<TD><IMG SRC=\"../../fases/e9.gif\"></TD>");
  if (edad == 10)
    printf("<TD><IMG SRC=\"../../fases/e10.gif\"></TD>");
  if (edad == 11)
    printf("<TD><IMG SRC=\"../../fases/e11.gif\"></TD>");
  if (edad == 12)
    printf("<TD><IMG SRC=\"../../fases/e12.gif\"></TD>");
  if (edad == 13)
    printf("<TD><IMG SRC=\"../../fases/e13.gif\"></TD>");
  if (edad == 14)
    printf("<TD><IMG SRC=\"../../fases/e14.gif\"></TD>");
  if (edad == 15)
    printf("<TD><IMG SRC=\"../../fases/e15.gif\"></TD>");
  if (edad == 16)
    printf("<TD><IMG SRC=\"../../fases/e16.gif\"></TD>");
  if (edad == 17)
    printf("<TD><IMG SRC=\"../../fases/e17.gif\"></TD>");
  if (edad == 18)
    printf("<TD><IMG SRC=\"../../fases/e18.gif\"></TD>");
  if (edad == 19)
    printf("<TD><IMG SRC=\"../../fases/e19.gif\"></TD>");
  if (edad == 20)
    printf("<TD><IMG SRC=\"../../fases/e20.gif\"></TD>");
  if (edad == 21)
    printf("<TD><IMG SRC=\"../../fases/e21.gif\"></TD>");
  if (edad == 22)
    printf("<TD><IMG SRC=\"../../fases/e22.gif\"></TD>");
  if (edad == 23)
    printf("<TD><IMG SRC=\"../../fases/e23.gif\"></TD>");
  if (edad == 24)
    printf("<TD><IMG SRC=\"../../fases/e24.gif\"></TD>");
  if (edad == 25)
    printf("<TD><IMG SRC=\"../../fases/e25.gif\"></TD>");
  if (edad == 26)
    printf("<TD><IMG SRC=\"../../fases/e26.gif\"></TD>");
  if (edad == 27)
    printf("<TD><IMG SRC=\"../../fases/e27.gif\"></TD>");
  if (edad == 28)
    printf("<TD><IMG SRC=\"../../fases/e28.gif\"></TD>");
  if (edad == 29)
    printf("<TD><IMG SRC=\"../../fases/e29.gif\"></TD>");
  if (edad == 30)
    printf("<TD><IMG SRC=\"../../fases/e29.gif\"></TD>");
}

