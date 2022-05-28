#ifndef USUARIO_H_
#define USUARIO_H_

class Usuario {
    private:
	char* nombre;
	char* contrasena;
	int numUsuario;
public:
	Usuario();
	Usuario(const char* nombre, const char* contrasena, int numUsuario);
	~Usuario();
	void setNombre(const char* nombre);
	char* getNombre() const;
	void setcontrasena(const char* contrasena);
	char* getcontrasena() const;
	void setnumUsuario(int numUsuario);
	int getnumUsuario() const;
	void imprimirInfo();
};

#endif /* USUARIO_H_ */