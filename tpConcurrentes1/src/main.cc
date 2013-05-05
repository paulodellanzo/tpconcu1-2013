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
#include "JugadorAdministrador.h"
#include "Mazo.h"
#include "Comunicador.h"
#include "Mensajes.h"


#define TAMBUFFER 100

using namespace std;

void pruebaRonda(int cantJugadores){

	char* jugadores[] = {(char*)"2",(char*)"3",(char*)"4",(char*)"5",(char*)"6",(char*)"7",(char*) "8"};

	Pipe* canal = new Pipe();

	Logger::setDebug();

	/*
	 * Creacion de los comunicadores entre procesos


	list<Comunicador*> comunicadores;
	comunicadores.push_back(new Comunicador());
	comunicadores.push_back(new Comunicador());
	comunicadores.push_back(new Comunicador());
	comunicadores.push_back(new Comunicador());
*/
	Comunicador* com1 = new Comunicador();
	Comunicador* com2 = new Comunicador();
	Comunicador* com3 = new Comunicador();
	Comunicador* com4 = new Comunicador();

	Comunicador commm;

	JugadorAdministrador* jAdmin = new JugadorAdministrador(cantJugadores, com1, com2, com3, com4);

	Mazo m(10);
			Carta c1 = m.getCarta();
			Carta c2 = m.getCarta();
			Carta c3 = m.getCarta();
			Carta c4 = m.getCarta();

			jAdmin->tomarCarta(c1);
			jAdmin->tomarCarta(c2);
			jAdmin->tomarCarta(c3);
			jAdmin->tomarCarta(c4);

	//JugadorAdministrador* jAdmin = new JugadorAdministrador(cantJugadores);

	int pid = fork();
	if(pid == 0) {

		cout << "soy el hijo voy a pasar una carta" << endl;
		jAdmin->pasarCarta();

		//execlp((char*) "./procJugadorCoordinador", (char*) "procJugadorCoordinador",(char*) sal.c_str(), jugadores[cantJugadores - 2], (char*) NULL);
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

		sleep(3);
		jAdmin->leerCarta();

		/*Mazo m(10);
		Carta c1 = m.getCarta();
		Carta c2 = m.getCarta();
		Carta c3 = m.getCarta();
		Carta c4 = m.getCarta();

		Jugador* j = new Jugador();
		j->tomarCarta(c1);
		j->tomarCarta(c2);
		j->tomarCarta(c3);
		j->tomarCarta(c4);

		Carta c = j->dejarCarta();

		//cout << c.convertir() << endl;
		delete j;

		 */



		//delete jAdmin;

		Comunicador* com = new Comunicador();

		//cout << Mensajes::REPARTIR << endl;


		canal->cerrar();
		delete canal;
		delete com;

		Logger::log("SABE");

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

