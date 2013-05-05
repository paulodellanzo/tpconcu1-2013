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
	if (! this->comunicadorJugadores.empty()){
		list<Comunicador*>::iterator it;
		for (it = this->comunicadorJugadores.begin() ; it != this->comunicadorJugadores.end() ; it++){
				delete *it;
			}
	}
}

void JugadorAdministrador::agregarComunicacionJugador(Comunicador* comOtroJugador){
	this->comunicadorJugadores.push_back(comOtroJugador);
}
