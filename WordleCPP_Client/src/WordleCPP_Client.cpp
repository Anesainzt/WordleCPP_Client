#include <stdio.h>
#include <winsock2.h>
#include <iostream>
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
	cout<<"Elige una opcion: ";
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
	int opcion,opcionA,opcionC,a,b,c;
	char nombre[51],con[20],usuarioNuevo[51],contraseniaNueva[20], palabraNueva[6], tematica[20], borrarPalabra[6];
	int resul,resulRegistro, resulPalabra, resulPalabraBorrada;
	do{
		opcion = menu();
		sprintf(sendBuff,"%d",opcion);
		send(s, sendBuff, sizeof(sendBuff), 0);   //Funcion para mandar el numero al server
		switch(opcion){
		case 1:
			cout<<"Nombre: ";
			cin>>nombre;
			cout<<"Contrasena: ";
			cin>>con;
			sprintf(sendBuff,"%s",nombre);
			send(s, sendBuff, sizeof(sendBuff), 0); //Envia el nombre al servidor
			sprintf(sendBuff,"%s",con);
			send(s, sendBuff, sizeof(sendBuff), 0); //Envia la contrasenia al servidor
			recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
			sscanf(recvBuff,"%d",&resul);
			cout<<"RESULTADO: "<<resul<<endl;
			if(resul==1){
				do{
					opcionA = menuAdministrador();
					switch(opcionA){
						case 1:
							//AÑADIR LA PALABRA EN LA BD CON LA TEMÁTICA
							a = 1;
							sprintf(sendBuff,"%d",a);
							send(s, sendBuff, sizeof(sendBuff), 0);//Envia la opcion seleccionada
							cout<<"PALABRA: ";cin>>palabraNueva;
							cout<<"TEMÁTICA: ";cin>>tematica;
							sprintf(sendBuff,"%s",palabraNueva);
							send(s, sendBuff, sizeof(sendBuff), 0);//Envia la palabra al servidor
							sprintf(sendBuff,"%s",tematica);
							send(s, sendBuff, sizeof(sendBuff), 0);//Envia la temática al servidor
							//ESPERA RESPUESTA
							recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del insertar la palabra
							sscanf(recvBuff,"%d",&resulPalabra);
							if(resulPalabra==0){
								cout<<"Añadida correctamente"<<endl;

							}else{
								cout<<"No Se ha podido añadir"<<endl;
							}
							WSACleanup();
							break;
							//AÑADIR LA PALABRA EN LA BD CON LA TEMÁTICA
						case 2: //BORRAR UNA PALABRA DE LA BBDD
							b=2;
							sprintf(sendBuff,"%d",b);
							send(s, sendBuff, sizeof(sendBuff), 0);//Envia la opcion seleccionada
							cout<<"PALABRA QUE SE QUIERE BORRAR: ";cin>>borrarPalabra;

							sprintf(sendBuff,"%s",borrarPalabra);
							send(s, sendBuff, sizeof(sendBuff), 0);//Envia la palabra al servidor
							//ESPERA AL SERVIDOR
							recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado de borrar la palabra
							sscanf(recvBuff,"%d",&resulPalabraBorrada);//0 si se ha borrado correctamente
							if(resulPalabraBorrada==0){
								cout<<"Pablabra borrada correctamente"<<endl;
							}else{
								cout<<"No Se ha podido borrar"<<endl;
							}
							WSACleanup();
							break;
						case 3:
							closesocket(s);
							WSACleanup();
							menu();
							break; //CERRAR SESIÓN
						case 4:
							cout<<"AGUR"<<endl;
							closesocket(s);
							WSACleanup();
							break;
						default: cout<<"La opcion no es correcta"<<endl;
					}
				}while(opcionA!=0);
			}else if(resul ==2){
				do{
					opcionC = menuCliente();
					switch(opcionC){
						case 1: break; //JUGAR
						case 2://VER PUNTUACIONES
						break;
						case 3:
							menu();
							break; //CERRAR SESIÓN
						case 4:
							cout<<"AGUR"<<endl;
							closesocket(s);
							WSACleanup();
							break;
						default: cout<<"La opcion no es correcta"<<endl;
					}
				}while(opcionC!=0);
			}else{
				cout<<"El Inicio de Sesion no ha sido correcto"<<endl;
			}
			break;
		case 2:
			cout<<"\n****REGISTRAR NUEVO USUARIO****\n "<<endl;
			cout<<"USUARIO: ";cin>>usuarioNuevo;
			cout<<"CONTRASENIA: ";cin>>contraseniaNueva;
			sprintf(sendBuff,"%s",usuarioNuevo);
			send(s, sendBuff, sizeof(sendBuff), 0);//Envia el nombre de Usuaio al servidor
			sprintf(sendBuff,"%s",contraseniaNueva);
			send(s, sendBuff, sizeof(sendBuff), 0);//Envia la contrase�a nueva al servidor
			recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del registro
			sscanf(recvBuff,"%d",&resulRegistro);			//1 si esta todo bien 0 si ya existe
			cout<<"RESULTADO: "<<resulRegistro<<endl;
			if(resulRegistro==1){
				cout<<"Registrado correctamente"<<endl;
			}else{
				cout<<"El usuario ya se encuentra registrado"<<endl;
			}
			break;
		case 3: cout<<"AGUR"<<endl;break;
		default: cout<<"La opcion seleccionada no es correcta"<<endl;
		}

	}while(opcion == 3);

	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
