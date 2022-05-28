#include "wordle.h"
#include <iostream>
#include <string.h>
#include <windows.h>
#include <ctype.h>
//#include "bbdd.h"

using namespace std;

void jugarWordle(/*sqlite3 * db*/){
	HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);

	//CARGAR PALABRAS
		
		char palabra5letras[6];
		


		/*EMPEZAR JUEGO Y SELECCIONAR UNA PALABRA RANDOM de la BD (falta por hacer)
            Hay que seleccionar una palabra de la bd, pero no sé como /@Iñigo.
            Por tanto, por ahora se juega con una palabra preestablecida "adora"
        */

        /* Aqui empezaria el codigo de Iñigo para seleccionar una palabra de la bd*/


		char respuesta[6]= "adora";/* En esta variable va la palabra seleccionada que hay que adivinar*/

        /* Aqui terminaria el codigo de Iñigo para seleccionar una palabra de la bd*/

		// LOOP PARA SEGUIR JUGANDO
		int numIntentos=6;
		bool seHaAcertado=false;
		char intento[6];
		while(numIntentos>0 && !seHaAcertado){
			//RECIBIR PALABRA INSERTADA POR EL USUARIO
			SetConsoleTextAttribute(consola,7);
			cout << "\n"<<numIntentos <<" intentos restantes" << endl;
			cout <<"Introduce palabra de 5 letras. Presiona ENTER para verificar. "<< endl;
			cin>>intento;
			
			
			

			//CONVERTIR LA PALABRA EN MINUSCULA
			for(int i = 0; i<strlen(intento); i++){
				intento[i] = tolower(intento[i]);
			}

			numIntentos--;

			//VER SI SE ACIERTA O NO LA PALABRA
			seHaAcertado=procesarPalabra(respuesta, intento);


		}

		//MOSTRAR MENSAJE DE FIN DE JUEGO
		if (seHaAcertado) {
			int opcion;
			SetConsoleTextAttribute(consola,7);

			cout <<"\nFelicidades, has acertado la palabra en " <<6-numIntentos<< " intentos "<< endl;
			cout <<"1= Seguir jugando\n2= Volver al menu\n";
			cin >> opcion;
			

			switch(opcion){
				case 1:
					jugarWordle();
					break;
				case 2:
					//menuUsuario(db);
					break;

				default:
					cout <<"Opcion incorrecta\n";
					break;
	}


		}else{
			int opcion;
			SetConsoleTextAttribute(consola,7);

			cout <<"\nHas agotado los intentos...La palabra correcta era "<<respuesta<<endl;
			cout <<"1= Seguir jugando\n2= Volver al menu\n";
			cin >> opcion;


			switch(opcion){
							case 1:
									jugarWordle();
									break;
							case 2:
									//menuUsuario(db);
									break;

							default:
									cout <<"Opcion incorrecta\n";
									break;
								}

		}

		



}


bool procesarPalabra(const char* laRespuesta, const char* elIntento){

	// pista
	char pista[6]="-----";
	
	
	//indicar si la letra en la respuesta se encuentra en la pista
	bool flagsRespuesta[5]={false,false,false,false,false};

	if(strlen(elIntento)==5){ //NOTA: Equivocarse y no poner una palabra de 5 letras implica perder un intento

		// B=Bien= la letra esta justo en esa posicion de la palabra
		for (int i = 0;  i< 5; i++) {
			if (elIntento[i] == laRespuesta[i]) {
				pista[i] = 'B';
				flagsRespuesta[i]=true;
			}

		}

		// S=Si= la letra en esa posicion esta en algun sitio de la palabra
		for (int i = 0;  i< 5; i++) {
				if (pista[i] == '-') {
					for (int j = 0;  j< 5; j++) {
							if (elIntento[i] == laRespuesta[j] && !flagsRespuesta[j]) {
								//Hay coincidencia en otra posicion y no se ha usado como pista

								pista[i] = 'S';

								flagsRespuesta[j]=true;

								break;//terminar loop porque no queremos m�ltiples pistas para la misma letra
							}
						}
				}
			}
	}else{
		cout<<"La palabra tiene que ser de 5 letras!"<<endl;
		
	}


	for (int i = 0; i < strlen(pista); i++){

		if (pista[i]=='B')
		{
			HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(consola,2);
			cout << elIntento[i];




		}else if (pista[i]=='S'){
			HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(consola,6);
			cout << elIntento[i];




		}else if (pista[i]=='-'){
			HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(consola,8);
			cout << elIntento[i];




		}

	}



	return strcmp(pista, "BBBBB") ==0;//Si coincide con strcmp devuelve 0, significa que se ha acertado la palabra
}