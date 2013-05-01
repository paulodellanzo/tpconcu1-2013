/*
 * main.cc
 *
 *  Created on: 01/05/2013
 *      Author: paulo
 */


#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>

#include "Pipe.h"

#define BUFFSIZE 3

using namespace std;

int main () {

	Pipe canal;

	int pid = fork ();

	if ( pid == 0 ) {

		// lector
		char buffer [ BUFFSIZE ];

		cout << "Lector: esperando para leer..." << endl;
		int bytes = canal.leer ( buffer,BUFFSIZE );
		buffer [ bytes ] = '\0';

		cout << "Lector: lei el dato [" << buffer << "] (" << bytes << " bytes) del pipe" << endl;
		cout << "Lector: fin del proceso" << endl;

		bytes = canal.leer ( buffer,BUFFSIZE );
		buffer [ bytes ] = '\0';

		cout << "Lector: lei el dato [" << buffer << "] (" << bytes << " bytes) del pipe" << endl;
		cout << "Lector: fin del proceso" << endl;

		char buffer1 [ 12 ];
		canal.leer(buffer1,12);
		buffer1 [ 12 ] = '\0';

		cout << "Lector: lei el dato [" << buffer1 << endl;

		//canal.cerrar ();
		exit ( 0 );

	} else {

		// escritor
		char *dato = (char *) "E12";
		//sleep ( 5 );
		canal.escribir ( dato,strlen(dato) );

		cout << "Escritor: escribi el dato [" << dato << "] en el pipe" << endl;
		cout << "Escritor: fin del proceso" << endl;


		dato = (char *) "C01";
		canal.escribir ( dato,strlen(dato) );

		cout << "Escritor: escribi el dato [" << dato << "] en el pipe" << endl;
		cout << "Escritor: fin del proceso" << endl;
		canal.escribir ( dato,strlen(dato) );
		canal.escribir ( dato,strlen(dato) );
		canal.escribir ( dato,strlen(dato) );
		canal.escribir ( dato,strlen(dato) );


		// espero a que termine el hijo
		wait ( NULL );

		//canal.cerrar ();
		exit ( 0 );
	}
}

