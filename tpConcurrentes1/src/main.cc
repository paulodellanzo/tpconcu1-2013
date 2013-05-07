#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/wait.h>

#include "SIGINT_Handler.h"
#include "SignalHandler.h"
#include "Logger.h"
#include "JugadorAdministrador.h"
#include "Mensajes.h"
//#include "Comunicador.h"
#include "Central.h"

#define TAMBUFFER 4

using namespace std;

int main() {

	Logger::setDebug();

	Logger::log("Comienza el juego");

	int cantJugadores = 2;
	//char* jugadores[] = {(char*)"2",(char*)"3",(char*)"4",(char*)"5",(char*)"6",(char*)"7",(char*) "8"};

	/*
	 * Creacion de los comunicadores entre procesos
	 * Las posiciones son relativas al numero de jugador
	 */

	list<Comunicador*> comunicadoresHaciaJugadores;
	for (int i = 0; i < cantJugadores; i++) {
		comunicadoresHaciaJugadores.push_back(new Comunicador());
	}

	list<Comunicador*> comunicadoresDesdeJugadores;
	for (int i = 0; i < cantJugadores; i++) {
		comunicadoresDesdeJugadores.push_back(new Comunicador());
	}

	Comunicador* com3 = new Comunicador();
	Comunicador* com4 = new Comunicador();

	list<Comunicador*> comJugAdminOtrosJug;
	for (int i = 1; i < cantJugadores; i++) {
		comJugAdminOtrosJug.push_back(new Comunicador());
	}

	Central* central = new Central(cantJugadores, comunicadoresHaciaJugadores,
			comunicadoresDesdeJugadores);

	JugadorAdministrador* jAdmin = new JugadorAdministrador(cantJugadores,
			comunicadoresDesdeJugadores.front(),
			comunicadoresHaciaJugadores.front(), com3, com4);
	jAdmin->setID(1);

	list<Comunicador*>::iterator it;
	for (it = comJugAdminOtrosJug.begin(); it != comJugAdminOtrosJug.end();
			it++) {
		jAdmin->agregarComunicacionJugador(*it);
	}

	list<Jugador*> listaJugadores;
	list<Comunicador*>::iterator itHaciaJugadores =
			comunicadoresHaciaJugadores.begin();
	list<Comunicador*>::iterator itDesdeJugadores =
			comunicadoresDesdeJugadores.begin();
	list<Comunicador*>::iterator itAdmin = comJugAdminOtrosJug.begin();

	itDesdeJugadores++;
	itHaciaJugadores++;
	//itAdmin++;

	//El primer jugador es el administrador por eso empiezo en 1
	for (int i = 2; i < cantJugadores + 1; i++) {

		Jugador* jug = new Jugador();
		jug->agregarcomJugadorCentral(*itDesdeJugadores);
		jug->agregarcomCentralJugador(*itHaciaJugadores);
		jug->agregarJugAdmin(*itAdmin);
		jug->setID(i);

		listaJugadores.push_back(jug);

		itDesdeJugadores++;
		itHaciaJugadores++;
		itAdmin++;
	}

	//Prueba de 2 jugadores
	//jAdmin->agregarcomJugDerecha(new Comunicador);
	listaJugadores.front()->agregarcomJugDerecha(jAdmin->comJugIzquierda);
	listaJugadores.front()->agregarcomJugIzquierda(jAdmin->comJugDerecha);
	/*
	 Mazo* m = new Mazo(cantJugadores);
	 m->barajar();
	 Carta c1 = m->getCarta();
	 Carta c2 = m->getCarta();
	 Carta c3 = m->getCarta();
	 Carta c4 = m->getCarta();

	 jAdmin->tomarCarta(c1);
	 jAdmin->tomarCarta(c2);
	 jAdmin->tomarCarta(c3);
	 jAdmin->tomarCarta(c4);

	 Carta c11 = m->getCarta();
	 Carta c22 = m->getCarta();
	 Carta c33 = m->getCarta();
	 Carta c44 = m->getCarta();

	 listaJugadores.front()->tomarCarta(c11);
	 listaJugadores.front()->tomarCarta(c22);
	 listaJugadores.front()->tomarCarta(c33);
	 listaJugadores.front()->tomarCarta(c44);
	 */

	//JugadorAdministrador* jAdmin = new JugadorAdministrador(cantJugadores);
	int pid = fork();
	if (pid == 0) {

		pid = fork();

		if (pid == 0) {

			/*jAdmin->pasarCarta();
			 jAdmin->pasarCarta();
			 jAdmin->pasarCarta();
			 jAdmin->pasarCarta();
			 */

			jAdmin->correr();
			//delete jAdmin;
		} else {
			//Itero sobre el resto de los jugadores y los pongo a jugar
			list<Jugador*>::iterator it;
			for (it = listaJugadores.begin(); it != listaJugadores.end();
					it++) {
				pid = fork();
				if (pid == 0) {
					(*it)->correr();
				} else {
					exit(0);
				}
			}

		}
		//execlp((char*) "./procJugadorCoordinador", (char*) "procJugadorCoordinador",(char*) sal.c_str(), jugadores[cantJugadores - 2], (char*) NULL);
	}

	/*
	 for (int i = 0; i <= cantJugadores - 2; i++) {
	 pid = fork();
	 if(pid == 0){
	 execlp((char*) "./procJugador", (char*) "procJugador", jugadores[i], jugadores[cantJugadores - 2], (char*) NULL);
	 }
	 }
	 */
	else {
		//sleep(2);

		/*jAdmin->leerCarta();
		 jAdmin->leerCarta();
		 jAdmin->leerCarta();
		 jAdmin->leerCarta();*/

		central->correr();

		//Logger::log("SABE");

		for (int i = 0; i < cantJugadores; i++)
			wait(NULL);

		list<Jugador*>::iterator it;
		for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
			delete *it;
		}

		list<Comunicador*>::iterator itBorrador;

		for (itBorrador = comunicadoresHaciaJugadores.begin();
				itBorrador != comunicadoresHaciaJugadores.end(); itBorrador++) {
			delete *itBorrador;
		}
		for (itBorrador = comunicadoresDesdeJugadores.begin();
				itBorrador != comunicadoresDesdeJugadores.end(); itBorrador++) {
			delete *itBorrador;
		}
		for (itBorrador = comJugAdminOtrosJug.begin();
				itBorrador != comJugAdminOtrosJug.end(); itBorrador++) {
			delete *itBorrador;
		}

		delete com3;
		delete com4;
		delete jAdmin;

		exit(0);
	}

}

