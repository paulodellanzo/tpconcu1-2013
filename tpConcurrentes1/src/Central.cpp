#include "Central.h"

Central::Central(int totalJugadores, list<Comunicador*> & comunicadoresHaciaJugadores, list<Comunicador*> & comunicadoresDesdeJugadores){
	this->cantJugadores = totalJugadores;
	this->comunicadoresHaciaJugadores = comunicadoresHaciaJugadores;
	this->comunicadoresDesdeJugadores = comunicadoresDesdeJugadores;
}

Central::~Central(){
	list<Comunicador*>::iterator it;
	for (it = this->comunicadoresHaciaJugadores.begin() ; it != this->comunicadoresHaciaJugadores.end() ; it++){
		delete *it;
	}
	for (it = this->comunicadoresDesdeJugadores.begin() ; it != this->comunicadoresDesdeJugadores.end() ; it++){
		delete *it;
	}

}

int Central::verificarJugadores(){

	return 0;
}

void Central::escribirJugadores(string mensaje){
	list<Comunicador*>::iterator it;
	for (it = this->comunicadoresHaciaJugadores.begin() ; it != this->comunicadoresHaciaJugadores.end() ; it++){
		(*it)->escribir( (char*) mensaje.c_str(), SIZE);
	}
}

void Central::leerJugadores(){


}


/*
 * Este metodo se ocupa de que se respete el protocolo de comunicacion con los jugadores
 */
int Central::correr(){

	//Comienzo todo con REPARTIR
	this->escribirJugadores(REPARTIR);


	return 0;
}

