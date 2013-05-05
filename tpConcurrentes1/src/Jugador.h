#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <list>
#include <string>
#include "Carta.h"
#include "Comunicador.h"


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
		int leerCarta();
		void enviarMensajeCentral(string mensaje);
		void leerMensajeCentral(string mensaje);

		Carta dejarCarta();
		void tomarCarta(Carta carta);
		bool gane();
		
};



#endif /* JUGADOR_H_ */
