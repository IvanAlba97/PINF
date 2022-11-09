#include "../kernel/externos.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

int fecha_valida(int ano, int mes, int dia);
void rellenarListaSol(struct TFecha *fecIni);
void strcatSol(struct Tcomsol *sol);
TFecha &operator++(TFecha &f, int);
int operator<=(TFecha &fi, TFecha &ff);
int operator-(TFecha &ff, TFecha &fi);
void strcatHora(char *dest, const char *msg, int *hora, double *min, int num = 1);

struct TFecha *fecIni;

int main(void)
{

  int latgra, latmin, latseg, longra, lonmin, lonseg, horut, anoi, mesi, diai;
  double minutos_lat, minutos_lon;
  char latsig, lonsig;

  char *data = (char *)calloc(sizeof(char), 40);

  // printf("<BODY leftmargin=0 frameborder: marginwidth=0 marginleft=0 marginheight=0 topmargin=0");

  printf("Content-Type:application/json\n");
  printf("{");

  data = getenv("QUERY_STRING");
  if (data == NULL)
  {
    printf("\"error\":\"Los datos introducidos no son válidos.\"}");
    exit(EXIT_FAILURE);
  }
  else if (sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&horut=%i&anoi=%i&mesi=%i&diai=%i", &latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &horut, &anoi, &mesi, &diai) != 12)
  {
    printf("\"error\":\"Los datos introducidos no son válidos.\"}");
    exit(EXIT_FAILURE);
  }
  else
  {
    if ((latgra < 0) || (latgra > 90))
    {
      printf("\"error\":\"Los datos introducidos no son válidos.\"}");
      exit(EXIT_FAILURE);
    }
    if ((latmin < 0) || (latmin > 59))
    {
      printf("\"error\":\"Los datos introducidos no son válidos.\"}");
      exit(EXIT_FAILURE);
    }
    if ((latseg < 0) || (latseg > 59))
    {
      printf("\"error\":\"Los segundos deben estar entre 0'' y 59''\"}");
      exit(EXIT_FAILURE);
    }
    if ((longra < 0) || (longra > 180))
    {
      printf("\"error\":\"Los grados deben estar entre 0º y 180º\"}");

      exit(EXIT_FAILURE);
    }
    if ((lonmin < 0) || (lonmin > 59))
    {
      printf("\"error\":\"Los minutos deben estar entre 0' y 59'\"}");

      exit(EXIT_FAILURE);
    }
    if ((lonseg < 0) || (lonseg > 59))
    {
      printf("\"error\":\"Los segundos deben estar entre 0'' y 59''\"}");

      exit(EXIT_FAILURE);
    }
    if ((latsig != 'N') && (latsig != 'S'))
    {
      printf("\"error\":\"La latitud debe ser Norte o Sur.\"}");

      exit(EXIT_FAILURE);
    }
    if ((lonsig != 'W') && (lonsig != 'E'))
    {
      printf("\"error\":\"La longitud debe ser Este u Oeste.\"}");

      exit(EXIT_FAILURE);
    }
    if ((latgra == 90) && ((latmin > 0) || (latseg > 0)))
    {
      printf("\"error\":\"La latitud debe ser menor o igual a 90º\"}");

      exit(EXIT_FAILURE);
    }
    if ((longra == 180) && ((lonmin > 0) || (lonseg > 0)))
    {
      printf("\"error\":\"La longitud debe ser menor o igual a 180º\"}");

      exit(EXIT_FAILURE);
    }
    if (!(fecha_valida(anoi, mesi, diai)))
    {
      printf("\"error\":\"La fecha debe estar dentro del intervalo de fechas válidas\"}");

      exit(EXIT_FAILURE);
    }
    if ((horut < -11) || (horut > 12))
    {
      printf("\"error\":\"La diferencia horaria (Hora - UT) debe estar entre -11 y 12\"}");

      exit(EXIT_FAILURE);
    }
  }

  //printf("<center><table border=0 width=580><tr><td>");

  //printf("<br><p class=\"titulo\">Fen&oacute;menos de Sol<br>para %i/%i/%i</p>\n", diai, mesi, anoi);

  printf("\"dia\": %i,",diai);
  minutos_lat = latmin + latseg / 60.;
  minutos_lon = lonmin + lonseg / 60.;

  fecIni = (struct TFecha *)calloc(sizeof(struct TFecha), 1);

  fecIni->dia = diai;
  fecIni->mes = mesi;
  fecIni->ano = anoi;

  preferen(latgra, minutos_lat, latsig, longra, minutos_lon, lonsig, horut);

  printf("<BR><BR><CENTER><TABLE summary=\"Datos de hora oficial-UT y posici&oacute;n\">\n");
  printf("<caption>Hora oficial-UT y posici&oacute;n</caption>");
  printf("<THEAD>\n");
  printf("<TR><TD width=170>Hora oficial - UT</TD><TD width=120>Latitud</TD><TD width=120>Longitud</TD></TR>");
  printf("</THEAD>\n");
  printf("<TBODY class=\"fondo_tabla\">\n");
  printf("<TR><TD ALIGN=left> %i</TD>\n", horut);
  printf("<TD ALIGN=left> %i. %4.1lf' %c</TD>\n", latgra, minutos_lat, latsig);
  printf("<TD ALIGN=left> %i. %4.1lf' %c</TD></TR></TBODY>\n", longra, minutos_lon, lonsig);
  printf("</TABLE><br><br>\n");

  rellenarListaSol(fecIni);

  printf("</TD></TR></TABLE>\n");
  printf("</BODY>\n");

  free(fecIni);
  return 0;
}

int fecha_valida(int ano, int mes, int dia)
{

  int ain = 2010, afi = 2020;

  if ((ano < ain) || (ano > afi))
  {
    return 0;
  }
  if ((mes < 1) || (mes > 12))
    return 0;
  if ((dia < 1) || (dia > 31))
    return 0;
  switch (mes)
  {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    return (dia <= 31);
  case 4:
  case 6:
  case 9:
  case 11:
    return (dia <= 30);
  case 2:
    if ((ano % 4) != 0)
      return (dia <= 28);
    else if ((ano % 100) != 0)
      return (dia <= 29);
    else if ((ano % 400) != 0)
      return (dia <= 28);
    else
      return (dia <= 29);
  }
  return EXIT_FAILURE;
}

/***********************************************\
|*** Rellenar la lista con los datos         ***|
\***********************************************/

void rellenarListaSol(struct TFecha *fecIni)
{

  struct Tcomsol *sol;
  struct TPosicion posIni, pos;
  struct TFecha fec;
  char *cad = (char *)calloc(sizeof(char), 70);

  fec = *fecIni;
  leerPosicionCommon(&posIni); // Leer situacion inicial
  leerPosicionCommon(&pos);
  pos.dia = fec.dia;
  pos.mes = fec.mes;
  pos.ano = fec.ano;
  escribirPosicionCommon(&pos);
  trad_ker();
  sol = c_fensol();
  strcatSol(sol);

  free(cad);
}

/**********************************************************\
|*** Copia en 'dest' los datos del fen�meno de sol.     ***|
|*** Corresponde a cada una de las l�neas del listBox.  ***|
\**********************************************************/

void strcatSol(Tcomsol *sol)
{

  char *cad = (char *)calloc(sizeof(char), 500);

  // Si se observa el paso por el meridiano
  if (sol->bpm)
  {
    printf("<CENTER><TABLE BORDER=0 CELLSPACING=0 BGCOLOR=\"#CCFFFF\">");

    sprintf(cad, "<TR><TD><b>Paso meridiano Superior:</b></td><td>%2ih %4.1lfm</td></tr>", sol->hpm, sol->mpm);
    printf("%s", cad);

    strcpy(cad, "");

    sprintf(cad, "<TR><TD><b>Altura verdadera:</b></td><td>%2i� %4.1lf\'</td></tr>", sol->gra, sol->mia);
    printf("%s", cad);

    strcpy(cad, "");

    sprintf(cad, "<tr><td><b>Culminaci&oacute;n:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</b></td><td>%s</td></tr>", sol->cul == 'N' ? "Norte" : "Sur");
    printf("%s", cad);

    printf("</table><br>");
  }

  // Comenzamos a chequear los casos negativos
  if (sol->hss[0] == 99)
  {
    printf("<TABLE><TR><TD><B>No hay fen&oacute;menos.</B></TD></TR>");
    printf("<TR><TD><B>Sol siempre por encima del horizonte.</B></TD></TR>");
    printf("</TABLE>");
  }
  else if (sol->hpc[0] == 99)
  {
    printf("<TABLE><TR><TD><B>No hay fen&oacute;menos.</B></TD></TR>");
    printf("<TR><TD><B>Crepusculo civil cont&iacute;nuo.</B></TD></TR>");
    printf("</TABLE>");
  }
  else if (sol->hpn[0] == 88)
  {
    printf("<TABLE><TR><TD><B>No hay fen&oacute;menos.</B></TD></TR>");
    printf("<TR><TD><B>Sol siempre con distancia cenital z > 102�.</B></TD></TR>");
    printf("</TABLE>");
  }
  else if (sol->hpn[0] == 99)
  {
    printf("<TABLE><TR><TD><B>No hay fen&oacute;menos.</B></TD></TR>");
    printf("<TR><TD><B>Crepusculo n&aacute;utico cont&iacute;nuo.</B></TD></TR>");
    printf("</TABLE>");
  }
  //********** Fin de los casos negativos *************
  else
  {

    // Si antes no puse este texto, lo pongo ahora
    /*	  if (!sol->bpm){
          printf("<CENTER><TABLE BORDER=0 CELLSPACING=0 BGCOLOR=\"#CCFFFF\">");
          printf("<TR><TH><font face=\"Arial\"><font size=-1>Horas oficiales de:</font></font></font></TH></TR>");
        } */

    printf("<CENTER><TABLE BORDER=0 CELLSPACING=0 BGCOLOR=\"#CCFFFF\">");

    strcatHora(cad, "<TR><TD><b>Principio crep. n&aacute;utico:</b></TD>", sol->hpn, sol->mpn, 2);
    printf("%s", cad);

    strcatHora(cad, "<tr><td><b>Principio crep. civil:</b></td> ", sol->hpc, sol->mpc, 2);
    printf("%s", cad);

    strcatHora(cad, "<TR><TD><b>Salida:</b></TD>", sol->hss, sol->mss, 2);
    printf("%s", cad);

    strcatHora(cad, "<tr><td><b>Puesta:</b></td>", sol->hps, sol->mps, 2);
    printf("%s", cad);

    strcatHora(cad, "<TR><TD><b>Fin crep&uacute;sculo civil:</b></td>", sol->hfc, sol->mfc, 2);
    printf("%s", cad);

    strcatHora(cad, "<tr><td><b>Fin crep&uacute;sculo n&aacute;utico:</b></td>", sol->hfn, sol->mfn, 2);
    printf("%s", cad);

    printf("</TABLE>");
    printf("<BR>");
    // Si hay salida o puesta, muestro 'acimutes'
    if (sol->hss[0] != -1 || sol->hps[0] != -1)
    {
      strcpy(cad, "");

      printf("<BR><BR><CENTER><TABLE summary=\"Acimutes\">\n");

      printf("<caption>Acimutes</caption>");

      printf("<THEAD><TR><TD>&nbsp;</TD><TD><B>Limbo superior</B></TD><TD><B>Limbo inferior</B></TD></TR>");

      printf("</THEAD>\n");
      printf("<TBODY class=\"fondo_tabla\">\n");

      // Acimutes de salida 1er fenomeno
      printf("<TR><TD><B>Salida:</B></TD>");
      if (sol->hss[0] != -1)
      {
        printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD>", sol->ssg[0], sol->ssm[0], sol->hss[0], sol->mss[0]);
      }
      else
      {
        printf("<TD> --------- </TD>");
      }
      if (sol->hsi[0] != -1)
      {
        printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD></TR>", sol->sig[0], sol->sim[0], sol->hsi[0], sol->msi[0]);
      }
      else
      {
        printf("<TD> --------- </TD></TR>");
      }

      // Acimutes de salida 2� fenomeno, si los hay
      if ((sol->hss[0] != -1 && sol->hss[1] != -1) || (sol->hsi[0] != -1 && sol->hsi[1] != -1))
      {
        printf("<TR><TD><B>y</B></TD>");
        if (sol->hss[1] != -1)
        {
          printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD>", sol->ssg[1], sol->ssm[1], sol->hss[1], sol->mss[1]);
        }
        else
        {
          printf("<TD> --------- </TD>");
        }
        if (sol->hsi[1] != -1)
        {
          printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD></TR>", sol->sig[1], sol->sim[1], sol->hsi[1], sol->msi[1]);
        }
        else
        {
          printf("<TD> --------- </TD></TR>");
        }
      }

      // Acimutes de puesta 1er fenomeno

      printf("<TR><TD><B>Puesta:</B></TD>");
      if (sol->hps[0] != -1)
      {
        printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD>", sol->psg[0], sol->psm[0], sol->hps[0], sol->mps[0]);
      }
      else
      {
        printf("<TD> --------- </TD>");
      }
      if (sol->hpi[0] != -1)
      {
        printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD></TR>", sol->pig[0], sol->pim[0], sol->hpi[0], sol->mpi[0]);
      }
      else
      {
        printf("<TD> -------- </TD></TR>");
      }

      // Acimutes de puesta 2� fenomeno, si los hay
      if ((sol->hps[0] != -1 && sol->hps[1] != -1) || (sol->hpi[0] != -1 && sol->hpi[1] != -1))
      {
        printf("<TR><TD><B>y</B></TD>");
        if (sol->hps[1] != -1)
        {
          printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD>", sol->psg[1], sol->psm[1], sol->hps[1], sol->mps[1]);
        }
        else
        {
          printf("<TD> --------- </TD>");
        }
        if (sol->hpi[1] != -1)
        {
          printf("<TD>%3i�%4.1f' a %2ih %2.0fm</TD></TR>", sol->pig[1], sol->pim[1], sol->hpi[1], sol->mpi[1]);
        }
        else
        {
          printf("<TD> --------- </TD></TR>");
        }
      }
      printf("</TBODY></TABLE><br>");
    }
  }

  free(cad);
}

/********************************************************\
|*** Operaciones con fechas                           ***|
\********************************************************/

TFecha &operator++(TFecha &f, int)
{
  const int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int max;

  if (f.mes == 2 && bisiesto(f.ano))
    max = 29;
  else
    max = dias[f.mes - 1];

  if (++f.dia > max)
  { // Pasar al d�a siguiente
    f.dia = 1;
    f.mes++; // Pasar al mes siguiente
    if (f.mes > 12)
    {
      f.mes = 1;
      f.ano++; // Pasar al a�o siguiente
    }
  }

  return f;
}

int operator<=(TFecha &fi, TFecha &ff)
{
  int siMenor = 0;
  if (fi.ano < ff.ano)
    siMenor = 1;
  else if (fi.ano == ff.ano)
    if (fi.mes < ff.mes)
      siMenor = 1;
    else if (fi.mes == ff.mes)
      if (fi.dia <= ff.dia)
        siMenor = 1;

  return siMenor;
}

int operator-(TFecha &ff, TFecha &fi)
{
  struct tm tmi, tmf;
  time_t timei, timef;
  double dif;

  tmi.tm_year = fi.ano - 1900;
  tmi.tm_mon = fi.mes - 1;
  tmi.tm_mday = fi.dia;
  tmi.tm_hour = 0;
  tmi.tm_min = 0;
  tmi.tm_sec = 1;
  tmi.tm_isdst = -1;

  tmf.tm_year = ff.ano - 1900;
  tmf.tm_mon = ff.mes - 1;
  tmf.tm_mday = ff.dia;
  tmf.tm_hour = 0;
  tmf.tm_min = 0;
  tmf.tm_sec = 1;
  tmf.tm_isdst = -1;

  timei = mktime(&tmi);
  timef = mktime(&tmf);
  dif = difftime(timef, timei);

  // Convertir a d�as
  return int(dif / (60L * 60L * 24L));
}
/**********************************************************\
|*** Copia en 'dest' la cadena 'msg' seguida de una o   ***|
|*** dos hora, segun se especifique en 'num'.           ***|
\**********************************************************/

void strcatHora(char *dest, const char *msg, int *hora, double *min, int num)
{
  char cad[80];

  strcpy(dest, msg);
  if (hora[0] == -1)
    strcat(dest, "<td>-------");
  else
  {
    sprintf(cad, "<td>%2ih %2.0fm", hora[0], float(min[0]));
    strcat(dest, cad);

    if (num == 2 && hora[1] != -1)
    {
      sprintf(cad, "  y  %2ih %2.0fm", hora[1], float(min[1]));
      strcat(dest, cad);
    }
  }
  sprintf(cad, "</TD></TR>");
  strcat(dest, cad);
}
