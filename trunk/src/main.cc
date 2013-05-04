/*
 * main.cc
 *
 *  Created on: 01/05/2013
 *      Author: paulo
 */

#ifdef MAIN
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/wait.h>

#include "SIGINT_Handler.h"
#include "SignalHandler.h"

#define TAMBUFFER 100

using namespace std;

void pruebaRonda(int cantJug){

	char* jugadores[] = {(char*)"2",(char*)"3",(char*)"4",(char*)"5",(char*)"6",(char*)"7",(char*) "8"};

	int pid = fork();
	if(pid == 0) {
		execlp((char*) "./procJugadorCoordinador", (char*) "procJugadorCoordinador", jugadores[cantJugadores - 2], (char*) NULL);
	}


	for (int i = 0; i <= cantJugadores - 2; i++) {
		pid = fork();
		if(pid == 0){
			execlp((char*) "./procJugador", (char*) "procJugador", jugadores[i], jugadores[cantJugadores - 2], (char*) NULL);
		}
	}

	Estadistico est(cantJugadores);
	est.correr();

	for (int i = 0; i < cantJugadores; i++)
		wait(NULL);

}

int main () {

	//pruebaJCRepartir();
	//pruebaLogger();
	//pruebaRondaCoordinador(4);
	pruebaRonda(2);

	return 0;

}
#endif
