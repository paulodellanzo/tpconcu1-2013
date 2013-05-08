#include "JugadorAdministrador.h"

JugadorAdministrador::JugadorAdministrador(int cantJugadores) :
		Jugador() {
	this->mazo = new Mazo(cantJugadores);
	this->cantJugadores = cantJugadores;
	this->idJugador = 1;
}

JugadorAdministrador::JugadorAdministrador(int cantJugadores,
		Comunicador* comJugadorCentral, Comunicador* comCentralJugador,
		Comunicador* comJugDerecha, Comunicador* comJugIzquierda) :
		Jugador(comJugadorCentral, comCentralJugador, comJugDerecha,
				comJugIzquierda) {
	this->mazo = new Mazo(cantJugadores);
	this->cantJugadores = cantJugadores;
	this->idJugador = 1;
}

void JugadorAdministrador::repartir() {
	this->mazo = new Mazo(this->cantJugadores);
	this->mazo->barajar();
	this->cartas.clear();
	list<Comunicador*>::iterator it;
	for (int i = 0; i < 4; i++) {
		Carta carta = this->mazo->getCarta();

		string logMessage = getDescripcionJugador();
		logMessage.append(" - Tomo carta: ");
		logMessage.append(carta.getPalo());
		logMessage.append(carta.getNumero());
		Logger::log(logMessage);

		this->tomarCarta(carta);
	}
	for (it = this->comunicadorJugadores.begin();
			it != this->comunicadorJugadores.end(); it++) {
		this->enviarCarta(*it);
	}
}

void JugadorAdministrador::enviarCarta(Comunicador* alJugadorSiguiente) {
	for (int i = 0; i < 4; i++) {
		Carta c = this->mazo->getCarta();
		string mensaje = c.convertir();
		int bytesleidos = alJugadorSiguiente->escribir((char*) mensaje.c_str(),
				SIZE);
		while (bytesleidos < SIZE) {
			bytesleidos = alJugadorSiguiente->escribir((char*) mensaje.c_str(),
					SIZE);
		}
	}
}

JugadorAdministrador::~JugadorAdministrador() {
	delete this->mazo;
	if (!this->comunicadorJugadores.empty()) {
		list<Comunicador*>::iterator it;
		for (it = this->comunicadorJugadores.begin();
				it != this->comunicadorJugadores.end(); it++) {
			delete *it;
		}
	}
}

void JugadorAdministrador::agregarComunicacionJugador(
		Comunicador* comOtroJugador) {
	this->comunicadorJugadores.push_back(comOtroJugador);
}

int JugadorAdministrador::correr() {

	string logMessage = getDescripcionJugador();
	logMessage.append(" - Comienza la ronda");
	Logger::log(logMessage);

	if (this->primerRonda) {
		this->msg = this->leerMensajeCentral();
	}
	this->primerRonda = false;

	//this->msg = this->leerMensajeCentral();
	if (this->msg == REPARTIR) {
		if (this->idJugador == 1) {
			//Soy el administrador
			this->repartir();
			this->jugar();
		}
	}

	return 0;
}

void JugadorAdministrador::jugar() {

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
			else {
				rondaVigente = false;
			}
		}

	}

	this->correr();

}

