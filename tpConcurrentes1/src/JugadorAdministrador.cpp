#include "JugadorAdministrador.h"


JugadorAdministrador::JugadorAdministrador(int cantJugadores) : Jugador() {
	this->mazo = new Mazo(cantJugadores);
	this->cantJugadores = cantJugadores;
	this->idJugador = "1";
}

JugadorAdministrador::JugadorAdministrador(int cantJugadores, Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda) : Jugador(comJugadorCentral, comCentralJugador, comJugDerecha, comJugIzquierda){
	this->mazo = new Mazo(cantJugadores);
	this->cantJugadores = cantJugadores;
	this->idJugador = "1";
}


void JugadorAdministrador::repartir(){
	this->mazo = new Mazo(this->cantJugadores);
	this->mazo->barajar();
	list<Comunicador*>::iterator it;
	for (int i = 0; i < 4; i++){
		this->tomarCarta(this->mazo->getCarta());
	}
	for (it = this->comunicadorJugadores.begin() ; it != this->comunicadorJugadores.end() ; it++){
			this->enviarCarta(*it);
		}
}

void JugadorAdministrador::enviarCarta(Comunicador* alJugadorSiguiente){
	for (int i = 0; i < 4; i++){
		Carta c = this->mazo->getCarta();
		string mensaje = c.convertir();
		//cout << c.convertir() << endl;
		int bytesleidos = alJugadorSiguiente->escribir((char*)mensaje.c_str(),SIZE);
		while (bytesleidos < SIZE){
				//sleep(1);
				bytesleidos = alJugadorSiguiente->escribir((char*)mensaje.c_str(),SIZE);
		}
	}
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

int JugadorAdministrador::correr(){

	bool corriendo = true;
	string msg = this->leerMensajeCentral();
	if (msg == REPARTIR){
		cout << "salimosss";
		if (this->idJugador == "1"){
			//Soy el administrado
			this->repartir();
		}
	}

	return 0;
}

