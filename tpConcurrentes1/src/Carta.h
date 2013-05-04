#ifndef CARTA_H_
#define CARTA_H_

#include <ostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define ESPADA 1
#define ORO 2
#define COPA 3
#define BASTO 4

using namespace std;

class Carta {
	private:
		string palo, numero;
	
	public:
		Carta(string palo,string numero);
		~Carta();
		string getPalo();
		string getNumero();
		
		string convertir();
		
};

#endif /* CARTA_H_ */
