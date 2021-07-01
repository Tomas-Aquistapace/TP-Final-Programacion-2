#ifndef GRILLO_H
#define GRILLO_H

#include <iostream>
#include "Animal.h"
using namespace std;

class Grillo:public Animal{
	int _clase;
public:
	Grillo(int x,int y,int vidas,int visible, string archivo, int clase);
	char getTipo();
	void Atacar(Animal* per);
	void dibujar();
	void borrar();
};

#endif
