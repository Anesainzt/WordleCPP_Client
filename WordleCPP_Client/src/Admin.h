#ifndef ADMIN_H_
#define ADMIN_H_

class Admin{
private:
	char* nombre;
	char* contrasena;
	int numAdmin;

public:
	Admin();
	Admin(const char* nombre, const char* contrasena, int numAdmin);
	~Admin();
	void setNombre(const char* nombre);
	char* getNombre() const;
	void setcontrasena(const char* contrasena);
	char* getcontrasena() const;
	void setnumAdmin(int numAdmin);
	int getnumAdmin() const;
	void imprimirInfo();
};



#endif /* ADMIN_H_ */
