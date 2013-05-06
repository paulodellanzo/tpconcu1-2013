#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <list>
#include <string>
#include "Carta.h"
#include "Comunicador.h"
#include "LockFile.h"
#include "Logger.h"

using namespace std;

class Jugador {
	
public:
		int idJugador;
		list<Carta> cartas;
		int tipo;
		int cantJugadores;
		Carta dejarCartaRand();
		//Carta dejarCartaInteligente();
		Comunicador* comJugadorCentral;
		Comunicador* comCentralJugador;
		Comunicador* comJugDerecha;
		Comunicador* comJugIzquierda;
		Comunicador* comJugAdmin;
		LockFile* pila;


		Jugador();
		Jugador(Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda);
		~Jugador();
		void setID(int ID);
		int getID();
		void agregarJugAdmin(Comunicador* comJugAdmin);
		void agregarcomJugadorCentral(Comunicador* comJugadorCentral);
		void agregarcomCentralJugador(Comunicador* comCentralJugador);
		void agregarcomJugDerecha(Comunicador* comJugDerecha);
		void agregarcomJugIzquierda(Comunicador* comJugIzquierda);
		void pasarCarta();
		int leerCarta();
		void enviarMensajeCentral(string mensaje);
		string leerMensajeCentral();

		Carta dejarCarta();
		void tomarCarta(Carta carta);
		bool gane();
		void crearCarta(string cartaEnMensaje);
		void recibirCartaRepartida();
		
		int correr();
		void chancho();
		void jugar();

};



#endif /* JUGADOR_H_ */
