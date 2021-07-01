#include "Archivo.h"

Archivo::Archivo() {
	_archivoNombre = "Resultado.log";
	_reg._aciertos = 0;
	_reg._porcentajeDeAcierto = 9999;
	_reg._cantidadPulsaciones = 0;
	_reg._tiempoTotal = 0;
}
Archivo::~Archivo() {

}
void Archivo::Salvar(int aciertos, int cantidadPulsaciones, float tiempoTotal) {
	
	_reg._aciertos = aciertos;
	_reg._porcentajeDeAcierto = (aciertos * 100 )/ cantidadPulsaciones;
	_reg._cantidadPulsaciones = cantidadPulsaciones;
	_reg._tiempoTotal = tiempoTotal;
	_fsalida.exceptions(ofstream::failbit | ofstream::badbit);
	try {
		_fsalida.open(_archivoNombre);
		try {
			//_fsalida.write((char*)&_reg._puntajeFinal, sizeof(char));
			//_fsalida.write((char*)&_reg._porcentajeDeAcierto, sizeof(char));
			//_fsalida.write((char*)&_reg._cantidadPulsaciones, sizeof(char));
			_fsalida.write((char*)&_reg, sizeof(Registro));
			_fsalida << _reg._aciertos << endl;
			_fsalida << _reg._porcentajeDeAcierto << endl;
			_fsalida << _reg._cantidadPulsaciones << endl;
			_fsalida << _reg._tiempoTotal << endl;
			try {
				_fsalida.close();

				ifstream _fentrada;
				_fentrada.exceptions(ofstream::failbit | ofstream::badbit);
				try {
					_fentrada.open(_archivoNombre);
					try {
						_fentrada.read((char*)&_reg, sizeof(Registro));
						cout << endl; cout << "aciertos " << _reg._aciertos << " pulsaciones " << _reg._cantidadPulsaciones <<
							"  porcentaje " << _reg._porcentajeDeAcierto << " tiempoTotal " << _reg._tiempoTotal;
						try {
							_fentrada.close();
						}
						catch (ofstream::failure& e) {
							if (_fsalida.fail()) {
								cout << "error al cerrar el archivo " << _archivoNombre << " " << e.what();
							}
						}
					}
					catch (ofstream::failure& e) {
						if (_fsalida.bad()) {
							cout << "error al leer el archivo " << _archivoNombre << " " << e.what();
						}
					}
				}
				catch (ofstream::failure& e) {
					if (_fentrada.fail()) {
						cout << "no se puede abrir el archivo " << _archivoNombre << " " << e.what();
					}
				}
			}
			catch (ofstream::failure& e) {
				if (_fsalida.fail()) {
					cout << "error al cerrar el archivo " << _archivoNombre << " " << e.what();
				}
			}
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