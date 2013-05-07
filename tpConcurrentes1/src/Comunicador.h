#ifndef COMUNICADOR_H_
#define COMUNICADOR_H_

#include "Pipe.h"
#include "Mensajes.h"

class Comunicador {

private:

	Pipe pipe;

public:
	/*
	 * Esta clase se ocupa de administrar el canal de comunicacion
	 * entre los procesos utilizando Pipes
	 */
	Comunicador();
	~Comunicador();

	int escribir(char* mensaje, int datoSize);
	int leer(char* mensaje, int buffSize);

	void cerrar();
};

#endif /* COMUNICADOR_H_ */
