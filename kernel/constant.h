#ifndef M_PI
const double M_PI = 3.14159265358979323846;
#endif

const double UA_KM = 1.4959787e+11; // UA en km
const double R_T_KM = 6.378140e+06; // radio terrestre en km
const double R_T_UA = 6.378140e+06/1.4959787e+11;    //R_T_KM/UA_KM; // radio terrestre en UA
const double R_L_UA = 1.16178124728647e-05; // radio lunar en UA
const double R_H_UA = 4.65247265886874e-03; // radio solar en UA
const double GRADOS = M_PI/180.;
const double ORTO_H = (90. + 50./60.)*M_PI/180.;  //GRADOS;
const double CIVIL = 96.*M_PI/180.;
const double NAUTICO = 102.*M_PI/180.;
const double AS_RAD = (1./60./60.)*M_PI/180.; // 1" en radianes
const double MIN_DIA = 1./60./24.;
