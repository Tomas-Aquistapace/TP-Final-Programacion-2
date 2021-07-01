#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <list>
#include <fstream>
#include "libreria.h"
using namespace std;

#define VIDAS_R 1
#define VIDAS_H 3
#define VIDAS_G 7

typedef list<list<char>> Matriz;

class Animal{
protected:
	int _x;
	int _y;	
	int _vidas;
	int _visible;
	Matriz _imagen;
public:
	Animal(int x, int y, int vidas, int visible, string archivo);
	virtual ~Animal();
	virtual void Atacar(Animal* per)=0;
	virtual char getTipo()=0;
	virtual void dibujar()=0;
	virtual void borrar()=0;
	bool estaVivo();
	int getVidas();
	int getVisible();
	void setVidas(int vidas);
	void setVisible(int visible);
	Matriz GetMatriz();
};
#endif
