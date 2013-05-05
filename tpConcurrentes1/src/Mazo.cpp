#include "Mazo.h"

#include <algorithm>    // random_shuffle
#include <ctime>
#include <cstdlib>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

/*
 * Creo un mazo de cartas según la cantidad de cartas
 * */
Mazo::Mazo(int cantCartas) {
	mazo = vector<Carta>();
	for (int i = 0; i < cantCartas; i++){
		mazo.push_back(Carta("ES", this->itos(i)));
		//cout << "CartaNRO:" << i << endl;
	}
	for (int i = 0; i < cantCartas; i++)
		mazo.push_back(Carta("OR", this->itos(i)));
	for (int i = 0; i < cantCartas; i++)
		mazo.push_back(Carta("CO", this->itos(i)));
	for (int i = 0; i < cantCartas; i++)
		mazo.push_back(Carta("BA", this->itos(i)));
}


Mazo::~Mazo() {
}

bool Mazo::estaVacio() {
	return mazo.empty();
}

/*
 * Saco la ultima carta del mazo si el mazo no está vacío
 * */
Carta Mazo::getCarta() {
	Carta aux = mazo.back();
	mazo.pop_back();
	return aux;
}

string Mazo::itos(int number) {
	stringstream salida;
	salida << number;
	return salida.str();
}

void Mazo::barajar() {
	srand ( unsigned ( time(0) ) );
	random_shuffle (mazo.begin(), mazo.end());
}


	
