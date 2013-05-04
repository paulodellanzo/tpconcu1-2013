#ifndef COMUNICADOR_H_
#define COMUNICADOR_H_

class Comunicador {
	
	public:
		/*
		Comunicador();
		virtual ~Comunicador();
		*/
		
		virtual int escribir ( char* dato,int datoSize ) = 0;
		virtual int leer ( char* buffer,int buffSize ) = 0;
		
		virtual void cerrar () = 0;
		virtual void eliminar () = 0;
};

#endif /* COMUNICADOR_H_ */
