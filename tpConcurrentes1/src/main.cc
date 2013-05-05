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
#include "Jugador.h"
#include "Mazo.h"


#define TAMBUFFER 100

using namespace std;

void pruebaRonda(int cantJugadores){

	char* jugadores[] = {(char*)"2",(char*)"3",(char*)"4",(char*)"5",(char*)"6",(char*)"7",(char*) "8"};

	Pipe* canal = new Pipe();
	Pipe canal2 = Pipe();
	Logger log;

	log.setDebug();
	log.log("123");

	int pid = fork();
	if(pid == 0) {

		canal2.escribir("asd21",5);
		//canal.setearModo(ESCRITURA);
		//dup2(canal->getFdEscritura(),1);
		//close(canal->getFdEscritura());
		//close(canal->getFdLectura());
		//dup2(canal.getFdLectura(),0);
		//cout << "HOLA123" << endl;

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
		//Estadistico est(cantJugadores);
		//est.correr();
		sleep(2);
		string s;
		//canal.setearModo(LECTURA);
		//dup2(canal->getFdLectura(),0);

		//canal.leer(s,50);
		//close(desc[0]);
		//int resultado = 1;
		char bbbbbbb[5];
		//resultado = read ( canal->getFdLectura(),bbbbbbb,5 );

		int y = canal2.leer(bbbbbbb,5);
		cout << " A: " << bbbbbbb << " -- "<< y << endl;

		log.log(s);

		string hs;
		//canal2.leer(hs,4);
/*
		while (cin >> s){
			cout << s << endl;
		}
*/

		Mazo m(10);
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

		cout << c.convertir() << endl;

		delete j;



		canal2.cerrar();
		canal->cerrar();
		delete canal;
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

