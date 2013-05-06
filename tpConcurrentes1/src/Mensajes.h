
#ifndef MENSAJES_H_
#define MENSAJES_H_

#include <iostream>
#include <string.h>

#define REPARTIR "REP"
#define VERCARTAS "VER"
#define GANAR "WIN"
#define PERDER "LOS"
#define LISTO "RDY"
#define CONTINUAR "CON"
#define TERMINARPASAR "PAS"
#define FINJUEGO "FIN"
#define SYNCRONIZAR "SYN"
#define SIZE 3
#define PILA "PILA.txt"
/*
class Mensajes {

public:

	static std::string REPARTIR;
	static std::string VER_CARTAS;
	static std::string GANAR;
	static std::string PERDER;
	static std::string LISTO;
	static std::string CONTINUAR;
	static std::string TERMINAR_PASAR;
	static std::string FIN_JUEGO;
	static std::string SYNCRONIZAR;
	static int SIZE;


	 *  static Mensajes* instance;
		Mensajes ( void );
		static Mensajes* getInstance ();
		static void destruir ();



};*/
/*
Mensajes* Mensajes :: instance = NULL;

Mensajes* Mensajes :: getInstance () {

	if ( instance == NULL )
		instance = new Mensajes ();

	return instance;
}

void Mensajes :: destruir () {
	if ( instance != NULL ) {
		delete ( instance );
		instance = NULL;
	}
}

std::string Mensajes::REPARTIR = "REP";
std::string Mensajes::VER_CARTAS = "VER";
std::string Mensajes::GANAR = "WIN";
std::string Mensajes::PERDER = "LOS";
std::string Mensajes::LISTO = "RDY";
std::string Mensajes::CONTINUAR = "CON";
std::string Mensajes::TERMINAR_PASAR = "PAS";
std::string Mensajes::FIN_JUEGO = "FIN";
std::string Mensajes::SYNCRONIZAR = "SYN";
int Mensajes::SIZE = 3;
*/
#endif /* MENSAJES_H_ */
