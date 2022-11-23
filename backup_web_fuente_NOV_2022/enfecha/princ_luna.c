#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../kernel/externos.h"

int fecha_valida(int ano, int mes, int dia);
void rellenarListaLuna(struct TFecha* fecIni);
TFecha& operator++(TFecha& f, int);
int operator<=(TFecha& fi, TFecha& ff);
int operator-(TFecha& ff, TFecha& fi);
void strcatHora(char* dest, const char* msg, int* hora, double* min, int num = 1);
void fase(int edad);

struct TFecha* fecIni;

int main(void) {
    int latgra, latmin, latseg, longra, lonmin, lonseg, horut, anoi, mesi, diai;
    double minutos_lat, minutos_lon;
    char latsig, lonsig;

    char* data = (char*)calloc(sizeof(char), 40);

    printf("%s%c%c\n", "Content-Type:application/json;charset=UTF-8", 13, 10);

    data = getenv("QUERY_STRING");
    if (data == NULL) {
        printf("{\"ERROR\":\"Los datos introducidos no son válidos.\"}");
        exit(EXIT_FAILURE);
    } else if (sscanf(data, "latgra=%i&latmin=%i&latseg=%i&latsig=%c&longra=%i&lonmin=%i&lonseg=%i&lonsig=%c&horut=%i&anoi=%i&mesi=%i&diai=%i", &latgra, &latmin, &latseg, &latsig, &longra, &lonmin, &lonseg, &lonsig, &horut, &anoi, &mesi, &diai) != 12) {
        printf("{\"ERROR\":\"Los datos introducidos no son válidos.\"}");
        exit(EXIT_FAILURE);
    } else {
        if ((latgra < 0) || (latgra > 90)) {
            printf("{\"ERROR\":\"Los grados deben estar entre 0� y 90�.\"}");
            exit(EXIT_FAILURE);
        }
        if ((latmin < 0) || (latmin > 59)) {
            printf("{\"ERROR\":\"Los minutos deben estar entre 0' y 59'\"}");
            exit(EXIT_FAILURE);
        }
        if ((latseg < 0) || (latseg > 59)) {
            printf("{\"ERROR\":\"Los segundos deben estar entre 0'' y 59''\"}");
            exit(EXIT_FAILURE);
        }
        if ((longra < 0) || (longra > 180)) {
            printf("{\"ERROR\":\"Los grados deben estar entre 0� y 180�\"}");
            exit(EXIT_FAILURE);
        }
        if ((lonmin < 0) || (lonmin > 59)) {
            printf("{\"ERROR\":\"Los minutos deben estar entre 0' y 59'\"}");
            exit(EXIT_FAILURE);
        }
        if ((lonseg < 0) || (lonseg > 59)) {
            printf("{\"ERROR\":\"Los segundos deben estar entre 0'' y 59''\"}");
            exit(EXIT_FAILURE);
        }
        if ((latsig != 'N') && (latsig != 'S')) {
            printf("{\"ERROR\":\"La latitud debe ser Norte o Sur\"}");
            exit(EXIT_FAILURE);
        }
        if ((lonsig != 'W') && (lonsig != 'E')) {
            printf("{\"ERROR\":\"La longitud debe ser Este u Oeste\"}");
            exit(EXIT_FAILURE);
        }
        if ((latgra == 90) && ((latmin > 0) || (latseg > 0))) {
            printf("{\"ERROR\":\"La latitud debe ser menor o igual a 90�\"}");
            exit(EXIT_FAILURE);
        }
        if ((longra == 180) && ((lonmin > 0) || (lonseg > 0))) {
            printf("{\"ERROR\":\"La longitud debe ser menor o igual a 180�\"}");
            exit(EXIT_FAILURE);
        }
        if (!(fecha_valida(anoi, mesi, diai))) {
            printf("{\"ERROR\":\"La fecha debe estar dentro del intervalo de fechas v&aacute;lidas\"}");
            exit(EXIT_FAILURE);
        }
        if ((horut < -11) || (horut > 12)) {
            printf("{\"ERROR\":\"La diferencia horaria (Hora - UT) debe estar entre -11 y 12\"}");
            exit(EXIT_FAILURE);
        }
    }


    minutos_lat = latmin + latseg / 60.;
    minutos_lon = lonmin + lonseg / 60.;

    fecIni = (struct TFecha*)calloc(sizeof(struct TFecha), 1);

    fecIni->dia = diai;
    fecIni->mes = mesi;
    fecIni->ano = anoi;

    preferen(latgra, minutos_lat, latsig, longra, minutos_lon, lonsig, horut);

    // printf("<BR><CENTER><TABLE BORDER=0 CELLSPACING=0 BGCOLOR=\"#CCFFFF\">");

    printf("{\"tabla1\":{\"diai\":%i,\"mesi\":%i,\"anoi\":%i,\"horut\":%i, \"latgra\":%i, \"minutos_lat\": %4.1lf, \"latsig\":\"%c\", \"longra\":%i, \"minutos_lon\": %4.1lf, \"lonsig\":\"%c\"},", diai, mesi, anoi, horut, latgra, minutos_lat, latsig, longra, minutos_lon, lonsig);

    rellenarListaLuna(fecIni);

    free(fecIni);
    return 0;
}

