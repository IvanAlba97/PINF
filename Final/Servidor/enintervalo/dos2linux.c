#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

  	FILE *fic1;
  	FILE *fic2;

	int c;


  	if ( ( fic1 = fopen (argv[1], "r") ) == NULL ) {

		fprintf (stderr,"Error al abrir archivo %s\n", argv[1]);
		exit (1);
	}

  	if ( ( fic2 = fopen (argv[2], "w") ) == NULL ) {

		fprintf (stderr,"Error al abrir archivo %s\n", argv[2]);
		exit (1);
	}
	while (!feof(fic1)){
		if ((c=getc(fic1)) != '\r')
			putc(c,fic2);
	}
	fclose(fic1);
	fclose(fic2);
	return 0;
  }
