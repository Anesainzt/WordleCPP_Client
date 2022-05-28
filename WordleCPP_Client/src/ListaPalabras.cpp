#include "ListaPalabras.h"
#include "Palabra.h"
#include <string.h>
#include <iostream>
using namespace std;

ListaPalabras::ListaPalabras(int tamanyoLista) {
	this->tamanyoLista = tamanyoLista;
    numPalabras=0;// Inicializamos el numero de palabras en la lista a 0
    listaPalabras= new Palabra[tamanyoLista];

    

}

ListaPalabras::~ListaPalabras() {
	delete [] listaPalabras;
}


