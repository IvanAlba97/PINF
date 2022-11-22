#include <stdio.h>

#include <stdlib.h>

int main(void){

char *data;
long m,n;
   
   printf("%s%c%c\n","Content-Type:application/json;charset=UTF-8",13,10);
   data = getenv("QUERY_STRING");
   if(data == NULL)
       printf("{\"ERROR\":\"Error al pasar los datos al programa\"}, ");
   else if(sscanf(data, "m=%ld&n=%ld", &m,&n) != 2)
   	printf("{\"ERROR\":\"Error al pasar los datos al programa\"}, ");
   else
       printf("{\"resProducto\":%ld, \"P1\": %ld, \"P2\": %ld,",m*n, m, n);
  return 0;	
}
