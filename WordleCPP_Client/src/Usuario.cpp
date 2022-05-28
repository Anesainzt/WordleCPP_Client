#include "Usuario.h"
#include <iostream>
#include <string.h>

using namespace std;
Usuario::Usuario(){

	this->numUsuario= 0;
	this->nombre = NULL;
	this->contrasena = NULL;
	//Constructor por defecto
}
Usuario::Usuario(const char* nombre, const char* contrasena, int numUsuario){
	this->nombre= new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
	this->contrasena= new char[strlen(contrasena)+1];
	strcpy(this->contrasena, contrasena);
	this->numUsuario= numUsuario;
}

Usuario::~Usuario(){
	delete []this->nombre;
	delete []this->contrasena;
}

void Usuario::setNombre(const char* nombre){
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
}
char* Usuario::getNombre() const{
	return this->nombre;
}

void Usuario::setcontrasena(const char* contrasena){
	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena, contrasena);
}
char* Usuario::getcontrasena() const{
	return this->contrasena;
}

void Usuario::setnumUsuario(int numUsuario){
	this->numUsuario=numUsuario;
}
int Usuario::getnumUsuario() const{
	return this->numUsuario;
}
void Usuario::imprimirInfo(){
	cout<<"Nombre: "<<this->nombre<<endl;
}
