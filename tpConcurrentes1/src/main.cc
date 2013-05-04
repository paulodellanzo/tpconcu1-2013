/*
 * main.cc
 *
 *  Created on: 01/05/2013
 *      Author: paulo
 */


#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/wait.h>

#include "SIGINT_Handler.h"
#include "SignalHandler.h"
#include "Pipe.h"
#include "Logger.h"

#define TAMBUFFER 100

using namespace std;

void pruebaRonda(int cantJugadores){

	char* jugadores[] = {(char*)"2",(char*)"3",(char*)"4",(char*)"5",(char*)"6",(char*)"7",(char*) "8"};

	Pipe canal = Pipe();
	Pipe canal2;
	Logger log;

	log.setDebug();
	log.log("123");

	stringstream salida;
	salida << canal.getFdEscritura();
	cout << salida.str() << endl;

	//canal.setearModo(LECTURA)
	int pid = fork();
	if(pid == 0) {

		canal2.escribir("asd",4);


		//dup2(canal.getFdLectura(),0);
		execlp((char*) "./procJugadorCoordinador", (char*) "procJugadorCoordinador",(char*) (salida.str()).c_str(), jugadores[cantJugadores - 2], (char*) NULL);
	}

/*
	for (int i = 0; i <= cantJugadores - 2; i++) {
		pid = fork();
		if(pid == 0){
			//dup2(canal.getFdEscritura(),1);
			execlp((char*) "./procJugador", (char*) "procJugador", jugadores[i], jugadores[cantJugadores - 2], (char*) NULL);
		}
	}
*/
	else{
		//Estadistico est(cantJugadores);
		//est.correr();
		sleep(2);
		string s;
		//canal.setearModo(LECTURA)

		canal.leer(s,50);
		canal.cerrar();
		log.log(s);

		string hs;
		canal2.leer(hs,4);
		cout << hs << endl;
		//dup2(canal.getFdLectura(),0);
		string hola;
		//cin >> hola;
		canal2.cerrar();
		log.log(hs);

		for (int i = 0; i < cantJugadores; i++)
			wait(NULL);
	}

}

int main () {

	//pruebaJCRepartir();
	//pruebaLogger();
	//pruebaRondaCoordinador(4);
	pruebaRonda(2);

	return 0;

}

