#ifndef LISTAPALABRAS_H_
#define LISTAPALABRAS_H_
#include "Palabra.h"

class ListaPalabras {
public:

    Palabra* listaPalabras;
    int tamanyoLista;
	int numPalabras;

	ListaPalabras(int tamanyoLista);//constructor
	virtual ~ListaPalabras();//destructor
};

#endif 