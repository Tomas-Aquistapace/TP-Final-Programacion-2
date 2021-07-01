#include"Animal.h"

Animal::Animal(int x, int y, int vidas, int visible, string archivo){
	_x=x;
	_y=y;
	_vidas=vidas;
	_visible=visible;

	ifstream fentrada;
	list<char> fila;
	char letra;
	try {
		fentrada.exceptions(ifstream::failbit | ifstream::badbit);
		fentrada.open(archivo);
		try {
			fentrada.read((char*)&letra, sizeof(letra));
			while (!fentrada.eof()) {
				if (letra != '\n') {
					fila.push_back(letra);
				}
				else {
					_imagen.push_back(fila);
					fila.clear();
				}

				fentrada.read((char*)&letra, sizeof(letra));
			}

			fentrada.close();

		}
		catch (ifstream::failure& e) {
			if (fentrada.bad()) {
				cout << "No se pudo leer el archivo - " << archivo;
			}
		}
	}
	catch (ifstream::failure& e) {
		if (fentrada.fail()) {
			cout << "Error al abrir el achivo - " << archivo << endl;

			for (int i = 0; i < 3; i++){
				for (int j = 0; j < TAM; j++){
					fila.push_back(FILAxDEFECTO[j]);
				}
				_imagen.push_back(fila);
				fila.clear();
			}
		}
	}
}
Animal::~Animal(){

}
bool Animal::estaVivo(){
	return (_vidas>0);
}
int Animal::getVidas(){
	return _vidas;
}
int Animal::getVisible(){
	return _visible;
} 
void Animal::setVidas(int vidas){
	_vidas=vidas;
}
void Animal::setVisible(int visible){
	if(_vidas>0)
		_visible=visible;
	else
		_visible=-1; // PORQUE -1? NO ENTENDEMOS
}
Matriz Animal::GetMatriz(){
	return _imagen;
}
