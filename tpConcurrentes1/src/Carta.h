#ifndef CARTA_H_
#define CARTA_H_

#include <ostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define ESPADA 1
#define ORO 2
#define COPA 3
#define BASTO 4

using namespace std;

class Carta {
	private:
		int palo, numero;
	
	public:
		Carta(int palo,int numero);
		~Carta();
		int getPalo();
		int getNumero();
		
		char* convertir();
		
};

#endif /* CARTA_H_ */
