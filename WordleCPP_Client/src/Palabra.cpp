#include "Palabra.h"
#include "string.h"
#include <iostream>
using namespace std;

Palabra::Palabra() {
	
    palabra[0] = '\0'; //Inicializamos la palabra a cadena vacía
    tema= new char[20];
    tema[0] = '\0'; //Inicializamos el tema a cadena vacia

}

Palabra::Palabra(const char*pal, const char *tem){
	
	strcpy(this->palabra,pal);
    this->tema=new char[strlen(tem)+1];
    strcpy(this->tema,tem);
	
}
Palabra::~Palabra() {
	delete [] tema;
}

Palabra::Palabra(const Palabra &other) {
	strcpy(this->palabra,other.palabra);
    this->tema =new char[strlen(other.tema)+1];
    strcpy(this->tema,other.tema);
    

}