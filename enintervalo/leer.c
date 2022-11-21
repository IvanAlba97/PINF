#include <stdio.h> 
#include <stdlib.h>

int main(void){

  FILE *fic;
  
static struct TPos {

  double latitud, longitud, elevacion, zona_hor;

} posicion;


  if ( ( fic = fopen ("posicion.dat", "rb") ) == NULL ) { // r+b = write binary

	printf ("Error al abrir archivo posicion.dat\n");

	return 1;

  }

  fseek (fic, 0, SEEK_SET); // posicionamos el registro a escribir

  fread (&posicion, sizeof(posicion), 1, fic); // escribe 'lor' bytes con lo que hay desde &jdP

  fclose (fic);

  printf("\n%lf\n%lf\n%lf\n%lf\n",posicion.latitud, posicion.longitud, posicion.zona_hor, posicion.elevacion);

  return 0;
}

