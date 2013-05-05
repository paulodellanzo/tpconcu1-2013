
#ifndef CONVERTIDOR_H_
#define CONVERTIDOR_H_

#include <iostream>
#include <string.h>
class Convertidor {

		public:

		/* Las clases que implementen esta interfaz devuelven un string
		 * con los datos que sean necesarios para enviar datos
		 * */

		virtual ~Convertidor();
		virtual std::string convertir () = 0;

};


#endif /* CONVERTIDOR_H_ */
