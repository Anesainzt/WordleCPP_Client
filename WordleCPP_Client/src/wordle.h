#ifndef WORDLE_H_
#define WORDLE_H_
#include "sqlite3.h"

void jugarWordle(/*sqlite3 * db*/);
bool procesarPalabra(const char* laRespuesta, const char* elIntento);



#endif