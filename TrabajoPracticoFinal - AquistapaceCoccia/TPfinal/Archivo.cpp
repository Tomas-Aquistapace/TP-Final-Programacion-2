#include "Archivo.h"

Archivo::Archivo() {
	_archivoNombre = "Resultado.txt";
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

			_fsalida.close();

			ifstream fentrada; 
			fentrada.open(_archivoNombre);
			fentrada.read((char*)&_reg, sizeof(Registro));
			cout<<endl; cout << "aciertos " << _reg._aciertos << " pulsaciones " << _reg._cantidadPulsaciones <<
				"  porcentaje " << _reg._porcentajeDeAcierto << "  tiempoTotal " << _reg._tiempoTotal;
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