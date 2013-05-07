#include "ProcesoCoordinador.h"
//#include "Fifo.h"
#include "Mazo.h"
#include "Carta.h"
#include <cstdlib>	//atoi
#include <string>

#define TAMBUFFER 100

using namespace std;

/*
 Central::Central(char* totalJugadores) :
 ProcesoJugador((char*)"0", totalJugadores) {
 // Abro los canales de comunicación
 cantJugadores = atoi(totalJugadores);
 aJugadores = vector<Comunicador*>();
 deJugadores = vector<Comunicador*>();
 for (int i = 1; i < cantJugadores; i++) {
 string nombre = itos(i);
 string nombreFifoAJugador = string(AJUGADOR) + nombre;
 string nombreFifoDeJugador = string(DEJUGADOR) + nombre;
 aJugadores.push_back(new Fifo( nombreFifoAJugador.c_str() ));
 deJugadores.push_back(new Fifo( nombreFifoDeJugador.c_str() ));
 }
 }


 ProcesoCoordinador::~ProcesoCoordinador() {
 vector<Comunicador*>::iterator it;
 for(it = aJugadores.begin(); it != aJugadores.end(); it++)
 delete *it;
 for(it = deJugadores.begin(); it != deJugadores.end(); it++)
 delete *it;
 }

 int ProcesoCoordinador::correr() {
 return 0;
 }


 void ProcesoCoordinador::repartirCartas() {
 Mazo mazo(cantJugadores);
 mazo.barajar();
 for (int i = 0; i < 4; i++)
 this->jugador.tomarCarta(mazo.getCarta());
 for (int i = 0; i < cantJugadores - 1; i++) {
 Carta carta = mazo.getCarta();
 int tamanioBuffer;
 char* bufferCarta = carta.serializar(&tamanioBuffer);
 aJugadores[i]->escribir(bufferCarta, tamanioBuffer);
 delete[] bufferCarta;
 }
 }


 int ProcesoCoordinador::verificarEstadoJugadores() {
 size_t tamanio = deJugadores.size();
 for (size_t i = 0; i < tamanio; i++) {

 char buffer[TAMBUFFER];
 int bytesLeidos = deJugadores[i]->leer(buffer, TAMBUFFER);
 Aviso senial = Aviso::deserializar(buffer, bytesLeidos);
 if (senial.getTipo() != OK)
 return 1;
 }
 return 0;
 }


 void ProcesoCoordinador::cerrarCanalesLectura() {
 size_t tamanio = deJugadores.size();
 for (size_t i = 0; i < tamanio; i++)
 deJugadores[i]->cerrar();
 }


 // Los cierra y los elimina
 void ProcesoCoordinador::cerrarCanalesEscritura() {
 size_t tamanio = aJugadores.size();
 for (size_t i = 0; i < tamanio; i++) {
 aJugadores[i]->cerrar();
 aJugadores[i]->eliminar();
 }
 }
 */

