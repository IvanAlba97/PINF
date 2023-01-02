#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../kernel/externos.h"

int fecha_valida(int ano, int mes, int dia);
void rellenarListaSol(struct TFecha *fecIni, struct TFecha *fecFin);
void strcatSol(char *dest, struct TFecha f, struct Tcomsol *sol);
TFecha &operator++(TFecha &f, int);
int operator<=(TFecha &fi, TFecha &ff);
int operator==(TFecha &fi, TFecha &ff);
int operator!=(TFecha &fi, TFecha &ff);
int operator-(TFecha &ff, TFecha &fi);
void strcatHora(char *dest, int hor, double min, int siDec = 0);

struct TFecha *fecIni, *fecFin;

int main(void)
{
    int latgra, latmin, latseg, longra, lonmin, lonseg, horut, anoi, mesi, diai, anof, mesf, diaf;
    double minutos_lat, minutos_lon;
    char latsig, lonsig;
    char *data = (char *)calloc(sizeof(char), 40);

    printf("%s%c%c\n", "Content-Type:application/json;charset=UTF-8\nAccess-Control-Allow-Origin: *", 13, 10);

    data = getenv("QUERY_STRING");
    if (data == NULL)
    {
        printf("{\"ERROR\":\"Los datos introducidos no son v&aacute;lidos\"");
        exit(EXIT_FAILURE);
    }
    else if (sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&horut=%i&anoi=%i&mesi=%i&diai=%i&anof=%i&mesf=%i&diaf=%i", &latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &horut, &anoi, &mesi, &diai, &anof, &mesf, &diaf) != 15)
    {
        printf("{\"ERROR\":\"Los datos introducidos no son válidos.\"}");
        exit(EXIT_FAILURE);
    }
    else
    {
        if ((latgra < 0) || (latgra > 90))
        {
            printf("{\"ERROR\":\"Los grados deben estar entre 0� y 90�\"}");
            exit(EXIT_FAILURE);
        }
        if ((latmin < 0) || (latmin > 59))
        {
            printf("{\"ERROR\":\"Los minutos deben estar entre 0' y 59'\"}");
            exit(EXIT_FAILURE);
        }
        if ((latseg < 0) || (latseg > 59))
        {
            printf("{\"ERROR\":\"Los segundos deben estar entre 0'' y 59''\"}");
            exit(EXIT_FAILURE);
        }
        if ((longra < 0) || (longra > 180))
        {
            printf("{\"ERROR\":\"Los grados deben estar entre 0� y 180�\"}");
            exit(EXIT_FAILURE);
        }
        if ((lonmin < 0) || (lonmin > 59))
        {
            printf("{\"ERROR\":\"Los minutos deben estar entre 0' y 59'\"}");
            exit(EXIT_FAILURE);
        }
        if ((lonseg < 0) || (lonseg > 59))
        {
            printf("{\"ERROR\":\"Los segundos deben estar entre 0'' y 59''\"}");
            exit(EXIT_FAILURE);
        }
        if ((latsig != 'N') && (latsig != 'S'))
        {
            printf("{\"ERROR\":\"La latitud debe ser Norte o Sur\"}");
            exit(EXIT_FAILURE);
        }
        if ((lonsig != 'W') && (lonsig != 'E'))
        {
            printf("{\"ERROR\":\"La longitud debe ser Este u Oeste\"}");
            exit(EXIT_FAILURE);
        }
        if ((latgra == 90) && ((latmin > 0) || (latseg > 0)))
        {
            printf("{\"ERROR\":\"La latitud debe ser menor o igual a 90�\"}");
            exit(EXIT_FAILURE);
        }
        if ((longra == 180) && ((lonmin > 0) || (lonseg > 0)))
        {
            printf("{\"ERROR\":\"La longitud debe ser menor o igual a 180�\"}");
            exit(EXIT_FAILURE);
        }
        if ((anof - anoi) > 1)
        {
            printf("{\"ERROR\":\"No debe haber dos años o más para realizar los cálculos\"}");
            exit(EXIT_FAILURE);
        }
        if (!(fecha_valida(anoi, mesi, diai)) || !(fecha_valida(anof, mesf, diaf)))
        {
            printf("\"ERROR\":\"La fecha debe estar dentro del intervalo de fechas válidas\"}");
            exit(EXIT_FAILURE);
        }
        if ((anoi * 366 + 31 * mesi + diai) > (anof * 366 + 31 * mesf + diaf))
        {
            printf("\"ERROR\":\"La fecha inicio debe ser menor que la fecha fin\"}");
            exit(EXIT_FAILURE);
        }
        if ((horut < -11) || (horut > 12))
        {
            printf("\"ERROR\">La diferencia horaria (Hora - UT) debe estar entre -11 y 12\"}");
            exit(EXIT_FAILURE);
        }
    }
    printf("{\"diaI\": %i, \"mesI\":%i, \"anoI\":%i, \"diaF\":%i, \"mesF\":%i, \"anoF\":%i, ", diai, mesi, anoi, diaf, mesf, anof);

    minutos_lat = latmin + latseg / 60.;
    minutos_lon = lonmin + lonseg / 60.;

    fecIni = (struct TFecha *)calloc(sizeof(struct TFecha), 1);
    fecFin = (struct TFecha *)calloc(sizeof(struct TFecha), 1);

    fecIni->dia = diai;
    fecIni->mes = mesi;
    fecIni->ano = anoi;
    fecFin->dia = diaf;
    fecFin->mes = mesf;
    fecFin->ano = anof;

    preferen(latgra, minutos_lat, latsig, longra, minutos_lon, lonsig, horut);

    printf("\"tabla1\":{\"horut\":%i, \"latgra\":%i, \"minutos_lat\": %4.1lf, \"latsig\":\"%c\", \"longra\":%i, \"minutos_lon\": %4.1lf, \"lonsig\":\"%c\"},", horut, latgra, minutos_lat, latsig, longra, minutos_lon, lonsig);
    rellenarListaSol(fecIni, fecFin);
    free(fecIni);
    free(fecFin);
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

void rellenarListaSol(struct TFecha *fecIni, struct TFecha *fecFin)
{
    struct Tcomsol *sol;
    struct TPosicion posIni, pos;
    struct TFecha fec;
    char *cad = (char *)calloc(sizeof(char), 70);
    /*mostrarMsgEsperar ();*/
    fec = *fecIni;
    leerPosicionCommon(&posIni); // Leer situacion inicial
    printf("\"DatosFecha\": [");

    while (fec <= *fecFin)
    {
        leerPosicionCommon(&pos);
        pos.dia = fec.dia;
        pos.mes = fec.mes;
        pos.ano = fec.ano;
        escribirPosicionCommon(&pos);
        trad_ker();
        sol = c_fensol();
        // printf("\"fecha%i\":", iterador);
        strcatSol(cad, fec, sol);
        if (fec != *fecFin)
            printf(",");
        strcpy(cad, "");
        fec++; // Pasar al siguiente d�a
    };
    printf("]");

    /*	borrarMsgEsperar ();
            listBox->newList (lista);
    escribirPosicionCommon (&posIni);  // Escribir situaci�n inicial
    trad_ker();
    msgSol->setState (sfVisible, siMsgSol);*/
    free(cad);
}

/**********************************************************\
|*** Copia en 'dest' los datos del fen�meno de sol.     ***|
|*** Corresponde a cada una de las l�neas del listBox.  ***|
\**********************************************************/

void strcatSol(char *dest, TFecha f, Tcomsol *sol)
{

    printf("{ \"dia\":%2i, \"mes\": %2i, \"ano\":%4i,", f.dia, f.mes, f.ano);

    // Si paso por el meridiano visible
    if (sol->bpm)
        if (sol->hss[0] == 99)
        { // siempre sobre el horizonte
            char cad[60];
            printf("\"hPasoMeridiano\":%2i, \"mPasoMeridiano\": %4.1lf", sol->hpm, sol->mpm);
            /*strcat (dest, cad);*/
            /*	siMsgSol = True;*/
        }
        else
        {
            // Escribir salida
            if (sol->hss[1] == -1)
            {
                /*strcat (dest, "    ");*/
                strcpy(dest, "\"SalidaLimboSuperior\":");

                strcatHora(dest, sol->hss[0], sol->mss[0]);
                printf("%s,", dest);
                /*strcat (dest, "     ");*/
            }
            else
            {
                strcpy(dest, "\"SalidaLimboSuperior1\":");
                strcatHora(dest, sol->hss[0], sol->mss[0]);
                printf("%s,", dest);
                strcpy(dest, "\"SalidaLimboSuperior2\":");
                strcatHora(dest, sol->hss[1], sol->mss[1]);
                printf("%s,", dest);
            }

            strcpy(dest, "\"PasoMeridiano\":");
            // Escribir paso meridiano
            strcatHora(dest, sol->hpm, sol->mpm, 1);
            printf("%s,", dest);
            // Escribir puesta
            if (sol->hps[1] == -1)
            {
                /*	strcat (dest, "    ");*/
                strcpy(dest, "\"PuestaLimboSuperior\":");
                strcatHora(dest, sol->hps[0], sol->mps[0]);
                /*	strcat (dest, "     ");*/
                printf("%s}", dest);
            }
            else
            {
                strcpy(dest, "\"PuestaLimboSuperior1\":");
                strcatHora(dest, sol->hps[0], sol->mps[0]);
                printf("%s,", dest);
                strcpy(dest, "\"PuestaLimboSuperior2\":");
                strcatHora(dest, sol->hps[1], sol->mps[1]);
                printf("%s}", dest);
            }
        }
    else
    {
        strcpy(dest, "");
        strcat(dest, "\"sinFenomeno\": \"Sol siempre por debajo del horizonte\"} ");
        printf("%s", dest);
    }
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
int operator==(TFecha &fi, TFecha &ff)
{
    return (fi.ano == ff.ano && fi.mes == ff.mes && fi.dia == ff.dia);
}
int operator!=(TFecha &fi, TFecha &ff)
{
    return !(fi == ff);
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
|*** Copia en 'dest' los datos de la hora 'hor' y 'min' ***|
\**********************************************************/

void strcatHora(char *dest, int hor, double min, int siDec)
{
    char cad[80];
    if (hor == -1)
        strcat(dest, "{}");
    else
    {
        if (siDec)
            sprintf(cad, "{\"hora\": %2i, \"minutos\": %4.1lf } ", hor, min);
        else
            sprintf(cad, "{\"hora\": %2i, \"minutos\": %2.0lf } ", hor, min);
        strcat(dest, cad);
    }
}
