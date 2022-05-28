#ifndef PALABRA_H_
#define PALABRA_H_

class Palabra {
    
public:
    char palabra[6];
    char * tema;
   


	Palabra();//constructor
    Palabra( const char *pal, const char *tem);//constructor especifico
	virtual ~Palabra();//destructor
	Palabra(const Palabra &other);//copia
};

#endif