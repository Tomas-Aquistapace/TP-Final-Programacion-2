#include "Archivo.h"

Archivo::Archivo() {
	_archivoNombre = "Resultado.txt";
	_reg._puntajeFinal = 0;
	_reg._porcentajeDeAcierto = 0;
	_reg._cantidadPulsaciones = 0;
}
Archivo::~Archivo() {

}
void Archivo::Salvar(int puntajeFinal, float porcentajeDeAcierto, int cantidadPulsaciones) {
	_reg._puntajeFinal = 12;
	_reg._porcentajeDeAcierto = 50;
	_reg._cantidadPulsaciones = 100;
	try {
		_fsalida.exceptions(ofstream::failbit | ofstream::badbit);
		_fsalida.open(_archivoNombre);

		try {
			//_fsalida.write((char*)&_reg._puntajeFinal, sizeof(char));
			//_fsalida.write((char*)&_reg._porcentajeDeAcierto, sizeof(char));
			//_fsalida.write((char*)&_reg._cantidadPulsaciones, sizeof(char));
			_fsalida.write((char*)&_reg, sizeof(Registro));

			_fsalida.close();
		}
		catch (ofstream::failure& e) {
			if(_fsalida.bad()) {
				cout << "error al grabar el archivo "<< _archivoNombre << " " << e.what();
			}
		}
	}
	catch (ofstream::failure& e  ) {
		if (_fsalida.fail()) {
			cout << "no se puede abrir el archivo "<< _archivoNombre<<" " << e.what();
		}
	}
}