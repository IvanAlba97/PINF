#include "string.h" // strcpy()

struct Testran {
	char* noe[99];
	char* mve[99];
	double are[99], ape[99], dee[99], dpe[99];
};

struct Testran estran = { {
       "Alpheratz", "Caph", "Algenib", "Ankaa", "Schedar",
	   "Diphda", "Navi", // "g-Cassiopeiae",
	   "Mirach", "Achernar", "Almak",
	   "Polaris", "Hamal", "Acamar", "Menkar", "Algol",
	   "Mirfak", "Alcyone", "Zaurak", //"g-Eridani",
	   "Aldebaran", "Rigel",
	   "Capella", "Bellatrix", "Elnath", "Mintaka", //"d-Orionis",
	   "Alnilam",
	   "Alnitak", "Saiph", //"k-Orionis",
	   "Betelgeuse", "Menkalinan", "Mirzam",
	   "Canopus", "Alhena", "Sirius", "Adhara", "Wezen",
	   "Aludra", //"y-Canis Majoris",
	   "Castor", "Procyon", "Pollux", "z-Puppis",
	   "Regor", //"g-Velorum",
	   "Avior", "d-Velorum", "z-Hydrae", "Suhail",
	   "Miaplacidus", "Aspidiske", //"i-Carinae",
	   "a-Lyncis", "Alphard", "Regulus",
	   "m-Velorum", "n-Hydrae", "Merak", "Dubhe", "Denebola",
	   "Gienah", "Acrux", "Gacrux", "Muhlifain", "Mimosa",
	   "Alioth", "Cor Caroli", "Vindemiatrix", //"e-Virginis",
	   "Mizar", "Spica",
	   "Alkaid", "Hadar", "Menkent", "Arcturus", "Rigil Kent",
	   "Zubenelgenubi", "Kochab", "Zubeneschamali", //"b-Librae",
	   "Alphecca", "Unukalhai", //"a-Serpentis",
	   "Antares", "Atria", "e-Scorpii", "Sabik", "Rasalgethi", //"a-Herculis",
	   "Shaula", "Rasalhague", "t-Scorpii", "Eltanin", "Kaus Australis",
	   "Vega", "Nunki", "Altair", "Sadr", //"g-Cygni",
	   "Peacock",
	   "Deneb", "Alderamin", "Enif", "DenebAlgedi", //"d-Capricorni",
	   "Al Na`ir",
	   "b-Gruis", "Fomalhaut", "Scheat", "Markab"
	  },
      {
       " 2.1 "," 2.3 "," 2.8 "," 2.4 "," 2.2 "," 2.0 ",
       " 1.6v"," 2.1 "," 0.5 "," 2.3 "," 2.0 "," 2.0 "," 3.3 "," 2.5 ",
       " 2.1v"," 1.8 "," 2.9 "," 3.0 "," 0.9 "," 0.1 "," 0.1 "," 1.6 ",
       " 1.7 "," 2.2 "," 1.7 "," 2.1 "," 2.1 "," 0.4v"," 1.9 "," 2.0 ",
       "-0.7 "," 1.9 ","-1.5 "," 1.5 "," 1.9 "," 2.5 "," 2.0 "," 0.4 ",
	   " 1.1 "," 2.3 "," 1.8 "," 1.9 "," 2.0 "," 3.1 "," 2.2 "," 1.7 ",
       " 2.3 "," 3.1 "," 2.0 "," 1.4 "," 2.8 "," 3.1 "," 2.4 "," 1.8 ",
	   " 2.1 "," 2.6 "," 1.3 "," 1.6v"," 2.4 "," 1.3 "," 1.8 "," 2.9 ",
       " 2.8 "," 2.3 "," 1.0 "," 1.9 "," 0.6 "," 2.1 "," 0.0 "," 0.0 ",
       " 2.8 "," 2.1 "," 2.6 "," 2.2 "," 2.7 "," 0.9v"," 1.9 "," 2.3 ",
       " 2.6 "," 3.5 "," 1.6 "," 2.1 "," 1.9 "," 2.2 "," 1.9 "," 0.0 ",
       " 2.0 "," 0.8 "," 2.2 "," 1.9 "," 1.3 "," 2.4 "," 0.7v"," 2.9 ",
       " 1.7 "," 2.1v"," 1.2 "," 2.4v"," 2.5 "
	 },

