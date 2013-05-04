#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Carta.h"
#include <list>
#include <string>

using namespace std;

class Jugador {
	
	private:
		string idJugador;
		list<Carta> cartas;
		int jugada;
		Carta dejarCartaRand();
		//Carta dejarCartaInteligente();
		

	public:
		Jugador();
		~Jugador();
		Carta dejarCarta();
		void tomarCarta(Carta carta);
		bool gane();
		
};



#endif /* JUGADOR_H_ */
