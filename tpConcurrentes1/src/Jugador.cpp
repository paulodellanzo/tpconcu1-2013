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
	this->primerRonda = true;
	this->idJugador = 0;
}

Jugador::Jugador(Comunicador* comJugadorCentral, Comunicador* comCentralJugador,
		Comunicador* comJugDerecha, Comunicador* comJugIzquierda) {
	cartas = list<Carta>();
	tipo = 0;
	this->primerRonda = true;
	this->idJugador = 0;
	this->comJugadorCentral = comJugadorCentral;
	this->comCentralJugador = comCentralJugador;
	this->comJugDerecha = comJugDerecha;
	this->comJugIzquierda = comJugIzquierda;
}

Jugador::~Jugador() {
	if (this->comJugDerecha != NULL) {
		delete this->comJugDerecha;
	}
	if (this->comJugIzquierda != NULL) {
		delete this->comJugIzquierda;
	}
	delete this->comCentralJugador;
	delete this->comJugadorCentral;
	if (this->comJugAdmin != NULL) {
		delete this->comJugAdmin;
	}
}

string Jugador::getDescripcionJugador() {
	stringstream salida;
	salida << "Jugador " << this->idJugador;
	return salida.str();
}

void Jugador::agregarJugAdmin(Comunicador* comJugAdmin) {
	this->comJugAdmin = comJugAdmin;
}

void Jugador::agregarcomJugadorCentral(Comunicador* comJugadorCentral) {
	this->comJugadorCentral = comJugadorCentral;
}

void Jugador::agregarcomCentralJugador(Comunicador* comCentralJugador) {
	this->comCentralJugador = comCentralJugador;

}
void Jugador::agregarcomJugDerecha(Comunicador* comJugDerecha) {
	this->comJugDerecha = comJugDerecha;

}

void Jugador::agregarcomJugIzquierda(Comunicador* comJugIzquierda) {
	this->comJugIzquierda = comJugIzquierda;

}

void Jugador::setID(int ID) {
	this->idJugador = ID;
}

int Jugador::getID() {
	return this->idJugador;
}

void Jugador::tomarCarta(Carta carta) {
	cartas.push_back(carta);
}

/*
 * Se crea una nueva carta con el mensaje recibido del jugador de la izquierda
 * Los 2 primero caracteres deben corresponder con el palo y el ultimo es el numero
 */
void Jugador::crearCarta(string cartaEnMensaje) {
	Carta cartaNueva(cartaEnMensaje.substr(0, 2), cartaEnMensaje.substr(2, 1));
	this->tomarCarta(cartaNueva);
}

//Carta Jugador::dejarCartaRand() {
//	srand(time(NULL));
//	int n_rand = rand() % CANTIDADCARTAS;
//	int i = 0;
//
//	list<Carta>::iterator it;
//	for (it = cartas.begin(); it != cartas.end(); it++) {
//		if (i == n_rand) {
//			Carta aux = *it;
//			cartas.erase(it);
//			return aux;
//		}
//		i++;
//	}
//	return Carta("00", "0");
//}

/*
 * Determina si el jugador gano si y solo si tiene todas sus cartas tienen el mismo numero
 */
bool Jugador::gane() {
	string numero = cartas.front().getNumero();
	list<Carta>::iterator it;
	for (it = cartas.begin(); it != cartas.end(); it++){
		if (numero != it->getNumero()){
			return false;
		}
	}
	return true;
}

//Deja una carta
Carta Jugador::dejarCarta() {
	srand(11 * getpid() * time(NULL));

	map<string,int> cantNumero;
	list<Carta>::iterator it;
	for (it = cartas.begin(); it != cartas.end(); it++){
		string numeroCarta = it->getNumero();
		if (cantNumero[numeroCarta]) {
			cantNumero[numeroCarta] += 1;
		} else {
			cantNumero[numeroCarta] = 1;
		}
	}

	list<string> numCartaMinimos;

	int minimo = std::numeric_limits<int>::max();
	for (map<string,int>::iterator it = cantNumero.begin(); it != cantNumero.end(); it++) {
		if (it->second < minimo) {
			minimo = it->second;
			numCartaMinimos.clear();
			numCartaMinimos.push_back(it->first);
		} else if (it->second == minimo) {
			numCartaMinimos.push_back(it->first);
		}
	}

	list<Carta> cartasMinimas;
	for (it = cartas.begin(); it != cartas.end(); it++){
		for(list<string>::iterator itNumero = numCartaMinimos.begin(); itNumero != numCartaMinimos.end(); itNumero++) {
			if((it->getNumero()) == (*itNumero)) {
				cartasMinimas.push_back((*it));
			}
		}
	}

	int numeroCarta = rand() % (cartasMinimas.size());

	int contador = 0;
	Carta carta("","");
	for (it = cartasMinimas.begin(); it != cartasMinimas.end(); it++){
		if(contador==numeroCarta) {
			carta = (*it);
		}
		contador++;
	}

	for (it = cartas.begin(); it != cartas.end(); it++){
		if(it->convertir() == carta.convertir()) {
			cartas.erase(it);
			break;
		}
	}

	return carta;
}

