#ifdef OBSERVADOR

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "LockFile.h"
#define TABLA "tabla.txt"

using namespace std;

int main () {

	LockFile* tablaPuntaje = new LockFile((char *)TABLA);
	//LockFile lock ( (char *) "main1.cc" );
	tablaPuntaje->tomarLock();

	cout << "CAPOOOO" << endl;

	sleep(2);

	FILE* archivo = fopen(TABLA, "r");
//	int x;
	char buffer[100];
	if ( ! archivo){
		cout << "No hay tabla de puntaje" << endl;
		return 0;
	}
	while (!feof(archivo)) {
		fgets(buffer,100,archivo);
		//fscanf(archivo, "%d", &x);
	}
	cout << buffer;
	fclose(archivo);

	int fileDes = open ( TABLA , O_RDONLY );
	int buffSize = 100;
	read ( fileDes,(void *)buffer,buffSize );
	cout << buffer;
	close ( fileDes );

	tablaPuntaje->liberarLock();

	return 0;

}

#endif
