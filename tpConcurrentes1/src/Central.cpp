#include "Central.h"

Central::Central(int totalJugadores,
		list<Comunicador*> & comunicadoresHaciaJugadores,
		list<Comunicador*> & comunicadoresDesdeJugadores) {
	this->cantJugadores = totalJugadores;
	this->comunicadoresHaciaJugadores = comunicadoresHaciaJugadores;
	this->comunicadoresDesdeJugadores = comunicadoresDesdeJugadores;

	Logger::log("Central - Constructor de central");

	list<perdedores> puntajeAux;
	for (int i = 1; i < totalJugadores + 1; i++) {

		perdedores p;
		p.idJugador = i;
		p.cantPerdidas = 0;
		puntajeAux.push_back(p);
	}
	this->puntaje = puntajeAux;

	string mensaje = "Central - Creo la lista de perdedores con ";
	mensaje.append(Logger::itos((int)this->puntaje.size()));
	mensaje.append(" jugadores");
	Logger::log(mensaje);

	this->chancho = "CHANCHO";
}

Central::~Central() {
	list<Comunicador*>::iterator it;
	for (it = this->comunicadoresHaciaJugadores.begin();
			it != this->comunicadoresHaciaJugadores.end(); it++) {
		delete *it;
	}
	for (it = this->comunicadoresDesdeJugadores.begin();
			it != this->comunicadoresDesdeJugadores.end(); it++) {
		delete *it;
	}

}

int Central::verificarJugadores() {

	return 0;
}

void Central::escribirJugadores(string mensaje) {
	string logMessage = "Central - envío a todos el mensaje: ";
	logMessage.append(mensaje);
	Logger::log(logMessage);

	list<Comunicador*>::iterator it;
	for (it = this->comunicadoresHaciaJugadores.begin();
			it != this->comunicadoresHaciaJugadores.end(); it++) {
		(*it)->escribir((char*) mensaje.c_str(), SIZE);
	}
}

list<string> Central::leerJugadores() {
	list<string> mensajesRecibidos;
	list<Comunicador*>::iterator it;
	for (it = this->comunicadoresDesdeJugadores.begin();
			it != this->comunicadoresDesdeJugadores.end(); it++) {
		//(*it)->escribir( (char*) mensaje.c_str(), SIZE);
		char buffer[SIZE];
		int bytesleidos = (*it)->leer(buffer, SIZE);
		while (bytesleidos < SIZE) {
			bytesleidos = (*it)->leer(buffer, SIZE);
		}
		buffer[bytesleidos] = '\0';
		mensajesRecibidos.push_back(buffer);

		string logMessage = "Central - Recibo de jugador: ";
		logMessage.append(buffer);
		Logger::log(logMessage);

	}
	return mensajesRecibidos;
}

int Central::obtenerPerdedor() {
	this->pila = new LockFile((char*) PILA);
	this->pila->tomarLock();
	FILE* archivo = fopen(PILA, "r");
	int x;
	while (!feof(archivo)) {
		fscanf(archivo, "%d", &x);
	}
//	cout << "Perdio: " << x;
	this->pila->liberarLock();
	delete this->pila;
	return x;
}

/*
 * Devuelve TRUE si alguien perdio el juego
 */
bool Central::actualizarPuntaje(int IDJugador) {

	bool perdioAlguien = false;
	list<perdedores>::iterator it;
//	cout << "Puntaje actual: " << endl;
	for (it = this->puntaje.begin(); it != this->puntaje.end(); it++) {
		if (it->idJugador == IDJugador) {
			it->cantPerdidas++;
			if (it->cantPerdidas == 7) {
				perdioAlguien = true;
			}
		}
//		cout << it->idJugador << " - " << this->chancho.substr(0,it->cantPerdidas) << endl;
	}
	return perdioAlguien;
}
/*
 * Este metodo se ocupa de que se respete el protocolo de comunicacion con los jugadores
 */
int Central::correr() {

	//Comienzo todo con REPARTIR

	//list<string> mensajesLeidos = this->leerJugadores();

	bool fin = false;

	int contarVueltas = 1;

	list<string> mensajesLeidos;
	while (!fin) {

		Logger::log("Central - Comienza una ronda nueva");

		if (contarVueltas == 1) {
			this->escribirJugadores(REPARTIR);
		}

		mensajesLeidos = this->leerJugadores();
		list<string>::iterator it;

		for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++) {
		}

		bool huboGanador = false;
		while (!huboGanador) {

			Logger::log("Central - Comienza una transferencia de cartas");

			//Hago que lean sus cartas y me avisen si ganaron o no
			this->escribirJugadores(VERCARTAS);
			mensajesLeidos = this->leerJugadores();

			//int nroJugador = 1;

			for (it = mensajesLeidos.begin(); it != mensajesLeidos.end();
					it++) {
				//Lee LOS o WIN
//				cout << "---- los o win " << *it;
				if ((*it) == GANAR) {
					huboGanador = true;
					break;
				}
			}

			if (huboGanador) {
				this->escribirJugadores(GANAR);

				contarVueltas++;
				if (contarVueltas == 2) {
					fin = true;
				}
				mensajesLeidos = this->leerJugadores();
				//Deberia leer el LISTO de los jugadores
				for (it = mensajesLeidos.begin(); it != mensajesLeidos.end();
						it++) {
//						cout << " rdy:-- " << *it;
				}

				//int idPerdedor = this->obtenerPerdedor();
				//fin = this->actualizarPuntaje(idPerdedor);

				if (fin) {

					this->escribirJugadores(FINJUEGO);

					break;

				} else {
					this->escribirJugadores(REPARTIR);
//					mensajesLeidos = this->leerJugadores();
//					for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
//							cout << " Sincronizo " << *it;
//					}break;

				}
			}
			//Todos escribieron que perdieron
			else {

				this->escribirJugadores(PERDER);

				mensajesLeidos = this->leerJugadores();
				for (it = mensajesLeidos.begin(); it != mensajesLeidos.end();
						it++) {
//						cout << " Listo " << *it;
				}

				this->escribirJugadores(CONTINUAR);
				mensajesLeidos = this->leerJugadores();
				//Deberia leer TERMINARPASAR
				for (it = mensajesLeidos.begin(); it != mensajesLeidos.end();
						it++) {
//						cout << "PAS  " << *it;
				}
				//this->escribirJugadores(VERCARTAS);
			}
		}
		/*
		 mensajesLeidos = this->leerJugadores();
		 for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
		 cout << "cont: " << *it;
		 }
		 */ //

	}

//	cout << "TERMINO JUEGO" << endl;
	return 0;
}

