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
	delete this->comCentralJugador;
	delete this->comJugadorCentral;
	delete this->comJugDerecha;
	delete this->comJugIzquierda;
	if (this->comJugAdmin != NULL){
		delete this->comJugAdmin;
	}
}

void Jugador::agregarJugAdmin(Comunicador* comJugAdmin){
	this->comJugAdmin = comJugAdmin;
}

void Jugador::agregarcomJugadorCentral(Comunicador* comJugadorCentral){
	this->comJugadorCentral = comJugadorCentral;
}

void Jugador::agregarcomCentralJugador(Comunicador* comCentralJugador){
	this->comCentralJugador = comCentralJugador;

}
void Jugador::agregarcomJugDerecha(Comunicador* comJugDerecha){
	this->comJugDerecha = comJugDerecha;

}

void Jugador::agregarcomJugIzquierda(Comunicador* comJugIzquierda){
	this->comJugIzquierda = comJugIzquierda;

}

void Jugador::tomarCarta(Carta carta) {
	cartas.push_back(carta);
}

/*
 * Se crea una nueva carta con el mensaje recibido del jugador de la izquierda
 * Los 2 primero caracteres deben corresponder con el palo y el ultimo es el numero
 */
void Jugador::crearCarta(string cartaEnMensaje){
	Carta cartaNueva(cartaEnMensaje.substr(0,2),cartaEnMensaje.substr(2,1));
	//cout << "Nueva:" << cartaNueva.convertir() << endl;
	this->tomarCarta(cartaNueva);
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
	return Carta("00","0");
}

/*
 * Determina si el jugador gano si y solo si tiene todas sus cartas con el mismo numero
 */
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
		//return dejarCartaRand();

	}
	Carta carta = this->cartas.back();
	this->cartas.pop_back();
	return carta;
	//return dejarCartaRand();
}



void Jugador::pasarCarta(){
	Carta c = this->dejarCarta();
	string mensaje = c.convertir();
	//cout << c.convertir() << endl;
	//char* cc = (char*) "DEB";
	int bytesleidos = this->comJugDerecha->escribir((char*)mensaje.c_str(),SIZE);
	while (bytesleidos < SIZE){
			//sleep(1);
			bytesleidos = this->comJugDerecha->escribir((char*)mensaje.c_str(),SIZE);
	}
}

int Jugador::leerCarta(){
	char buffer[SIZE];
	int bytesleidos = this->comJugDerecha->leer(buffer,SIZE);
	//cout << "bien" <<bytesleidos;
	while (bytesleidos < SIZE){
		//sleep(1);
		bytesleidos = this->comJugDerecha->leer(buffer,SIZE);
	}
	buffer [bytesleidos] = '\0';
	cout << "Lei la carta:" << buffer << endl;
	this->crearCarta(buffer);
	return bytesleidos;
}

void Jugador::enviarMensajeCentral(string mensaje){
	int bytesleidos = this->comJugadorCentral->escribir((char*)mensaje.c_str(),SIZE);
	while (bytesleidos < SIZE){
		//sleep(1);
		bytesleidos = this->comJugadorCentral->escribir((char*)mensaje.c_str(),SIZE);
	}
}

string Jugador::leerMensajeCentral(){
	char buffer[SIZE];
	int bytesleidos = this->comCentralJugador->leer(buffer,SIZE);
	//cout << "bien" <<bytesleidos;
	while (bytesleidos < SIZE){
		//sleep(1);
		bytesleidos = this->comCentralJugador->leer(buffer,SIZE);
	}
	buffer [bytesleidos] = '\0';
	return buffer;

}

int Jugador::correr(){

	bool corriendo = true;
	string msg = this->leerMensajeCentral();
	if (msg == REPARTIR){
		cout << "salimosss";
	}

	return 0;
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
