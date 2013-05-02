#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Carta.h"
#include <list>
#include <string>

class Jugador {
	
	private:
		std::string nombreJugador;
		std::list<Carta> cartas;
		int jugada;
		//Carta dejarCartaInteligente();
		Carta dejarCartaRandom();
		
	public:
		Jugador();
		~Jugador();
		void tomarCarta(Carta carta);
		
		/* Devuelve una carta para pasarla a un rival.
		 * Pre: debe tener al menos una carta. */
		Carta dejarCarta(); 
		bool gano();

};



#endif /* JUGADOR_H_ */