     { 0.3659846358353860E-01, 0.4004767051779240E-01,
       0.5775250861617938E-01, 0.1146848579280258E+00,
	   0.1767473116879008E+00, 0.1901952190186214E+00,
       0.2474386005475837E+00, 0.3042640484427454E+00,
       0.4263586289880608E+00, 0.5406130450893135E+00,
       0.6624036474565732E+00, 0.5548985650168872E+00,
       0.7778129624682811E+00, 0.7953445766384076E+00,
       0.8210414955478331E+00, 0.8915261810573111E+00,
       0.9925885987294167E+00, 0.1038599113914596E+01,
       0.1203930808741619E+01, 0.1372430057994855E+01,
       0.1381817384098759E+01, 0.1418651394409265E+01,
       0.1423716776230865E+01, 0.1448652222532056E+01,
       0.1467008068441437E+01, 0.1486841626450839E+01,
       0.1517373761886759E+01, 0.1549729257336647E+01,
	   0.1568739747159630E+01, 0.1669841507461958E+01,
       0.1675306569682265E+01, 0.1735346332283183E+01,
       0.1767790984969027E+01, 0.1826599635948820E+01,
	   0.1869209813418801E+01, 0.1937729912689002E+01,
       0.1983566476725399E+01, 0.2004082531194384E+01,
       0.2030323047443754E+01, 0.2110034125155691E+01,
       0.2135989570960569E+01, 0.2192630450287331E+01,
       0.2289453899538655E+01, 0.2336096223913057E+01,
       0.2391084785492547E+01, 0.2413787228459915E+01,
       0.2430763973372012E+01, 0.2448064476860353E+01,
       0.2476567448874673E+01, 0.2654523255625475E+01,
       0.2822075809203609E+01, 0.2834523351984728E+01,
	   0.2887827743558096E+01, 0.2896058716310501E+01,
       0.3093856444106705E+01, 0.3210559775314663E+01,
       0.3257647667702687E+01, 0.3277577727875315E+01,
       0.3322716014766809E+01, 0.3349813124068648E+01,
       0.3377339220756215E+01, 0.3386059758363805E+01,
       0.3412889686845983E+01, 0.3507787383433889E+01,
       0.3513317750057042E+01, 0.3610826895538243E+01,
       0.3681874449731489E+01, 0.3694349408726275E+01,
       0.3733526669001688E+01, 0.3837970662099532E+01,
       0.3887190983223233E+01, 0.3886437073708424E+01,
       0.4001197926180963E+01, 0.4078345478831982E+01,
       0.4120146914359820E+01, 0.4317103829788875E+01,
	   0.4401129070523535E+01, 0.4407670491837957E+01,
       0.4495953972337221E+01, 0.4514504422458199E+01,
       0.4597236083328921E+01, 0.4603020540802344E+01,
       0.4613425248416056E+01, 0.4697580370735884E+01,
       0.4817859736137073E+01, 0.4873565191706819E+01,
       0.4953529778492610E+01, 0.5195772606579058E+01,
       0.5332977447845566E+01, 0.5347896231403405E+01,
       0.5416768741738405E+01, 0.5578855433153659E+01,
       0.5690585230491902E+01, 0.5703041354475176E+01,
       0.5795511225351504E+01, 0.5945759566616637E+01,
       0.6011136109737841E+01, 0.6037854846202257E+01,
       0.6042159555358196E+01
	  },

