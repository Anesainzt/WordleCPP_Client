#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

using namespace std;

int menu(){
	int num;
	cout<<"****BIENVENIDO A WORDC****"<<endl;
	cout<<"1. INICIAR SESION"<<endl;
	cout<<"2. REGISTRARSE"<<endl;
	cout<<"3.Salir"<<endl;
	cout<<"Elige una opcion: ";
	cin>>num;
	return num;
}
int menuAdministrador(){
	int opcion;
	cout<<"**** MENU ADMINISTRADOR ****"<<endl;
	cout<<"1. ANIADIR PALABRA"<<endl;
	cout<<"2.BORRAR PALABRA"<<endl;
	cout<<"3.Cerrar sesion "<<endl;
	cout<<"4.Salir"<<endl;
	cout<<"Elige una opción: ";
	cin>>opcion;
	return opcion;
}
int menuCliente(){
	int opcion;
	cout<<"****BIENVENIDO, JUGADOR****"<<endl;
	cout<<"1. JUGAR"<<endl;
	cout<<"2.Ver puntuaciones"<<endl;
	cout<<"3.Cerrar sesion"<<endl;
	cout<<"4.Salir"<<endl;
	cout<<"Elige una opcion: ";
	cin>>opcion;
	return opcion;
}

void jugarWordle( /*sqlite3 * db*/ ){
	HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);

	//CARGAR PALABRAS
		
		char palabra5letras[6];
		//EMPEZAR JUEGO Y SELECCIONAR UNA PALABRA RANDOM de la BD (falta por hacer). Nota: algunas lineas están comentadas porque son relacionadas con la bd, que por ahora no está

		char respuesta[6]= "adora";// para probar, como no puedo sacar una palabra random de la BD, fingimos que la palabra a adivinar es "adora"

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
		cout<<" La palabra tiene que ser de 5 letras!"<<endl;
		
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

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	/*EMPIEZA EL PROGRAMA DEL CLIENTE*/
	int opcion,opcionA,opcionC;
	char nombre[51],con[20];
	int resul;
	do{
		opcion = menu();
		sprintf(sendBuff,"%d",opcion);
		send(s, sendBuff, sizeof(sendBuff), 0);
		switch(opcion){
		case 1: break;
			cout<<"Nombre: ";cin>>nombre;
			cout<<"Contrasena: ";cin>>con;
			sprintf(sendBuff,"%s",nombre);
			send(s, sendBuff, sizeof(sendBuff), 0); //Env�o el nombre al servidor
			sprintf(sendBuff,"%s",con);
			send(s, sendBuff, sizeof(sendBuff), 0); //Env�o la contrase�a al servidor
			recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesi�n
			sscanf(recvBuff,"%d",&resul);
			cout<<"RESULTADO: "<<resul<<endl;
			if(resul==1){
				do{
					opcionA = menuAdministrador();
					switch(opcionA){
						case '1': break;
						case '2': break;
						case '0': break;
						default: cout<<"La opci�n no es correcta"<<endl;
					}
				}while(opcionA!='0');
			}else if(resul ==2){
				do{
					opcionC = menuCliente();
					switch(opcionC){
						case '1': break;
						case '2': break;
						case '0': break;
						default: cout<<"La opci�n no es correcta"<<endl;
					}
				}while(opcionC!='0');
			}else{
				cout<<"El Inicio de Sesi�n no ha sido correcto"<<endl;
			}
			break;
		case 2: break;
		case '0': cout<<"AGUR"<<endl;break;
		default: cout<<"La opci�n seleccionada no es correcta"<<endl;
		}

	}while(opcion!='0');

	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