void Jugador::pasarCarta() {

	string logMessage = getDescripcionJugador();
	logMessage.append(" - Cantidad de cartas: ");
	logMessage.append(Logger::itos((int)this->cartas.size()));
	logMessage.append(" - [ ");
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++){
		logMessage.append(it->convertir());
		logMessage.append(" ");
	}
	logMessage.append("]");
	Logger::log(logMessage);

	Carta c = this->dejarCarta();
	string mensaje = c.convertir();
	int bytesleidos = this->comJugDerecha->escribir((char*) mensaje.c_str(),
			SIZE);
	while (bytesleidos < SIZE) {
		bytesleidos = this->comJugDerecha->escribir((char*) mensaje.c_str(),
				SIZE);
	}

	logMessage = getDescripcionJugador();
	logMessage.append(" - Pasé carta a la derecha: ");
	logMessage.append(mensaje);
	Logger::log(logMessage);

	logMessage = getDescripcionJugador();
	logMessage.append(" - Me quedaron: [ ");
	for (list<Carta>::iterator it = cartas.begin(); it != cartas.end(); it++){
		logMessage.append(it->convertir());
		logMessage.append(" ");
	}
	logMessage.append("]");
	Logger::log(logMessage);
}

int Jugador::leerCarta() {
	char buffer[SIZE];
	int bytesleidos = this->comJugIzquierda->leer(buffer, SIZE);
	while (bytesleidos < SIZE) {
		bytesleidos = this->comJugIzquierda->leer(buffer, SIZE);
	}
	buffer[bytesleidos] = '\0';
	this->crearCarta(buffer);

	string logMessage = getDescripcionJugador();
	logMessage.append(" - Me pasaron carta: ");
	logMessage.append(buffer);
	Logger::log(logMessage);

	return bytesleidos;
}

void Jugador::enviarMensajeCentral(string mensaje) {
	int bytesleidos = this->comJugadorCentral->escribir((char*) mensaje.c_str(),
			SIZE);
	while (bytesleidos < SIZE) {
		bytesleidos = this->comJugadorCentral->escribir((char*) mensaje.c_str(),
				SIZE);
	}
}

string Jugador::leerMensajeCentral() {

	char buffer[SIZE];
	int bytesleidos = this->comCentralJugador->leer(buffer, SIZE);
	while (bytesleidos < SIZE) {
		bytesleidos = this->comCentralJugador->leer(buffer, SIZE);
	}
	buffer[bytesleidos] = '\0';

	string logMessage = getDescripcionJugador();
	logMessage.append(" - Recibo de central: ");
	logMessage.append(buffer);
	Logger::log(logMessage);

	return buffer;

}

void Jugador::recibirCartaRepartida() {
	for (int i = 0; i < 4; i++) {
		char buffer[SIZE];
		int bytesleidos = this->comJugAdmin->leer(buffer, SIZE);
		while (bytesleidos < SIZE) {
			bytesleidos = this->comJugAdmin->leer(buffer, SIZE);
		}
		buffer[bytesleidos] = '\0';
		this->crearCarta(buffer);

		string logMessage = getDescripcionJugador();
		logMessage.append(" - Recibo carta: ");
		logMessage.append(buffer);
		Logger::log(logMessage);
	}
}

void Jugador::chancho() {
	this->pila = new LockFile((char*) PILA);
	this->pila->tomarLock();
	stringstream salida;
	salida << this->idJugador;
	string s = salida.str();
	s.append("\n");
	char* miNombre = (char*) s.c_str();
	this->pila->escribir(miNombre, 2);
	this->pila->liberarLock();
	delete this->pila;
	string logMessage = getDescripcionJugador();
	logMessage.append(" - Me agrego en la pila");
	Logger::log(logMessage);
}

int Jugador::correr() {

	string logMessage = getDescripcionJugador();
	logMessage.append(" - Comienza la ronda");
	Logger::log(logMessage);

	if (this->primerRonda) {
		this->msg = this->leerMensajeCentral();
	}
	this->primerRonda = false;
	//string msg = this->leerMensajeCentral();
	if (this->msg == REPARTIR) {
		//Los jugadores solo reciben cartas no reparten
		this->recibirCartaRepartida();
		this->jugar();
	}

	return 0;
}

/*
 * Proseguir segun protocolo
 */
void Jugador::jugar() {

	//Todos avisan que tienen sus cartas para comenzar a jugar
	this->enviarMensajeCentral(RECIBI);

	this->msg = this->leerMensajeCentral();
	assert(this->msg == VERCARTAS);

	bool rondaVigente = true;

	while (rondaVigente) {
		if (this->gane()) {
			this->enviarMensajeCentral(GANAR);
			this->chancho();
			//Ignoro el mensaje de ganar porque yo ya gane
			//msg = this->leerMensajeCentral();
			//this->enviarMensajeCentral(LISTO);
		} else {
			this->enviarMensajeCentral(PERDER);

		}

		this->msg = this->leerMensajeCentral();

		if (this->msg == PASARDERECHA) {
			this->pasarCarta();
			this->leerCarta();
			this->enviarMensajeCentral(TERMINARPASAR);
			this->msg = this->leerMensajeCentral();
		} else if (this->msg == GANAR) {
			if (this->gane()) {
				this->enviarMensajeCentral(LISTO);
				this->msg = this->leerMensajeCentral();
			} else {
				this->chancho();
				this->enviarMensajeCentral(LISTO);
				this->msg = this->leerMensajeCentral();
			}

			if (this->msg == FINJUEGO) {
				exit(0);
			}
			//Me mando repartir ahora lo sincronizo
			else {
				rondaVigente = false;
			}
		}
	}

	this->correr();

}


 /*Carta Jugador::dejarCartaInteligente() {
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
 }*/
