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
	this->pila->liberarLock();
	delete this->pila;
	return x;
}

/*
 * Devuelve TRUE si alguien perdio el juego
 */
bool Central::actualizarPuntaje(int IDJugador) {

	this->tablaPuntaje = new LockFile((char*) TABLA);
	this->tablaPuntaje->tomarLock();
	bool perdioAlguien = false;
	list<perdedores>::iterator it;
	string puntos="PUNTOS\n";
	for (it = this->puntaje.begin(); it != this->puntaje.end(); it++) {
		if (it->idJugador == IDJugador) {
			it->cantPerdidas++;
			if (it->cantPerdidas == 7) {
				perdioAlguien = true;
			}
		}
	stringstream salida;
	salida << it->idJugador << " - " << this->chancho.substr(0,it->cantPerdidas) << endl;
	Logger::log(salida.str());

	puntos.append(salida.str());

	}
	puntos.append("\n");
	FILE* archivo = fopen(TABLA, "w");
	fputs(puntos.c_str(),archivo);
	//fprintf(archivo, puntos.c_str());
	fclose(archivo);
	this->tablaPuntaje->liberarLock();
	//delete this->tablaPuntaje;
	return perdioAlguien;
}
/*
 * Este metodo se ocupa de que se respete el protocolo de comunicacion con los jugadores
 */
int Central::correr() {

	//Comienzo todo con REPARTIR

	//list<string> mensajesLeidos = this->leerJugadores();

	bool fin = false;

	list<string> mensajesLeidos;
	while (!fin) {

		Logger::log("Central - Comienza una ronda nueva");

		this->escribirJugadores(REPARTIR);

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

			Logger::log("Central - Me fijo si alguien ganó");

			for (it = mensajesLeidos.begin(); it != mensajesLeidos.end();
					it++) {

				if ((*it) == GANAR) {

					Logger::log("Central - Ganó un jugador");

					huboGanador = true;
					break;
				}
			}

			if (huboGanador) {

				Logger::log("Central - Aviso que ganó alguien");

				this->escribirJugadores(GANAR);

				//Debería recibir LISTO
				mensajesLeidos = this->leerJugadores();
				Logger::log("Central - Todos los jugadores se agregaron a la pila");

				int idPerdedor = this->obtenerPerdedor();
				fin = this->actualizarPuntaje(idPerdedor);

				//Espero 5 segundos para darle tiempo a consultar;
				sleep(5);

				if (fin) {

					this->escribirJugadores(FINJUEGO);

					break;

				}
			}
			//Todos escribieron que perdieron
			else {

				this->escribirJugadores(PASARDERECHA);

				//Espero TERMINARPASAR
				mensajesLeidos = this->leerJugadores();
			}
		}

	}

	cout << "TERMINO JUEGO" << endl;
	return 0;
}

