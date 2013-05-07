#include "JugadorAdministrador.h"


JugadorAdministrador::JugadorAdministrador(int cantJugadores) : Jugador() {
	this->mazo = new Mazo(cantJugadores);
	this->cantJugadores = cantJugadores;
	this->idJugador = 1;
}

JugadorAdministrador::JugadorAdministrador(int cantJugadores, Comunicador* comJugadorCentral, Comunicador* comCentralJugador, Comunicador* comJugDerecha, Comunicador* comJugIzquierda) : Jugador(comJugadorCentral, comCentralJugador, comJugDerecha, comJugIzquierda){
	this->mazo = new Mazo(cantJugadores);
	this->cantJugadores = cantJugadores;
	this->idJugador = 1;
}


void JugadorAdministrador::repartir(){
	this->mazo = new Mazo(this->cantJugadores);
	this->mazo->barajar();
	list<Comunicador*>::iterator it;
	for (int i = 0; i < 4; i++){
		this->tomarCarta(this->mazo->getCarta());
	}
	for (it = this->comunicadorJugadores.begin() ; it != this->comunicadorJugadores.end() ; it++){
			this->enviarCarta(*it);
		}
}

void JugadorAdministrador::enviarCarta(Comunicador* alJugadorSiguiente){
	for (int i = 0; i < 4; i++){
		Carta c = this->mazo->getCarta();
		string mensaje = c.convertir();
		//cout << c.convertir() << endl;
		int bytesleidos = alJugadorSiguiente->escribir((char*)mensaje.c_str(),SIZE);
		while (bytesleidos < SIZE){
				//sleep(1);
				bytesleidos = alJugadorSiguiente->escribir((char*)mensaje.c_str(),SIZE);
		}
	}
	cout << "Termine de repartir" << endl;
}

JugadorAdministrador::~JugadorAdministrador() {
	delete this->mazo;
	if (! this->comunicadorJugadores.empty()){
		list<Comunicador*>::iterator it;
		for (it = this->comunicadorJugadores.begin() ; it != this->comunicadorJugadores.end() ; it++){
				delete *it;
			}
	}
}

void JugadorAdministrador::agregarComunicacionJugador(Comunicador* comOtroJugador){
	this->comunicadorJugadores.push_back(comOtroJugador);
}

int JugadorAdministrador::correr(){


	if (this->primerRonda){
			this->msg = this->leerMensajeCentral();
			//this->enviarMensajeCentral(SYNCRONIZAR);
		}
	this->primerRonda = false;

	//this->msg = this->leerMensajeCentral();
	if (this->msg == REPARTIR){
		cout << "salimosss";
		if (this->idJugador == 1){
			//Soy el administrador
			this->repartir();
			this->jugar();
		}
	}

	return 0;
}

void JugadorAdministrador::jugar(){

	//Todos avisan que tienen sus cartas para comenzar a jugar
		this->enviarMensajeCentral(REPARTIR);

		//deberia leer VER
		this->msg = this->leerMensajeCentral();

		while (true){
			if(this->gane()){
				this->enviarMensajeCentral(GANAR);
				this->chancho();
				sleep(2);
				//Ignoro el mensaje de ganar porque yo ya gane
				//msg = this->leerMensajeCentral();
				//this->enviarMensajeCentral(LISTO);
			}
			else{
				this->enviarMensajeCentral(PERDER);

			}

			this->msg = this->leerMensajeCentral();
			if (this->msg == PERDER){
				this->enviarMensajeCentral(LISTO);
				this->msg = this->leerMensajeCentral();

				if (this->msg == CONTINUAR){
						this->pasarCarta();
						this->leerCarta();
						this->enviarMensajeCentral(TERMINARPASAR);
						this->msg = this->leerMensajeCentral();
					}
			}
			else if (this->msg == GANAR){
					if(this->gane()){
						this->enviarMensajeCentral(LISTO);
						this->msg = this->leerMensajeCentral();
					}
					else{
						this->chancho();
						this->enviarMensajeCentral(LISTO);
						this->msg = this->leerMensajeCentral();
					}

					if (this->msg == FINJUEGO){
						exit(0);
					}
				//Me mando repartir ahora lo sincronizo
					else{
						//this->msg = this->leerMensajeCentral();
						if (this->msg == SYNCRONIZAR){
							this->enviarMensajeCentral(SYNCRONIZAR);
						}
					}
				}




	/*
			msg = this->leerMensajeCentral();
			if (msg == CONTINUAR){
				this->pasarCarta();
				this->leerCarta();
				this->enviarMensajeCentral(TERMINARPASAR);
			}

			//msg = this->leerMensajeCentral();
			cout << msg;
			if (msg == VERCARTAS){
				cout << "Vuelve a comenzar ronda" << endl;
				break;
			}*/

		}

		this->correr();

	}




/*	//Todos avisan que tienen sus cartas para comenzar a jugar
	this->enviarMensajeCentral(REPARTIR);



	while (true){
		string msg = this->leerMensajeCentral();
		if(this->gane()){
			this->enviarMensajeCentral(GANAR);
			this->chancho();
			//Ignoro el mensaje de ganar porque yo ya gane
			//msg = this->leerMensajeCentral();
			//this->enviarMensajeCentral(LISTO);
		}
		else{
			this->enviarMensajeCentral(PERDER);

		}

		msg = this->leerMensajeCentral();
			if (msg == CONTINUAR){
				this->pasarCarta();
				this->leerCarta();
				this->enviarMensajeCentral(TERMINARPASAR);
			}
			else if (msg == GANAR){
				if(this->gane()){
					this->enviarMensajeCentral(LISTO);
					msg = this->leerMensajeCentral();
				}
				else if (msg == PERDER){
					this->chancho();
					this->enviarMensajeCentral(LISTO);
					msg = this->leerMensajeCentral();
				}
			}


		if (msg == FINJUEGO){
			exit(0);
		}


		msg = this->leerMensajeCentral();
		if (msg == CONTINUAR){
			this->pasarCarta();
			this->leerCarta();
			this->enviarMensajeCentral(TERMINARPASAR);
		}

		//msg = this->leerMensajeCentral();
		cout << msg;
		if (msg == VERCARTAS){
			cout << "Vuelve a comenzar ronda" << endl;
			break;
		}

	}

	this->correr();

}
*/
