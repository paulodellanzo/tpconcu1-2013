#include <iostream>
//#include "../include/ProcesoCoordinador.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "ProcesoJugadorCoordinador " << argv[1] << "de" <<  argv[2] << endl;
	dup2((int)argv[1],1);
	cout << "Escribo en el pipe atraves del stdout";
	//cin <<
	//ProcesoCoordinador coord;
	//coord.correr();	
	return 0;
}