int fecha_valida(int ano, int mes, int dia) {
    int ain = 2010, afi = 2020;

    if ((ano < ain) || (ano > afi)) {
        return 0;
    }
    if ((mes < 1) || (mes > 12))
        return 0;
    if ((dia < 1) || (dia > 31))
        return 0;
    switch (mes) {
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

/********************************************************\
|*** Operaciones con fechas                           ***|
\********************************************************/

TFecha& operator++(TFecha& f, int) {
    const int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max;

    if (f.mes == 2 && bisiesto(f.ano))
        max = 29;
    else
        max = dias[f.mes - 1];

    if (++f.dia > max) {  // Pasar al d�a siguiente
        f.dia = 1;
        f.mes++;  // Pasar al mes siguiente
        if (f.mes > 12) {
            f.mes = 1;
            f.ano++;  // Pasar al a�o siguiente
        }
    }

    return f;
}

int operator<=(TFecha& fi, TFecha& ff) {
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

int operator-(TFecha& ff, TFecha& fi) {
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

void strcatHora(char* dest, const char* msg, int* hora, double* min, int num) {
    char cad[80];

    strcpy(dest, msg);
    if (hora[0] == -1)
        strcat(dest, "\"error\": -1");
    else {
        sprintf(cad, "{\"hora1\": %2i, \"minutos1\": %2.0f,", hora[0], float(min[0]));
        strcat(dest, cad);

        if (num == 2 && hora[1] != -1) {
            sprintf(cad, "\"hora2\": %2i, \"minutos2\": %2.0f", hora[1], float(min[1]));
            strcat(dest, cad);
        }
    }
    sprintf(cad, "},");
    strcat(dest, cad);
}

void rellenarListaLuna(struct TFecha* fecIni) {
    struct Tcomfel* comfel;
    struct TPosicion posIni, pos;
    struct TFecha fec;

    fec = *fecIni;
    leerPosicionCommon(&posIni);  // Leer situacion inicial
    leerPosicionCommon(&pos);
    pos.dia = fec.dia;
    pos.mes = fec.mes;
    pos.ano = fec.ano;
    escribirPosicionCommon(&pos);
    trad_ker();
    printf("\"Luna\": {");
    comfel = c_fenlun();

    printf("\"edad0h\": %.1lf,", comfel->eda);
    // printf("<TABLE><TR><TD><B>Edad (a 0h):</B> %.1lf d&iacute;as</TD>", comfel->eda);

    // fase((int)comfel->eda);
    if (comfel->bpm != -99 && (comfel->bpm != 99 || comfel->hpm != -1)) {

        if (comfel->hpm != -1) {
            printf("\"hPasoMeridiano\":%2i,\"mPasoMeridiano\": %4.1lf, ", comfel->hpm, comfel->mpm);
            printf("\"gAlturaMeridiano\": %i, \"mAlturaMeridiano\": %.1lf, ", comfel->gam, comfel->mam);

            printf("\"culminacion\":%s},", comfel->cul == 'N' ? "\"Norte\"" : "\"Sur\"");
        }
        // Si no hay, escribimos una l�nea
        // else {
        //     printf("<TR><TD COLSPAN=2><B>Paso meridiano lugar.:</B> --------- ");
        //     printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Altura verdadera.:</B> --------- ");
        //     printf("<BR>&nbsp;&nbsp;&nbsp;&nbsp;<B>Culminaci&oacute;n......:</B> --------- </TD></TR>");
        // }

        if (comfel->bpm != 99) {  /////////////********

            // Si hay salida de la luna mandamos los datos
            if (comfel->hsa != -1) {
                printf("\"hSalida\": %2i, \"mSalida\": %2.0lf, ", comfel->hsa, comfel->msa);
                printf("\"gAcimutSalida\": %3i, \"mAcimutSalida\":%4.1lf, ", comfel->gzs, comfel->mzs);

            } 
            // else {
            //     printf("<TR><TD><B>Salida...............:</B> --------- </TD>");
            //     printf("<TD><B>Acimut:</B> --------- </TD></TR>");
            // }

            // Si hay puesta de la luna mandamos los datos
            if (comfel->hpu != -1) {
                printf("\"hPuesta\": %2i, \"mPuesta\": %2.0lf, ", comfel->hpu, comfel->mpu);
                printf("\"gAcimutPuesta\": %3i, \"mAcimutPuesta\":%4.1lf, }", comfel->gzp, comfel->mzp);
            } 
            // else {
            //     printf("<TR><TD><B>Puesta...............:</B> ---------- </TD>");
            //     printf("<TD><B>Acimut:</B> --------- </TD></TR>");
            // }
        } else {
            printf("\"sinFenomeno\":\"Luna siempre por encima del horizonte\",}, ");
        }
    }
    // Si no hay fenomenos, indicar la causa
    else {
        if (comfel->bpm == 99)
            printf("\"sinFenomeno\":\"Luna siempre por encima del horizonte\",}, ");
        else
            printf("\"sinFenomeno\":\"Luna siempre por debajo del horizonte\", }, ");
    }
}

// void fase(int edad) {
//     if (edad == 0)
//         printf("<TD><IMG SRC=\"../../fases/e0.gif\"></TD>");
//     if (edad == 1)
//         printf("<TD><IMG SRC=\"../../fases/e1.gif\"></TD>");
//     if (edad == 2)
//         printf("<TD><IMG SRC=\"../../fases/e2.gif\"></TD>");
//     if (edad == 3)
//         printf("<TD><IMG SRC=\"../../fases/e3.gif\"></TD>");
//     if (edad == 4)
//         printf("<TD><IMG SRC=\"../../fases/e4.gif\"></TD>");
//     if (edad == 5)
//         printf("<TD><IMG SRC=\"../../fases/e5.gif\"></TD>");
//     if (edad == 6)
//         printf("<TD><IMG SRC=\"../../fases/e6.gif\"></TD>");
//     if (edad == 7)
//         printf("<TD><IMG SRC=\"../../fases/e7.gif\"></TD>");
//     if (edad == 8)
//         printf("<TD><IMG SRC=\"../../fases/e8.gif\"></TD>");
//     if (edad == 9)
//         printf("<TD><IMG SRC=\"../../fases/e9.gif\"></TD>");
//     if (edad == 10)
//         printf("<TD><IMG SRC=\"../../fases/e10.gif\"></TD>");
//     if (edad == 11)
//         printf("<TD><IMG SRC=\"../../fases/e11.gif\"></TD>");
//     if (edad == 12)
//         printf("<TD><IMG SRC=\"../../fases/e12.gif\"></TD>");
//     if (edad == 13)
//         printf("<TD><IMG SRC=\"../../fases/e13.gif\"></TD>");
//     if (edad == 14)
//         printf("<TD><IMG SRC=\"../../fases/e14.gif\"></TD>");
//     if (edad == 15)
//         printf("<TD><IMG SRC=\"../../fases/e15.gif\"></TD>");
//     if (edad == 16)
//         printf("<TD><IMG SRC=\"../../fases/e16.gif\"></TD>");
//     if (edad == 17)
//         printf("<TD><IMG SRC=\"../../fases/e17.gif\"></TD>");
//     if (edad == 18)
//         printf("<TD><IMG SRC=\"../../fases/e18.gif\"></TD>");
//     if (edad == 19)
//         printf("<TD><IMG SRC=\"../../fases/e19.gif\"></TD>");
//     if (edad == 20)
//         printf("<TD><IMG SRC=\"../../fases/e20.gif\"></TD>");
//     if (edad == 21)
//         printf("<TD><IMG SRC=\"../../fases/e21.gif\"></TD>");
//     if (edad == 22)
//         printf("<TD><IMG SRC=\"../../fases/e22.gif\"></TD>");
//     if (edad == 23)
//         printf("<TD><IMG SRC=\"../../fases/e23.gif\"></TD>");
//     if (edad == 24)
//         printf("<TD><IMG SRC=\"../../fases/e24.gif\"></TD>");
//     if (edad == 25)
//         printf("<TD><IMG SRC=\"../../fases/e25.gif\"></TD>");
//     if (edad == 26)
//         printf("<TD><IMG SRC=\"../../fases/e26.gif\"></TD>");
//     if (edad == 27)
//         printf("<TD><IMG SRC=\"../../fases/e27.gif\"></TD>");
//     if (edad == 28)
//         printf("<TD><IMG SRC=\"../../fases/e28.gif\"></TD>");
//     if (edad == 29)
//         printf("<TD><IMG SRC=\"../../fases/e29.gif\"></TD>");
//     if (edad == 30)
//         printf("<TD><IMG SRC=\"../../fases/e29.gif\"></TD>");
// }
