#include <stdio.h>

#include <stdlib.h>

int main(void){

char *data;
long m,n;
   
   printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
   printf("<TITLE>Resultados de multiplicacion</TITLE>\n");
   printf("<H3>Resultados de multiplicacion.</H3>\n");
   data = getenv("QUERY_STRING");
   if(data == NULL)
      printf("<P>Error al pasar los datos al programa.");
   else if(sscanf(data, "m=%ld&n=%ld", &m,&n) != 2)
   	printf("<P>Error al pasar los datos al programa.");
   else
   	printf("<P>El pruducto de %ld y %ld is %ld.", m,n, m*n);
  return 0;	
}
