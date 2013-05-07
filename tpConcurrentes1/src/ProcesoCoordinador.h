#ifndef PROCESOCOORDINADOR_H_
#define PROCESOCOORDINADOR_H_

//#include "ProcesoJugador.h"
//#include "Comunicador.h"
#include <vector>

class ProcesoCoordinador {
public:
	ProcesoCoordinador(char* totalJugadores);
	~ProcesoCoordinador();
	int correr();

private:
	//std::vector<Comunicador*> aJugadores, deJugadores;
	int cantJugadores;

	void repartirCartas();
	int verificarEstadoJugadores();
	void cerrarCanalesLectura();
	// Los cierra y los elimina
	void cerrarCanalesEscritura();

};

#endif /* PROCESOCOORDINADOR_H_ */
