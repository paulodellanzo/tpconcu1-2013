#include "Carta.h"
#include <cstring>

Carta::Carta(string palo, string numero) :
		palo(palo), numero(numero) {
}

Carta::~Carta() {
}

string Carta::getPalo() {
	return palo;
}

string Carta::getNumero() {
	return numero;
}

string Carta::convertir() {
	/* Convertimos a la carta en un solo string para transimitirla luego como un dato*/
	string p = this->getPalo();
	p.append(this->getNumero());
	return p;
}

