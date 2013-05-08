#ifndef CENTRAL_H_
#define CENTRAL_H_

#include <list>
#include <string>
#include "Comunicador.h"
#include "LockFile.h"
#include <fstream>
#include "Logger.h"
#include "SIGINT_Handler.h"
#include "SignalHandler.h"

struct perdedores {
	int idJugador;
	int cantPerdidas;
};

class Central {

private:
	/*
	 * Tiene todos los comunicadores necesarios para comunicarse con todos los jugadores
	 */
	list<Comunicador*> comunicadoresHaciaJugadores;
	list<Comunicador*> comunicadoresDesdeJugadores;
	int cantJugadores;
	list<perdedores> puntaje;
	string chancho;
	LockFile* pila;
	SIGINT_Handler sigint_handler;

	void escribirJugadores(string mensaje);
	list<string> leerJugadores();

public:
	Central(int totalJugadores,
			list<Comunicador*> & comunicadoresHaciaJugadores,
			list<Comunicador*> & comunicadoresDesdeJugadores);
	~Central();
	bool actualizarPuntaje(int IDJugador);
	int obtenerPerdedor();
	int correr();
	void mostrarPuntaje();

};

#endif /* CENTRAL_H_ */
