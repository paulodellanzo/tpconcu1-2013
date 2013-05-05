#include "JugadorAdministrador.h"



JugadorAdministrador::JugadorAdministrador(int cantJugadores) : Jugador() {
	this->mazo = new Mazo(cantJugadores);
}

JugadorAdministrador::JugadorAdministrador(int cantJugadores, Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda) : Jugador(comJugadorCentral, comCentralJugador, comJugDerecha, comJugIzquierda){
	this->mazo = new Mazo(cantJugadores);
}


void JugadorAdministrador::repartir(){
	this->mazo->barajar();
}

JugadorAdministrador::~JugadorAdministrador() {
	delete this->mazo;
}
