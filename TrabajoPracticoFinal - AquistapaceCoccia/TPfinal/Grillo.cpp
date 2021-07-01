#include "Grillo.h"

Grillo::Grillo(int x, int y,int vidas,int visible, string archivo, int clase):Animal(x,y,vidas,visible,archivo){
	_clase=clase;
}
char Grillo::getTipo(){
	return 'G';
}
void Grillo::Atacar(Animal* per){
int danio=0;
	if(per->estaVivo()){
		danio=per->getVidas()-2;
		if(danio<0)danio=0;
		per->setVidas(danio);
	}
}
void Grillo::borrar(){
	gotoxy(_x,_y);  cout<<"           ";
	gotoxy(_x,_y+1);cout<<"           ";
	gotoxy(_x,_y+2);cout<<"           ";
	gotoxy(_x,_y+4);cout<<"           ";
}
void Grillo::dibujar(){
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

	gotoxy(_x, _y + 4); cout << "[ " << _clase << " ]";
}