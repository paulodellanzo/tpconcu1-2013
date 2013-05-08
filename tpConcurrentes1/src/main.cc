#ifdef MAIN

#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdlib>

#include "SIGINT_Handler.h"
#include "SignalHandler.h"
#include "Logger.h"
#include "JugadorAdministrador.h"
#include "Mensajes.h"
#include "Central.h"

#define MAXJUGADORES 10

using namespace std;

int main(int argc, char **argv) {

	cout << "Uso del Programa: ./tpconcu1-2013 n d" << endl;
	cout << "Donde n es el numero de jugadores y d es modo debug" << endl;
	cout << "Deben haber mas de 1 jugador y "<< MAXJUGADORES << " como maximo" << endl;

	//int cant = 4;

	if (argc <= 1 || argc > 3){
		cout << "Incorrecto uso del programa, adios" << endl;
		return 0;
	}
	int cant = atoi(argv[1]);
	if (cant < 2 || cant > MAXJUGADORES){
		cout << "Cantidad incorrecta o mal formato de jugadores" << endl;
		return 0;
	}
	if (argc == 3){
		if (strcmp (argv[2],"d") == 0){
			Logger::setDebug();
		}
		else{
			cout << "Se debe pasar d ultimo parametro para debuggear" << endl;
			return 0;
		}
	}

	cout << "INICIA Partida de : " << cant << " jugadores " << endl;

	Logger::emptyLog();

	//Logger::setDebug();

	Logger::log("Main - Comienza el juego");

	int cantJugadores = cant;

	/*
	 * Creacion de los comunicadores entre procesos
	 * Las posiciones son relativas al numero de jugador
	 */

	Logger::log("Main - Creo comunicadores central-jugadores");
	list<Comunicador*> comunicadoresHaciaJugadores;
	for (int i = 0; i < cantJugadores; i++) {
		string mensaje = "Main - Creo comunicador central-jugador ";
		mensaje.append(Logger::itos(i+1));
		Logger::log(mensaje);
		comunicadoresHaciaJugadores.push_back(new Comunicador());
	}

	list<Comunicador*> comunicadoresDesdeJugadores;
	for (int i = 0; i < cantJugadores; i++) {
		string mensaje = "Main - Creo comunicador jugador ";
		mensaje.append(Logger::itos(i+1));
		mensaje.append("-central");
		Logger::log(mensaje);
		comunicadoresDesdeJugadores.push_back(new Comunicador());
	}

	list<Comunicador*> comJugAdminOtrosJug;
	for (int i = 1; i < cantJugadores; i++) {
		string mensaje = "Main - Creo comunicador jugador admin-jugador ";
				mensaje.append(Logger::itos(i));
				Logger::log(mensaje);
		comJugAdminOtrosJug.push_back(new Comunicador());
	}

	Logger::log("Main - Creo central");
	Central* central = new Central(cantJugadores, comunicadoresHaciaJugadores,
			comunicadoresDesdeJugadores);

	Logger::log("Main - Creo jugador admin");
	JugadorAdministrador* jAdmin = new JugadorAdministrador(cantJugadores,
			comunicadoresDesdeJugadores.front(),
			comunicadoresHaciaJugadores.front(), NULL, NULL);
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

	Jugador* jugadorAnterior = jAdmin;
	//El primer jugador es el administrador por eso empiezo en 1
	for (int i = 2; i < cantJugadores + 1; i++) {

		string mensaje = "Main - Creo comunicador jugador ";
		mensaje.append(Logger::itos(i));
		Logger::log(mensaje);

		Jugador* jug = new Jugador();
		jug->agregarcomJugadorCentral(*itDesdeJugadores);
		jug->agregarcomCentralJugador(*itHaciaJugadores);
		jug->agregarJugAdmin(*itAdmin);
		jug->setID(i);

		listaJugadores.push_back(jug);

		Comunicador* comAux = new Comunicador();

		jug->agregarcomJugIzquierda(comAux);
		jugadorAnterior->agregarcomJugDerecha(comAux);

		jugadorAnterior = jug;

		itDesdeJugadores++;
		itHaciaJugadores++;
		itAdmin++;
	}

	//El ultimo con el primero y el primero con el último
	Comunicador* comAux = new Comunicador();
	listaJugadores.back()->agregarcomJugDerecha(comAux);
	jAdmin->agregarcomJugIzquierda(comAux);

	int pid = fork();
	if (pid == 0) {

		Logger::log("Main - Comienza proceso creador de jugadores");

		pid = fork();

		if (pid == 0) {

			Logger::log("Main - Comienza proceso Jugador Admin");

			jAdmin->correr();

		} else {
			//Itero sobre el resto de los jugadores y los pongo a jugar
			list<Jugador*>::iterator it;
			for (it = listaJugadores.begin(); it != listaJugadores.end();
					it++) {
				pid = fork();
				if (pid == 0) {
					string mensaje = "Main - Comienza proceso Jugador ";
					mensaje.append(Logger::itos((*it)->idJugador));
					Logger::log(mensaje);

					(*it)->correr();
				}
			}
			//Crea los hijos y termina
			exit(0);

		}

	}

	else {

		Logger::log("Main - Comienza proceso central");

		central->correr();

		Logger::log("Main - Termino el juego, comienzo a borrar todo");

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

		delete jAdmin;

		exit(0);
	}

}

#endif
