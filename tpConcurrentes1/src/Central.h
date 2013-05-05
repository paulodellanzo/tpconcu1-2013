
#ifndef CENTRAL_H_
#define CENTRAL_H_

#include <list>
#include <string>
#include "Comunicador.h"

class Central  {

	private:
		/*
		 * Tiene todos los comunicadores necesarios para comunicarse con todos los jugadores
		 */
		list<Comunicador*> comunicadoresHaciaJugadores;
		list<Comunicador*> comunicadoresDesdeJugadores;
		int cantJugadores;

		int verificarJugadores();
		void escribirJugadores(string mensaje);
		void leerJugadores();

		//Mensajes* protocolo = Mensajes::getInstance();

	public:
		Central(int totalJugadores, list<Comunicador*> & comunicadoresHaciaJugadores, list<Comunicador*> & comunicadoresDesdeJugadores);
		~Central();
		int correr();

};


#endif /* CENTRAL_H_ */
