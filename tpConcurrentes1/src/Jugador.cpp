#include "Jugador.h"
#include <map>
#include <iostream>
#include <cstdlib>     	/* srand, rand*/
#include <ctime>       	/* time */

#define JUGADARANDOM 4
#define CANTIDADCARTAS 4

Jugador::Jugador() {
	cartas = list<Carta>();
	tipo = 0;
}

Jugador::Jugador(Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda) {
	cartas = list<Carta>();
	tipo = 0;
	this->comJugadorCentral = comJugadorCentral;
	this->comCentralJugador = comCentralJugador;
	this->comJugDerecha = comJugDerecha;
	this->comJugIzquierda = comJugIzquierda;
}

Jugador::~Jugador() {

}

void Jugador::tomarCarta(Carta carta) {
	cartas.push_back(carta);
}

Carta Jugador::dejarCartaRand() {
	srand ( time(NULL));
	int n_rand = rand() % CANTIDADCARTAS;
	int i = 0;

	cout << "tipo random:"<<n_rand<<endl;
	list<Carta>::iterator it;
	for(it = cartas.begin(); it != cartas.end(); it++) {
		if (i == n_rand) {
			Carta aux = *it;
			cartas.erase(it);
			return aux;
		}
		i++;
	}
	return Carta(0,0);
}

bool Jugador::gane() {
	/* debug:
	cout << "mis cartas son: ";
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++)
		cout << (*it) << " ";
	cout << endl;*/
	
	string numero = cartas.front().getNumero();
	list<Carta>::iterator it;
	for (it = cartas.begin() ; it != cartas.end() ; it++)
		if (numero != it->getNumero())
			return false;
	return true;
}



/* Deja una carta.
 * Cada JUGADARANDOM jugadas hace una jugada random.*/
Carta Jugador::dejarCarta() {
	tipo++;
	if (tipo % JUGADARANDOM == 0) {
		tipo = 1;
		return dejarCartaRand();
	}
	return dejarCartaRand();
}



void Jugador::pasarCarta(){
	Carta c = this->dejarCarta();
	cout << c.convertir() << endl;
	char* cc = (char*) "DEB";
	this->comJugDerecha->escribir(cc,3);
}
void Jugador::leerCarta(){
	char b[3];
	this->comJugDerecha->leer(b,3);
	cout << "Lei la carta:" << b << endl;
}
void Jugador::enviarMensajeCentral(){

}
void Jugador::leerMensajeCentral(){

}

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
