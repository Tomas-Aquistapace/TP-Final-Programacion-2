#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>

using namespace std;
struct Registro{
	int _puntajeFinal;
	float _porcentajeDeAcierto;
	int _cantidadPulsaciones;
};
class Archivo{

private:
	string _archivoNombre;
	Registro _reg;
	ofstream _fsalida;

public:
	
	Archivo();
	~Archivo();
	void Salvar(int puntajeFinal, float porcentajeDeAcierto, int cantidadPulsaciones);
};
#endif 


