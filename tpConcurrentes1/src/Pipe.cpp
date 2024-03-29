#include "Pipe.h"

Pipe::Pipe() {
	int res = pipe(this->descriptores);
	if (res == -1) {
//	    cout << "Algo salio mal con la creacion del Pipe %s\n" << strerror(errno);
	} else {
		/*fcntl ( this->descriptors[0],F_SETFL,O_NONBLOCK );
		 fcntl ( this->descriptors[1],F_SETFL,O_NONBLOCK );*/
		this->lectura = true;
		this->escritura = true;
	}
}

void Pipe::setearModo(int modo) {
	if (modo == LECTURA) {
		close(this->descriptores[1]);
		this->escritura = false;

	} else if (modo == ESCRITURA) {
		close(this->descriptores[0]);
		this->lectura = false;
	}
}

int Pipe::escribir(char* dato, int datoSize) {
	if (this->lectura == true) {
		close(this->descriptores[0]);
		this->lectura = false;
	}

	int resultado = write(this->descriptores[1], dato, datoSize);
	return resultado;
}

int Pipe::leer(char* buffer, int buffSize) {
	if (this->escritura == true) {
		close(this->descriptores[1]);
		this->escritura = false;
	}

	int resultado = read(this->descriptores[0], buffer, buffSize);
	return resultado;
}

int Pipe::getFdLectura() {
	if (this->lectura == true)
		return this->descriptores[0];
	else
		return -1;
}

int Pipe::getFdEscritura() {
	if (this->escritura == true)
		return this->descriptores[1];
	else
		return -1;
}

void Pipe::cerrar() {
	if (this->lectura == true) {
		close(this->descriptores[0]);
		this->lectura = false;
	}

	if (this->escritura == true) {
		close(this->descriptores[1]);
		this->escritura = false;
	}
}

Pipe::~Pipe() {
}
