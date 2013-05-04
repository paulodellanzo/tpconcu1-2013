#include "ProcesoJugador.h"
#include "Carta.h"
#include "Pipe.h"
//#include "Canales.h"
#include <cstdlib>  // atoi
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream> 	// stringstream

#include <iostream> //cout

#define TAMBUFFER 100

using namespace std;
/*
ProcesoJugador::ProcesoJugador(char* unJugador, char* totalJugadores) : Receptor(), Trasmisor() {
	this->jugadorNombre = string(unJugador);
	this->totalJugadores = string(totalJugadores);
	this->jugador = Jugador();
	
	//abrirCanalEstadistico();
	
	// Creo el proceso Recibidor
	int pidRecibidor = fork();
	if (pidRecibidor == 0) { 
		execlp((char*) "./procRecibidor", (char*) "procRecibidor", unJugador, (char*) NULL);
	}
	
	// Creo el proceso Perdedor
	int pidPerdedor = fork();
	if (pidPerdedor == 0) { 
		execlp((char*) "./procPerdedor", (char*) "procPerdedor", unJugador, (char*) NULL);
	}
	
}


ProcesoJugador::~ProcesoJugador() {	
	// COMENTO SI NO TIRA FALLO CON glibc
	//delete aCoord;
	//delete deCoord;
}


int ProcesoJugador::correr() {
	abrirCanalesCoordinador();	
	
	abrirCanalLecturaCarta();
	abrirCanalEscrituraCarta();
	
	cout << "JUG Voy a recibir cartas"<<endl;
		
	recibirCartasIniciales();
	
	cout << "jugador" << jugadorNombre << ": 01" << endl;
	Aviso aviso = recibirAviso(deCoord);
	int rondaTerminada = 0;
		
	/*	Evidentemente hay que hacer cosas diferentes. */
	/*	(esto va dentro de otro while)
	if(aviso.getTipo() == FINDELJUEGO || aviso.getTipo() == FINDERONDA)
		rondaTerminada = 1;
	
	while( ! rondaTerminada ) {
		
		pasarCarta();
		
		recibirCarta();
		
		cout << "Jugador "<< this->jugadorNombre<< " juega mano"<<endl;
		
		if (jugador.gano()) {
			avisar(aCoord, GANO);
			//avisar(aEstadistico, GANO);
			cout << "GANEEEE!!! Soy Jugador "<< this->jugadorNombre << endl;
			
		} else {
			avisar(aCoord, OK);	
		}
		aviso = recibirAviso(deCoord);
		if (aviso.getTipo() != OK) {
			rondaTerminada = 1;
			
			// SOLO PARA LA PRUEBA MATO AL RECIBIDOR siguiente
			matarRecibidorSiguiente(); 
		}
	}
	wait(NULL);	// procRecibidor
	wait(NULL); // procPerdedor
	
	cerrarCanalLectura();
	cerrarCanalEscritura();
	cerrarCanalesCoordinador();
	
	return 0;
}


void ProcesoJugador::abrirCanalLecturaCarta() {
	string archivo = string(RECIBIDORJUGADOR) + this->jugadorNombre;
	Receptor::abrirCanalLectura((char*) archivo.c_str());
}


void ProcesoJugador::abrirCanalEscrituraCarta() {
	string valor = this->jugadorNombre;
	
	// El jugador debe "conectarse" con el siguiente.
	// Si es el ultimo, debe conectarse con el primero
	if (jugadorNombre.compare(totalJugadores) != 0)
		valor = incrementarJugador();
	else
		valor = itos(1);
	string archivo = string(JUGADORRECIBIDOR) + valor;
	Trasmisor::abrirCanalEscritura((char*) archivo.c_str());
}

/*
void ProcesoJugador::abrirCanalEstadistico() {
	string nombreFifo = string(JUGADORESTAD) + this->jugadorNombre;
	aEstadistico = new Fifo( nombreFifo.c_str() );
}


void ProcesoJugador::abrirCanalesCoordinador() {
	string nombreACoord = string(JUGADORCOORD) + jugadorNombre;
	aCoord = new Fifo( nombreACoord.c_str() );
	string nombreDeCoord = string(COORDJUGADOR) + jugadorNombre;
	deCoord = new Fifo( nombreDeCoord.c_str() );
}


void ProcesoJugador::cerrarCanalesCoordinador() {
	deCoord->cerrar();
	aCoord->cerrar();
	aCoord->eliminar();
}


void ProcesoJugador::matarRecibidorSiguiente() {
	int tamBuff;
	Aviso matar(FINDELJUEGO);
	char* buffMatar = matar.serializar(&tamBuff);
	escribir(buffMatar, tamBuff);
	delete[] buffMatar;
}	

void ProcesoJugador::pasarCarta() {
	int tamBuff;
	Carta cartaAPasar = jugador.dejarCarta();
	char* buffCarta = cartaAPasar.serializar(&tamBuff);
	escribir(buffCarta, tamBuff);
	delete[] buffCarta;
}


string ProcesoJugador::incrementarJugador() {
	int valor = atoi((this->jugadorNombre).c_str()) + 1;
	return itos(valor);
}


string ProcesoJugador::itos(int num) {
	string str;
	stringstream sal;
	sal << num;
	return sal.str();
}


void ProcesoJugador::recibirCarta() {
	leer();
	Carta cartaNueva = Carta::deserializar(buffer, bytesLeidos);
	jugador.tomarCarta(cartaNueva);
}	


void ProcesoJugador::recibirCartasIniciales() {
	for (int i = 0; i < 4; i++) {
		char buffer[TAMBUFFER];
		cout<< "JUG voy a leer carta "<<i<<endl;
		int leido = deCoord->leer(buffer, TAMBUFFER);
		Carta carta = Carta::deserializar(buffer, leido);
		jugador.tomarCarta(carta);
		cout << "JUG tomo carta "<< i<<endl;
		// Le mando un ACK por cada carta recibida
		avisar(aCoord, OK);
	}
}


Aviso ProcesoJugador::recibirAviso(Comunicador *canal) {
	char bufferAviso[TAMBUFFER];
	int bytesLeidos = canal->leer(bufferAviso, TAMBUFFER);
	return Aviso::deserializar(bufferAviso, bytesLeidos);
}


void ProcesoJugador::avisar(Comunicador* canal, int tipoAviso) {
	Aviso aviso(tipoAviso);
	int tamanioBuffer;
	char *bufferAviso = aviso.serializar(&tamanioBuffer);
	canal->escribir(bufferAviso, tamanioBuffer);
	delete[] bufferAviso;
}
*/