      { 0.7555821220092119E-04,
        0.4964734501402204E-03,  0.1381718991162178E-05,
        0.1332995216210669E-03,  0.4625122517784974E-04,
        0.1190459993964466E-03,  0.2581632851908280E-04,
        0.1059560300064891E-03,  0.8530296719122288E-04,
       	0.2937970907523789E-04,  0.1445496230912137E-02,
     	  0.1005745981461733E-03, -0.2843432239707429E-04,
       -0.4581489286485116E-05,  0.2254383617159343E-05,
        0.1788962483294188E-04,  0.9890199094634537E-05,
        0.3054326190990077E-04,  0.3192498090106295E-04,
		0.2181661564992913E-06,  0.5294165397716134E-04,
       -0.4290601077819394E-05,  0.1229002681612674E-04,
        0.7272205216643041E-06,  0.4363323129985825E-06,
        0.3345214399655798E-05,  0.9453866781635954E-06,
        0.1258091502479246E-04, -0.3934263022203886E-04,
       -0.3199770295322938E-05,  0.1781690278077545E-04,
        0.2130756128476411E-04, -0.2797617346842578E-03,
        0.2254383617159343E-05, -0.1745329251994330E-05,
       -0.2254383617159343E-05, -0.9795660426818177E-04,
       -0.3457933580513766E-03, -0.3447025272688801E-03,
       -0.1730784841561044E-04, -0.2690715930157925E-05,
       -0.2516183004958492E-04,  0.1752601457210973E-04,
	   -0.4836016469067623E-04, -0.1250819297262603E-04,
       -0.2260201381332657E-03, -0.1890773356327191E-04,
       -0.1300997513257440E-03, -0.6763150851478028E-05,
       -0.1231184343177667E-03,  0.4930555136883983E-04,
        0.4756022211684549E-04,  0.7184938754043325E-04,
       -0.1218094373787709E-03, -0.2488548625135249E-03,
       -0.8173958663506779E-04, -0.3810635533520954E-04,
        0.2072578486743267E-04, -0.1441351073938650E-03,
       -0.4588761491701759E-04,  0.9657488527701959E-04,
       -0.1444987176546972E-03, -0.1348266847165620E-03,
        0.1026108156068333E-03, -0.2021673050226766E-04,
       -0.9082984315587159E-04, -0.3097959422289936E-04,
	   -0.3121957699504858E-03, -0.5609779104118442E-03,
       -0.3623448971244562E-02, -0.5337798629015992E-04,
       -0.5548692580298640E-04, -0.4719661185601334E-04,
        0.6588617926278596E-04,  0.6668612183661669E-04,
       -0.5163265703816559E-05,  0.1890773356327191E-04,
       -0.3585197171805019E-03,  0.1748965354602651E-03,
       -0.1890773356327190E-05, -0.7999425738307346E-06,
        0.5977752688080579E-04,  0.9890199094634537E-05,
       -0.5890486225480864E-05, -0.2247111411942700E-04,
        0.1255182620392589E-03,  0.7199483164476611E-05,
        0.2639083273119760E-03,  0.2545271825825064E-05,
        0.5963208277647293E-05,  0.1963495408493621E-05,
		0.1586067957749847E-03,  0.1505346479845110E-04,
        0.1328631893080683E-03,  0.9155706367753589E-04,
        0.9708393964218460E-04,  0.1855139550765640E-03,
        0.1040652566501619E-03,  0.3170681474456366E-04
        },

      {
        0.5077239394613121E+00,
        0.1032358277082461E+01,  0.2650030366039213E+00,
       -0.7383800114574515E+00,  0.9867629078524164E+00,
       -0.3139256821274208E+00,  0.1059706665315218E+01,
        0.6216957334271620E+00, -0.9989691588644473E+00,
		  0.7387929757510207E+00,  0.1557952254903998E+01,
     	  0.4094962273826539E+00, -0.7034499614353993E+00,
        0.7137877890018023E-01,  0.7148113761267287E+00,
        0.8702422059581331E+00,  0.4207134584852215E+00,
       -0.2357683353007033E+00,  0.2881412058671869E+00,
       -0.1431459905216654E+00,  0.8028170341460330E+00,
        0.1108222988492580E+00,  0.4992934658791303E+00,
       -0.5220861569132373E-02, -0.2097798494434585E-01,
       -0.3390607504618084E-01, -0.1687672784968378E+00,
        0.1292772649157417E+00,  0.7844807989500530E+00,
       -0.3133902054166353E+00, -0.9197133696804398E+00,
        0.2862215376154655E+00, -0.2917511285367285E+00,
	   -0.5056582453288406E+00, -0.4606483855814718E+00,
       -0.5114359154107273E+00,  0.5565589791526351E+00,
        0.9119374430491241E-01,  0.4891491759342262E+00,
       -0.6981881331102131E+00, -0.8261802539200696E+00,
       -0.1038638214137977E+01, -0.9548531501009400E+00,
        0.1037689385282678E+00, -0.7580419696644255E+00,
       -0.1216794830715495E+01, -0.1034548956181923E+01,
        0.6002632841381440E+00, -0.1511219997591752E+00,
        0.2088668968005611E+00, -0.8625521883111100E+00,
       -0.2826330921919971E+00,  0.9840585686578192E+00,
        0.1077756424107030E+01,  0.2543301058211354E+00,
       -0.3061645423133788E+00, -0.1101286177380528E+01,
	   -0.9968132893872894E+00, -0.8545101959316010E+00,
       -0.1041765019974293E+01,  0.9766836799035171E+00,
        0.6687820986520909E+00,  0.1912729598317280E+00,
        0.9586287820866850E+00, -0.1948015792469475E+00,
        0.8606797893932967E+00, -0.1053707580825169E+01,
       -0.6347763943944421E+00,  0.3347963778041371E+00,
       -0.1061778031767759E+01, -0.2799819370582178E+00,
        0.1294257536499919E+01, -0.1637629831990571E+00,
        0.4662595706452655E+00,  0.1121486036366693E+00,
       -0.4613251854803007E+00, -0.1204761124892571E+01,
       -0.5985302206722817E+00, -0.2744443951925846E+00,
        0.2511422619423677E+00, -0.6475836689269446E+00,
		0.2192140327896414E+00, -0.7504538113718034E+00,
        0.8986516574133664E+00, -0.6001253061645002E+00,
        0.6769025338852033E+00, -0.4589645307042421E+00,
        0.1547817612751348E+00,  0.7026120579503377E+00,
       -0.9902143934109713E+00,  0.7902914363622551E+00,
        0.1092324396485219E+01,  0.1723508757834952E+00,
       -0.2814744359755134E+00, -0.8196240215476892E+00,
       -0.8182912687383190E+00, -0.5170057943488904E+00,
        0.4901374201417999E+00,  0.2653816760888678E+00
      },

