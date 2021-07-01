#include "Rana.h"

Rana::Rana(int x, int y,int vidas,int visible, string archivo, int salto):Animal(x,y,vidas,visible,archivo){
	_salto=salto;
}
char Rana::getTipo(){
	return 'R';
}
void Rana::Atacar(Animal* per){
int danio=0;
	if(per->estaVivo()){
		if(per->getTipo()=='H')	danio=1;
		if(per->getTipo()=='G')	danio=2;
		danio=per->getVidas()-danio;
		if(danio<0)danio=0;
		per->setVidas(danio);
	}
}
void Rana::setSalto(int salto){
	_salto=salto;
}
int Rana::getSalto(){
	return _salto;
}
void Rana::borrar(){
	gotoxy(_x,_y);	cout<<"         ";
	gotoxy(_x,_y+1);cout<<"         ";
	gotoxy(_x,_y+2);cout<<"         ";
	gotoxy(_x,_y+3);cout<<"         ";
}
void Rana::dibujar(){
	Matriz mat = GetMatriz();
	int cantMatriz = mat.size();

	list<char> fila = mat.front();

	for (int i = 0; i < cantMatriz; i++) {
		fila.clear();
		fila = mat.front();
		mat.pop_front();
		
		gotoxy(_x, _y + i);
		while (!fila.empty()) {
			cout << fila.front();
			fila.pop_front();
		}
	}
}