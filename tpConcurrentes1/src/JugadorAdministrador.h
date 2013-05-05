#ifndef JUGADORADMINISTRADOR_H_
#define JUGADORADMINISTRADOR_H_

#include "Jugador.h"
#include "Mazo.h"

class JugadorAdministrador : public Jugador {
	
	private:
		Mazo* mazo;
		//Para repartir las cartas
		list<Comunicador*> comunicadorJugadores;
	
	public:
		JugadorAdministrador(int cantJugadores);
		JugadorAdministrador(int cantJugadores, Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda);
		void agregarComunicacionJugador(Comunicador* comOtroJugador);
		~JugadorAdministrador();
		void repartir();
		void enviarCarta(Comunicador* alJugadorSiguiente);
		int correr();
		
};
		
		
		
#endif /* JUGADORADMINISTRADOR_H_ */
