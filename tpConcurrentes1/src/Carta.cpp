#include "Carta.h"
#include <cstring>

Carta::Carta(int palo, int numero) : palo(palo), numero(numero) {
}

Carta::~Carta() {
}

int Carta::getPalo() {
	return palo; 
}

int Carta::getNumero() {
	return numero; 
}

char* Carta::convertir() {

	/* Lo hacemos de esta forma porque al usar funciones del standard tuvimos problemas...*/
	char* p;
	if (this->getPalo() == 1){
		if (this->getNumero() == 1) p = (char*) "E01";
		else if (this->getNumero() == 2) p = (char*) "E02";
		else if (this->getNumero() == 3) p = (char*) "E03";
		else if (this->getNumero() == 4) p = (char*) "E04";
		else if (this->getNumero() == 5) p = (char*) "E05";
		else if (this->getNumero() == 6) p = (char*) "E06";
		else if (this->getNumero() == 7) p = (char*) "E07";
		else if (this->getNumero() == 8) p = (char*) "E08";
		else if (this->getNumero() == 9) p = (char*) "E09";
		else if (this->getNumero() == 10) p = (char*) "E10";
		else if (this->getNumero() == 11) p = (char*) "E11";
		else if (this->getNumero() == 12) p = (char*) "E12";
	}else if (this->getPalo() == 2){
		if (this->getNumero() == 1) p = (char*) "O01";
		else if (this->getNumero() == 2) p = (char*) "O02";
		else if (this->getNumero() == 3) p = (char*) "O03";
		else if (this->getNumero() == 4) p = (char*) "O04";
		else if (this->getNumero() == 5) p = (char*) "O05";
		else if (this->getNumero() == 6) p = (char*) "O06";
		else if (this->getNumero() == 7) p = (char*) "O07";
		else if (this->getNumero() == 8) p = (char*) "O08";
		else if (this->getNumero() == 9) p = (char*) "O09";
		else if (this->getNumero() == 10) p = (char*) "O10";
		else if (this->getNumero() == 11) p = (char*) "O11";
		else if (this->getNumero() == 12) p = (char*) "O12";
	}else if (this->getPalo() == 3){
		if (this->getNumero() == 1) p = (char*) "C01";
		else if (this->getNumero() == 2) p = (char*) "C02";
		else if (this->getNumero() == 3) p = (char*) "C03";
		else if (this->getNumero() == 4) p = (char*) "C04";
		else if (this->getNumero() == 5) p = (char*) "C05";
		else if (this->getNumero() == 6) p = (char*) "C06";
		else if (this->getNumero() == 7) p = (char*) "C07";
		else if (this->getNumero() == 8) p = (char*) "C08";
		else if (this->getNumero() == 9) p = (char*) "C09";
		else if (this->getNumero() == 10) p = (char*) "C10";
		else if (this->getNumero() == 11) p = (char*) "C11";
		else if (this->getNumero() == 12) p = (char*) "C12";
	}else if (this->getPalo() == 4){
		if (this->getNumero() == 1) p = (char*) "B01";
		else if (this->getNumero() == 2) p = (char*) "B02";
		else if (this->getNumero() == 3) p = (char*) "B03";
		else if (this->getNumero() == 4) p = (char*) "B04";
		else if (this->getNumero() == 5) p = (char*) "B05";
		else if (this->getNumero() == 6) p = (char*) "B06";
		else if (this->getNumero() == 7) p = (char*) "B07";
		else if (this->getNumero() == 8) p = (char*) "B08";
		else if (this->getNumero() == 9) p = (char*) "B09";
		else if (this->getNumero() == 10) p = (char*) "B10";
		else if (this->getNumero() == 11) p = (char*) "B11";
		else if (this->getNumero() == 12) p = (char*) "B12";
	}
	return p;
}
/*
char* Carta::convertirNumero(){
	int i = this->getNumero();
	char buffer [2], *b;
	b = itoa(i,buffer,10);
	//char* Cadena;  // Se declara la cadena, donde almacenaremos el valor de tipo int
	//sprintf(Cadena, "%d", this->getNumero());  // De este modo se copia el valor de 'numero' a la cadena 'Cadena'
	return "AS";
}*/


