#include "Mazo.h"

#include <algorithm>    // random_shuffle
#include <ctime>        // time
#include <cstdlib>      // srand
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

/* Instancia un mazo de cartas con cantCartas de cada palo 
 * Pre: cantCartas >= 1
 * Post: las cartas quedan ordenadas de 1 a cantCartas, y por palo.*/
Mazo::Mazo(int cantCartas) {
	mazo = vector<Carta>();
	for (int i = 1; i <= cantCartas; i++)
		mazo.push_back(Carta(ORO, i));
	for (int i = 1; i <= cantCartas; i++)
		mazo.push_back(Carta(COPA, i));
	for (int i = 1; i <= cantCartas; i++)
		mazo.push_back(Carta(ESPADA, i));
	for (int i = 1; i <= cantCartas; i++)
		mazo.push_back(Carta(BASTO, i));
}


Mazo::~Mazo() {
}


bool Mazo::estaVacio() {
	return mazo.empty();
}

void Mazo::barajar() {
	srand ( unsigned ( time(0) ) );
	random_shuffle (mazo.begin(), mazo.end() );
}

/* Devuelve la ultima carta del mazo.
 * Pre: el mazo no está vacío */
Carta Mazo::getCarta() {
	//if ( this->estaVacio() )
	//	return NULL;
	// Lanzamos una excepción???!?!?!?!??!?!?!
	Carta var = mazo.back();
	mazo.pop_back();
	
	return var;
}
	
