#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <list>
#include <string>
#include "Carta.h"
#include "Comunicador.h"

using namespace std;

class Jugador {
	
public:
		string idJugador;
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


		Jugador();
		Jugador(Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda);
		~Jugador();
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

};



#endif /* JUGADOR_H_ */
