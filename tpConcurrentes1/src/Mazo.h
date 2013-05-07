#ifndef MAZO_H_
#define MAZO_H_

#include "Carta.h"
#include <vector>

class Mazo {
private:
	std::vector<Carta> mazo;

public:
	Mazo(int cantCartas);
	~Mazo();
	bool estaVacio();
	void barajar();
	Carta getCarta();
	string itos(int number);
};

#endif /* MAZO_H_ */
