#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Carta.h"
#include "Comunicador.h"
#include <list>
#include <string>

using namespace std;

class Jugador {
	
	private:
		string idJugador;
		list<Carta> cartas;
		int tipo;
		Carta dejarCartaRand();
		//Carta dejarCartaInteligente();
		Comunicador* comJugadorCentral;
		Comunicador* comCentralJugador;
		Comunicador* comJugDerecha;
		Comunicador* comJugIzquierda;

	public:
		Jugador();
		Jugador(Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda);
		~Jugador();
		void pasarCarta();
		void leerCarta();
		void enviarMensajeCentral();
		void leerMensajeCentral();

		Carta dejarCarta();
		void tomarCarta(Carta carta);
		bool gane();
		
};



#endif /* JUGADOR_H_ */
