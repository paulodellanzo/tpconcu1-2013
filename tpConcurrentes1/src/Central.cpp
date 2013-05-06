#include "Central.h"

Central::Central(int totalJugadores, list<Comunicador*> & comunicadoresHaciaJugadores, list<Comunicador*> & comunicadoresDesdeJugadores){
	this->cantJugadores = totalJugadores;
	this->comunicadoresHaciaJugadores = comunicadoresHaciaJugadores;
	this->comunicadoresDesdeJugadores = comunicadoresDesdeJugadores;
	list<perdedores> puntajeAux;
	for (int i = 1; i < totalJugadores + 1; i++){
		perdedores p;
		p.idJugador = i;
		p.cantPerdidas = 0;
		puntajeAux.push_back(p);
	}
	this->puntaje = puntajeAux;
	this->chancho = "CHANCHO";
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

list<string> Central::leerJugadores(){
	list<string> mensajesRecibidos;
	list<Comunicador*>::iterator it;
	for (it = this->comunicadoresDesdeJugadores.begin() ; it != this->comunicadoresDesdeJugadores.end() ; it++){
		//(*it)->escribir( (char*) mensaje.c_str(), SIZE);
		char buffer[SIZE];
		int bytesleidos = (*it)->leer(buffer,SIZE);
		while (bytesleidos < SIZE){
			bytesleidos = (*it)->leer(buffer,SIZE);
		}
		buffer [bytesleidos] = '\0';
		mensajesRecibidos.push_back(buffer);
	}
	return mensajesRecibidos;
}

int Central::obtenerPerdedor(){
	this->pila = new LockFile((char*)PILA);
	this->pila->tomarLock();
	FILE* archivo = fopen(PILA,"r");
	int x;
	while(!feof(archivo)){
		fscanf(archivo ,"%d",&x);
	}
	cout << "Perdio: " << x;
	this->pila->liberarLock();
	delete this->pila;
	return x;
}

/*
 * Devuelve TRUE si alguien perdio el juego
 */
bool Central::actualizarPuntaje(int IDJugador){

	bool perdioAlguien = false;
	list<perdedores>::iterator it;
	cout << "Puntaje actual: " << endl;
	for (it = this->puntaje.begin() ; it != this->puntaje.end() ; it++){
		if (it->idJugador == IDJugador){
			it->cantPerdidas++;
			if (it->cantPerdidas == 7){
				perdioAlguien = true;
			}
		}
		cout << it->idJugador << " - " << this->chancho.substr(0,it->cantPerdidas) << endl;
	}
	return perdioAlguien;
}
/*
 * Este metodo se ocupa de que se respete el protocolo de comunicacion con los jugadores
 */
int Central::correr(){

	//Comienzo todo con REPARTIR

	list<string> mensajesLeidos = this->leerJugadores();

	bool fin = false;

	int contarVueltas = 1;

	while(!fin){
		this->escribirJugadores(REPARTIR);

		list<string> mensajesLeidos = this->leerJugadores();
		list<string>::iterator it;

		for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
			cout << "lei: " << *it;
		}



		bool huboGanador = false;
		while (!huboGanador){

			sleep(0.1);

			//Hago que lean sus cartas y me avisen si ganaron o no
			this->escribirJugadores(VERCARTAS);
			mensajesLeidos = this->leerJugadores();

			//int nroJugador = 1;

			for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
				cout << "lei:-- " << *it;
				if ( (*it) == GANAR ){
					huboGanador = true;
				}
			}

			if (huboGanador){
				this->escribirJugadores(GANAR);
				int idPerdedor = this->obtenerPerdedor();
				fin = this->actualizarPuntaje(idPerdedor);

				contarVueltas++;
				if (contarVueltas == 2){
					fin = true;
				}
				mensajesLeidos = this->leerJugadores();
				//Deberia leer el LISTO de los jugadores
				for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
						cout << "L:--- " << *it;
				}
				if (fin){
					this->escribirJugadores(FINJUEGO);
				}
				else{
					this->escribirJugadores(REPARTIR);
				}
			}
			//Todos escribieron que perdieron
			else {
				this->escribirJugadores(CONTINUAR);
				mensajesLeidos = this->leerJugadores();
				for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
						cout << "Lee:--- " << *it;
				}
				//this->escribirJugadores(VERCARTAS);
			}
		}
/*
		mensajesLeidos = this->leerJugadores();
		for (it = mensajesLeidos.begin(); it != mensajesLeidos.end(); it++){
				cout << "cont: " << *it;
		}
*/


	}


	return 0;
}

