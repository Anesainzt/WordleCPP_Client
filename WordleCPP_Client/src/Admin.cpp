#include <iostream>
#include <string.h>
#include "Admin.h"
using namespace std;
Admin::Admin(){

	this->numAdmin= 0;
	this->nombre = NULL;
	this->contrasena = NULL;
	//Constructor por defecto
}
Admin::Admin(const char* nombre, const char* contrasena, int numAdmin){
	this->nombre= new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
	this->contrasena= new char[strlen(contrasena)+1];
	strcpy(this->contrasena, contrasena);
	this->numAdmin= numAdmin;
}

Admin::~Admin(){
	delete []this->nombre;
	delete []this->contrasena;
}

void Admin::setNombre(const char* nombre){
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
}
char* Admin::getNombre() const{
	return this->nombre;
}

void Admin::setcontrasena(const char* contrasena){
	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena, contrasena);
}
char* Admin::getcontrasena() const{
	return this->contrasena;
}

void Admin::setnumAdmin(int numAdmin){
	this->numAdmin=numAdmin;
}
int Admin::getnumAdmin() const{
	return this->numAdmin;
}
void Admin::imprimirInfo(){
	cout<<"Nombre: "<<this->nombre<<endl;
}
