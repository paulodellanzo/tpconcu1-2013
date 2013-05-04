#ifndef PROCESOJUGADOR_H_
#define PROCESOJUGADOR_H_

//#include "Receptor.h"
//#include "Trasmisor.h"
#include "Jugador.h"
#include "Comunicador.h"
//#include "Aviso.h"
#include "Carta.h"
#include <string>

class ProcesoJugador {
	public:
		ProcesoJugador(char* unJugador, char* totalJugadores){
			char* a = unJugador;
			char* b = totalJugadores;
		}
		~ProcesoJugador(){

		}
		int correr(){
			cout << "hola" << endl;
			return 0;
		}
		
	protected:
		Jugador jugador;
		std::string jugadorNombre, totalJugadores;
		//Comunicador *aEstadistico;
		
		std::string itos(int num);
		void pasarCarta();
		void recibirCarta();
		void abrirCanalLecturaCarta();
		void abrirCanalEscrituraCarta();
		void avisar(Comunicador* canal, int tipoAviso);
		//Aviso recibirAviso(Comunicador *canal);
		void matarRecibidorSiguiente();

	private:
		Comunicador *aCoord, *deCoord;
		void abrirCanalesCoordinador();
		void cerrarCanalesCoordinador();
		void recibirCartasIniciales();
		int esperarAvisoDelCoodinador();
		std::string incrementarJugador();
		//void abrirCanalEstadistico();
};

#endif /* PROCESOJUGADOR_H_ */

