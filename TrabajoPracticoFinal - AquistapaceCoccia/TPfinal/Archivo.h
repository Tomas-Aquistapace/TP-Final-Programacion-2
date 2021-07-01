#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>

using namespace std;
struct Registro{
	int _aciertos;
	float _porcentajeDeAcierto;
	int _cantidadPulsaciones;
	float _tiempoTotal;
};

class Archivo{
private:
	string _archivoNombre;
	Registro _reg;
	ofstream _fsalida;
public:
	Archivo();
	~Archivo();
	void Salvar(int aciertos, int cantidadPulsaciones, float tiempoTotal);
};
#endif 


