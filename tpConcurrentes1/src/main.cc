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

#define TAMBUFFER 4

using namespace std;

int main (){

	int cantJugadores = 2;
	//char* jugadores[] = {(char*)"2",(char*)"3",(char*)"4",(char*)"5",(char*)"6",(char*)"7",(char*) "8"};

	Pipe* canal = new Pipe();

	Pipe canal2;

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

	Mazo* m = new Mazo(10);
	m->barajar();
	Carta c1 = m->getCarta();
	Carta c2 = m->getCarta();
	Carta c3 = m->getCarta();
	Carta c4 = m->getCarta();

	jAdmin->tomarCarta(c1);
	jAdmin->tomarCarta(c2);
	jAdmin->tomarCarta(c3);
	jAdmin->tomarCarta(c4);

	//JugadorAdministrador* jAdmin = new JugadorAdministrador(cantJugadores);

	int pid = fork();
	if(pid == 0) {

		cout << "soy el padre voy a pasar una carta" << endl;

		jAdmin->pasarCarta();
		jAdmin->pasarCarta();
		jAdmin->pasarCarta();
		jAdmin->pasarCarta();
		//delete jAdmin;
		//char* lo = (char*) "hola";

		//canal->escribir(lo,strlen(lo));
		//canal2.escribir(lo,strlen(lo));
		//cout << ppp << endl;

		//jAdmin->leerCarta();

		//lei = canal2.leer(ppp,TAMBUFFER);


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

		//sleep(1);

		jAdmin->leerCarta();
		jAdmin->leerCarta();
		jAdmin->leerCarta();
		jAdmin->leerCarta();

		//int size = 100;
		//char ppp [ TAMBUFFER ];

		//int lei = canal2.leer(ppp,TAMBUFFER);
		//ppp [ lei ] = '\0';



		//canal2.cerrar();



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

		//Comunicador* com = new Comunicador();

		//cout << Mensajes::REPARTIR << endl;


		canal->cerrar();

		//delete canal;
		//delete com;

		//Logger::log("SABE");

		for (int i = 0; i < cantJugadores; i++)
			wait(NULL);

		//delete jAdmin;
		canal2.cerrar();
		exit ( 0 );
	}

}

int main2 () {

	//pruebaJCRepartir();
	//pruebaLogger();
	//pruebaRondaCoordinador(4);
	//pruebaRonda(2);
cout << "main2" << endl;
	return 0;

}