     {
	   -0.7917007412518723E-04,
       -0.8770279491271507E-04, -0.5817764173314433E-05,
       -0.1918407736150434E-03, -0.1546555642739420E-04,
        0.1575644463605992E-04, -0.2569512509880541E-05,
       -0.5502635280593235E-04, -0.1682303473450090E-04,
       -0.2506486731336301E-04, -0.7369167952864948E-05,
       -0.7189786890854420E-04,  0.9405385413525000E-05,
       -0.3781546712654382E-04, -0.4363323129985825E-06,
       -0.1192641655529459E-04, -0.2230142933103866E-04,
       -0.5400824407560233E-04, -0.9196915530647898E-04,
       -0.6302577854423968E-06, -0.2059003703672200E-03,
       -0.6738910167422552E-05, -0.8489087556227976E-04,
	   -0.1066590098440979E-05, -0.1163552834662887E-05,
       -0.1115071466551933E-05, -0.1163552834662887E-05,
        0.4217879025652964E-05,  0.1454441043328608E-06,
        0.1454441043328608E-06,  0.1003564319896740E-04,
       -0.2016824913415670E-04, -0.5843459298413238E-03,
        0.1357478307106701E-05,  0.2133180196881959E-05,
        0.2569512509880541E-05, -0.4785111032551121E-04,
       -0.4959159144069445E-03, -0.2225294796292771E-04,
        0.5866245541425386E-05,  0.3005844822879123E-05,
        0.6981317007977319E-05, -0.3936687090609432E-04,
        0.6981317007977319E-05,  0.6157133750091108E-05,
        0.5226291482360798E-04,  0.3781546712654382E-05,
		0.9066015836748324E-05,  0.1590188874039278E-04,
        0.3102807559101031E-05, -0.2521031141769587E-04,
        0.9705969895812912E-04,  0.1648366515772423E-04,
       -0.3224010979378415E-04, -0.5531724101459806E-04,
        0.1129615876985219E-04, -0.5866245541425386E-05,
       -0.1271666285550313E-03, -0.5332950492204896E-05,
       -0.6593466063089691E-05, -0.2811919350435309E-05,
        0.2739197298268879E-04,  0.9696273622190721E-05,
       -0.9696273622190721E-05, -0.1372022717539987E-04,
       -0.5284469124093944E-05, -0.9356904045414047E-05,
       -0.2516183004958492E-03, -0.9688516603292969E-03,
        0.3390302071998986E-03, -0.3238555389811700E-04,
		0.5914726909536340E-05, -0.9259941309192138E-05,
       -0.4295449214630489E-04,  0.2268928027592629E-04,
       -0.9841717726523582E-05, -0.1648366515772423E-04,
       -0.1238214141553755E-03,  0.4489374687074304E-04,
       -0.1609581421283659E-04, -0.1415655948839845E-04,
       -0.1097618174031990E-03, -0.8726646259971649E-06,
       -0.9405385413525000E-05, -0.6016537782569342E-04,
        0.1387051941654383E-03, -0.2627690151613686E-04,
        0.1872835250126138E-03,  0.1454441043328608E-06,
       -0.4319689898685967E-04,  0.1115071466551933E-05,
        0.2394979584681108E-04, -0.2908882086657217E-06,
       -0.1437957378170884E-03, -0.7320686584753995E-04,
	   -0.4023953553209149E-05, -0.7984881327874059E-04,
		0.6661339978445026E-04, -0.2060458144715528E-04
	  }
};

//char *listPlanetas[] =
//  {"Venus", "Marte", "J�piter", "Saturno", "Luna", "Sol"};


void  stardata ( int i, char* nom, char* mag,
				 double *ar, double *ap, double *de, double *dp) {

  strcpy (nom, estran.noe[i-1]);
  strcpy (mag, estran.mve[i-1]);
  *ar = estran.are[i-1];
  *de = estran.dee[i-1];
  *ap = estran.ape[i-1];
  *dp = estran.dpe[i-1];
}
