#include "ProcesoJugador.h"
#include <iostream>		// cout

using namespace std;

int main2(int argc, char **argv) {
	
    cout << "ProcesoJugador " << argv[1] << " de " << argv[2] << endl;
    
    ProcesoJugador procesoJugador(argv[1], argv[2]);
    procesoJugador.correr();
    
    return 0;
}
