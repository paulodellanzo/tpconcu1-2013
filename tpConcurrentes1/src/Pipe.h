#ifndef PIPE_H_
#define PIPE_H_

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ostream>
#include <stdlib.h>

#include "Comunicador.h"

#define	LECTURA		0
#define	ESCRITURA	1

using namespace std;

class Pipe : public Comunicador {

private:

	int descriptores[2];
	bool lectura;
	bool escritura;

public:
	Pipe();
	virtual ~Pipe();

	void setearModo ( int modo );

	int escribir ( string dato,int datoSize );
	int leer ( string buffer,int buffSize );

	int getFdLectura ();
	int getFdEscritura ();

	void cerrar ();
};

#endif /* PIPE_H_ */
