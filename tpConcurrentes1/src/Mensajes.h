
#ifndef MENSAJES_H_
#define MENSAJES_H_

#include <iostream>
#include <string.h>

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

};

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

#endif /* MENSAJES_H_ */
