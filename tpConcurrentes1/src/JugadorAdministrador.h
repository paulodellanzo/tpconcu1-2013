#ifndef JUGADORADMINISTRADOR_H_
#define JUGADORADMINISTRADOR_H_

#include "Jugador.h"
#include "Mazo.h"


class JugadorAdministrador : public Jugador {
	
	private:
		Mazo* mazo;
	
	public:
		JugadorAdministrador(int cantJugadores);
		JugadorAdministrador(int cantJugadores, Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda);
		~JugadorAdministrador();
		void repartir();
		
};
		
		
		
#endif /* JUGADORADMINISTRADOR_H_ */
