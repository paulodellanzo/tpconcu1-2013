#ifdef OBSERVADOR

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "LockFile.h"
#define TABLA "tabla.txt"

using namespace std;

int main () {

	LockFile* tablaPuntaje = new LockFile((char *)TABLA);
	tablaPuntaje->tomarLock();

	FILE *archivo;

	char caracteres[200];

	archivo = fopen(TABLA,"r");

	if (archivo == NULL)
			exit(1);

	while (feof(archivo) == 0)
	{
			fgets(caracteres,100,archivo);
			printf("%s",caracteres);
	}

	fclose(archivo);

	/*char buffer[100];
	int fileDes = open ( TABLA , O_RDONLY );
	int buffSize = 100;
	read ( fileDes,(void *)buffer,buffSize );
	cout << buffer;
	close ( fileDes );
	*/

	tablaPuntaje->liberarLock();

	return 0;

}

#endif
