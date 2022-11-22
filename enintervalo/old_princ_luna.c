#include "../kernel/externos.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

int fecha_valida(int ano, int mes, int dia);
TFecha& operator++ (TFecha& f, int);
int operator<= (TFecha& fi, TFecha& ff);
int operator- (TFecha& ff, TFecha& fi);
void strcatHora (char* dest, int hor, double min, int siDec=0);
void rellenarListaLuna (struct TFecha *fecIni, struct TFecha *fecFin);
void strcatLun (char* dest, TFecha f, Tcomfel* lun);
void fase ();

struct TFecha *fecIni, *fecFin;

int main(void){

   int latgra, latmin, latseg, longra, lonmin, lonseg, horut, anoi,mesi,diai, anof, mesf, diaf;
   double minutos_lat, minutos_lon;
   char latsig, lonsig;
   char *data = (char *) calloc(sizeof(char), 40);
   printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
   printf("<TITLE>Fen&oacute;menos de Luna en un intervalo</TITLE>\n");
   printf("<script language=\"JavaScript\">");
   printf("var fases;");
   printf("fases = window.open(\"fases.cgi\", \"Edades\", \"width=280,height=310, resizable=no\");");
   printf("fases.focus();");
   printf("</script>");
   printf("<body leftmargin=0 frameborder: marginwidth=0 marginleft=0 marginheight=0 topmargin=0"
   "text=\"#000000\" bgcolor=\"#FFFFFF\" link=\"#0000FF\" vlink=\"#800080\" alink=\"#FF0000\">");
   
   data = getenv("QUERY_STRING");
     if(data == NULL) {
      printf("<BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los datos introducidos no son v&aacute;lidos.</font></font></CENTER>");
      exit(EXIT_FAILURE);
      }     
   else if(sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&horut=%i&anoi=%i&mesi=%i&diai=%i&anof=%i&mesf=%i&diaf=%i",&latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &horut, &anoi, &mesi, &diai, &anof, &mesf, &diaf) != 15)
   {	printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los datos introducidos no son v&aacute;lidos.</font></font></CENTER>");
	exit(EXIT_FAILURE);
    }
   else{
      if ((latgra < 0) || (latgra > 90)) {
	printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los grados deben estar entre 0º y 90º.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
      }
      if ((latmin < 0) || (latmin > 59)) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los minutos deben estar entre 0' y 59'.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((latseg < 0) || (latseg > 59)) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los segundos deben estar entre 0'' y 59''.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((longra < 0) || (longra > 180)) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los grados deben estar entre 0º y 180º.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((lonmin < 0) || (lonmin > 59)) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los minutos deben estar entre 0' y 59'.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((lonseg < 0) || (lonseg > 59)) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>Los segundos deben estar entre 0'' y 59''.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }   
      if ((latsig != 'N') && (latsig != 'S')) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La latitud debe ser Norte o Sur.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((lonsig != 'W') && (lonsig != 'E')) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La longitud debe ser Este u Oeste.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((latgra == 90) && ((latmin > 0) || (latseg > 0))) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La latitud debe ser menor o igual a 90º</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 } 
      if ((longra == 180) && ((lonmin > 0) || (lonseg > 0))) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La longitud debe ser menor o igual a 180º</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ( (anof - anoi) > 1 ) {
	 printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>No debe haber dos a&ntilde;os o m&aacute;s para realizar los c&aacute;lculos</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if (!(fecha_valida(anoi, mesi, diai)) || !(fecha_valida(anof, mesf, diaf))) {
	 printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La fecha debe estar dentro del intervalo de fechas v&aacute;lidas</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
      if ((anoi*366+31*mesi+diai) > (anof*366+31*mesf+diaf)) {
	 printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La fecha inicio debe ser menor que la fecha fin.</font></font></CENTER>");
	 exit(EXIT_FAILURE);
	 }
     if ((horut < -11) || (horut > 12)) {
         printf("<BR><BR><BR><BR><CENTER><font face=\"Arial\"><font size=+1>La diferencia horaria (Hora - UT) debe estar entre -11 y 12</font></font></CENTER>");
	 exit(EXIT_FAILURE);
     }
   }

   printf("<center><TABLE BORDER=0 WIDTH=580><TR><TD>");
   printf("<br><center><font face=\"Arial\"><font color=\"#000099\"><font size=+2><b>Fen&oacute;menos de Luna desde %i/%i/%i hasta %i/%i/%i</font></font></font></b></center>\n",diai,mesi,anoi,diaf,mesf,anof);
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
   printf("<BR><BR><CENTER><TABLE cellspacing=0 BORDER=0 BGCOLOR=\"#CCFFFF\">");
   printf("<TR><TD BGCOLOR=\"#3333FF\"><font face=\"Arial\" color=\"#FFFF33\"><font size=+0><B>Hora Oficial - UT:</B></font></font></TD><TD ALIGN=right><font face=\"Arial\"><font size=+0> %i</font></font></TD></TR>", horut);
   printf("<TR><TD BGCOLOR=\"#3333FF\"><font face=\"Arial\" color=\"#FFFF33\"><font size=+0><B>Latitud:</B></font></font></TD><TD ALIGN=right><font face=\"Arial\"><font size=+0> %iº %4.1lf' %c</font></font></TD></TR>", latgra, minutos_lat, latsig);
   printf("<TR><TD BGCOLOR=\"#3333FF\"><font face=\"Arial\" color=\"#FFFF33\"><font size=+0><B>Longitud:</B></font></font></TD><TD ALIGN=right><font face=\"Arial\"><font size=+0> %iº %4.1lf' %c</font></font></TD></TR></TABLE></CENTER><BR><BR>", longra, minutos_lon, lonsig);
   
   rellenarListaLuna(fecIni,fecFin);
   printf("</TD></TR></TABLE></center>");

   printf("</BODY>");
   free(fecIni);
   free(fecFin);
   return 0;
}

int fecha_valida(int ano, int mes, int dia){
  
  int ain = 2001, afi = 2010;

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


/***********************************************\
|*** Rellenar la lista con los datos         ***|
\***********************************************/

void rellenarListaLuna (struct TFecha *fecIni, struct TFecha *fecFin) {

	struct Tcomfel* lun;
	struct TPosicion posIni, pos;
	struct TFecha fec;
	char* cad = (char *) calloc(sizeof(char), 80);

	/*mostrarMsgEsperar ();*/
	fec = *fecIni;
	leerPosicionCommon (&posIni);  // Leer situacion inicial
	printf("<center><TABLE BORDER=0 CELLSPACING=0 COLS=5 WIDTH=\"500\" BGCOLOR=\"#CCFFFF\">");
	printf("<TR BGCOLOR=\"#3333FF\"><TD><font color=\"#FFFF33\"><font face=\"Arial\"><font size=+0><B>FECHA</B></font></font></font></TD><TD><font face=\"Arial\"><font size=+0><font color=\"#FFFF33\"><B>ORTO</B></font></font></font></TD><TD><font face=\"Arial\"><font size=+0><font color=\"#FFFF33\"><B>MERIDIANO</B></font></font></font></TD><TD><font face=\"Arial\"><font size=+0><font color=\"#FFFF33\"><B>OCASO</font></B></font></font></TD><TD><font face=\"Arial\"><font color=\"#FFFF33\"><font size=+0><B>EDAD</B></font></font></font></TD></TR>");	
	while (fec <= *fecFin) {
		leerPosicionCommon (&pos);
		pos.dia = fec.dia;
		pos.mes = fec.mes;
		pos.ano = fec.ano;
		escribirPosicionCommon (&pos);
		trad_ker ();
		lun = c_fenlun ();
		printf("<TR>");
		/*cad = new (char[70]);*/
		strcatLun (cad, fec, lun);
		/*printf("%s\n", cad);*/
		strcpy(cad, "");
		/*lista->insert (cad);*/
		fec++;		// Pasar al siguiente d¡a
		printf("</TR>");
	};
	printf("</TABLE></center>");
	/*borrarMsgEsperar ();
	listBox->newList (lista);
	escribirPosicionCommon (&posIni);  // Escribir situaci¢n inicial
	trad_ker();
	msgLun->setState (sfVisible, siMsgLun);*/
	free(cad);
}


/**********************************************************\
|*** Copia en 'dest' los datos del fenomeno de luna.    ***|
|*** Corresponde a cada una de las l¡neas del listBox.  ***|
\**********************************************************/

void strcatLun (char* dest, TFecha f, Tcomfel* lun) {
	sprintf (dest, "%2i/%02i/%4i", f.dia, f.mes, f.ano);
	printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);

	if (lun->bpm == -99){
	  strcpy(dest, "");
	  strcat (dest,   "Luna siempre por debajo del horizonte");
	  printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	}
	else if (lun->bpm == 99) {
	  if (lun->hpm == -1){
	    strcpy(dest, "");
	    strcat (dest, "***");
	    printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	    strcpy(dest, "");
	    strcat (dest, "***");
	    printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	    strcpy(dest, "");
	    strcat (dest, "***");
	    printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	  }
	  else {
		char cad[60];
		sprintf (cad, "***");
		printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", cad);
		strcpy(cad, "");
		sprintf(cad, "%2ih %4.1lfm", lun->hpm, lun->mpm);
		printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", cad);
		strcpy(cad, "");
		sprintf(cad, "***");
		printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", cad);
		/*strcat (dest, cad);*/
	  }
	  /*siMsgLun = True;*/
	}
	else {
	  strcpy(dest, "");
	  /*strcat (dest, "   ");*/
	  strcatHora (dest, lun->hsa, lun->msa);
	  printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	  /*strcat (dest, "   ");*/
	  strcpy(dest, "");
	  strcatHora (dest, lun->hpm, lun->mpm);
	  printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	  /* strcat (dest, "   ");*/
	  strcpy(dest, "");
	  strcatHora (dest, lun->hpu, lun->mpu);
	  printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", dest);
	  /*strcat (dest, "     ");*/
	}
	char cad[15];
	sprintf (cad, "%4.1lf", lun->eda);
	/*strcat (dest, cad);*/
	printf("<TD><font face=\"Arial\"><font size=-1>%s</font></font></TD>", cad);
/*	fase((int) lun->eda); */
}

void fase (){
    printf("<TD><IMG SRC=\"../../fases/e0.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e1.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e2.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e3.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e4.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e5.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e6.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e7.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e8.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e9.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e10.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e11.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e12.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e13.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e14.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e15.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e16.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e17.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e18.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e19.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e20.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e21.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e22.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e23.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e24.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e25.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e26.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e27.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e28.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e29.gif\"></TD>");
    printf("<TD><IMG SRC=\"../../fases/e29.gif\"></TD>");
}









