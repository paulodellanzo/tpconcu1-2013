#include "Jugador.h"
#include <map>
#include <iostream>
#include <cstdlib>     	/* srand, rand*/
#include <ctime>       	/* time */
#include <sys/types.h> 	/* getpid */
#include <unistd.h>		/* getpid */

#define JUGADARANDOM 4
#define CANTCARTAS 4

using namespace std;

Jugador::Jugador() {
	cartas = list<Carta>();
	jugada = 0;
}

Jugador::~Jugador() {

}

void Jugador::tomarCarta(Carta carta) {
	cartas.push_back(carta);
}


bool Jugador::gano() {
	/* debug:
	cout << "mis cartas son: ";
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++)
		cout << (*it) << " ";
	cout << endl;*/
	
	int numero = cartas.front().getNumero();
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++)
		if (numero != it->getNumero())
			return false;
	return true;
}


/* Deja una carta.
 * Cada JUGADARANDOM jugadas hace una jugada random.*/
/*Carta Jugador::dejarCarta() {
	jugada++;
	if (jugada % JUGADARANDOM == 0) {
		jugada = 1;
		return dejarCartaRandom();
	}
	return dejarCartaInteligente();
}*/

/*
Carta Jugador::dejarCartaInteligente() {
	map<int,int> frec;
	// Cuento las frecuencias de las cartas (por número)
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++) {
		int numero = it->getNumero();
		if ( frec[numero] )
			frec[numero] += 1;
		else
			frec[numero] = 1;
	}
	// Busco el mínimo
	int numeroMin = frec.begin()->first;
	int cantMin = frec.begin()->second;
	for (map<int,int>::iterator it = frec.begin(); it != frec.end(); it++) {
		if (it->second < cantMin) {
			numeroMin = it->first;
			cantMin = it->second;
		}
	}
	
	// Elimino la carta y devuelvo
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++) {
		if (it->getNumero() == numeroMin) {
			Carta aux = *it;
			cartas.erase(it);
			return aux;
		}
	}
	return Carta(0,0);
}
*/
	
Carta Jugador::dejarCartaRandom() {
	srand ( getpid() * 101 + time(NULL));
	int n_rand = rand() % CANTCARTAS;
	int i = 0;
	
	cout << "jugada random con valor "<<n_rand<<endl;
	
	for(list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++) {
		if (i == n_rand) {
			Carta aux = *it;
			cartas.erase(it);
			return aux;
		}
		i++;
	}
	return Carta(0,0);
}

