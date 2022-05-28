#include "Puntuacion.h"
#include "string.h"
#include <iostream>
using namespace std;

Puntuacion::Puntuacion() {
	jugador[0] = '\0'; //Inicializamos el jugador a cadena vacía
    palabra[0] = '\0'; //Inicializamos la palabra a cadena vacía
    intentos=1;

}

Puntuacion::Puntuacion(const char*jug, const char *palab, int intent){
	
	strcpy(this->jugador,jug);
    strcpy(this->palabra,palab);
	this->intentos = intent;
}
Puntuacion::~Puntuacion() {
	// TODO Auto-generated destructor stub
}

Puntuacion::Puntuacion(const Puntuacion &other) {
	strcpy(this->jugador,other.jugador);
    strcpy(this->palabra,other.palabra);
    this->intentos = other.intentos;

}