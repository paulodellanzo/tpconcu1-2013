#include "Comunicador.h"

Comunicador::Comunicador() {
	Pipe p;
	this->pipe = p;
}

Comunicador::~Comunicador() {
	this->pipe.cerrar();
}

void Comunicador::cerrar() {
	this->pipe.cerrar();
}

int Comunicador::escribir(char* mensaje, int datoSize) {
	int res = this->pipe.escribir(mensaje, datoSize);
	if (res == -1) {
//		cout << "No se pudo escribir en el canal: " << this->pipe.getFdEscritura() << "-->" << strerror(errno) << endl;
		this->pipe.cerrar();
	}
	return res;
}

int Comunicador::leer(char* mensaje, int buffSize) {
	int res = this->pipe.leer(mensaje, buffSize);
	if (res == -1) {
//		cout << "No se pudo leer en el canal: " << this->pipe.getFdLectura() << "-->" << strerror(errno) << endl;
		this->pipe.cerrar();
	}
	return res;
}
