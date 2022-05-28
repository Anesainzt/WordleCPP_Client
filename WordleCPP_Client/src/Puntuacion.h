#ifndef PUNTUACION_H_
#define PUNTUACION_H_

class Puntuacion {
    
public:
    char jugador[20];
    char palabra[6];
    int intentos;


	Puntuacion();//constructor
    Puntuacion( const char *jug, const char *palab, int intent);//constructor especifico
	virtual ~Puntuacion();//destructor
	Puntuacion(const Puntuacion &other);//copia
};

#endif