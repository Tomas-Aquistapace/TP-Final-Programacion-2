#include "Juego.h"

time_t initial_time;
time_t bicho_time;

Juego::Juego(){
	_arch = new Archivo(); 
	_lista.clear();
	_depredador= NULL;
}

Juego::~Juego(){
	list<Animal*>::iterator iter;
	for ( iter = _lista.begin(); iter != _lista.end(); iter++) {
		if (*iter != NULL) {
			delete *iter;
		}
	}
	_lista.clear();

	if(_depredador!=NULL)
		delete _depredador;
	if (_arch != NULL)
		delete _arch;
}

void Juego::init(){
	_tecla=' ';
	_gameOver=false;
	srand(time(0));
	_vivos=0;
	_presa=0;
	_tiempo=TIEMPOMAX;
	_intentos= 0;
	_ultimo=0;
	_visibles=0;
	_dificultad=0;

	_tiempoPerdido = 0;

	_vecesPulsadas = 0;
	_aciertos = 0;
	_tiempoTotal = 0;

	int top=1;
	int max = 0;
	int h = 0;
	int g = 0;

	gotoxy(10,3);
	while(_dificultad<1||_dificultad>3){
		cout<<"ingrese dificultad:\n\t\t1:principiante\n\t\t2:intermedio\n\t\t3:avanzado\n\t\t";
		cin>>_dificultad;
	}
	_depredador=new Rana(60, 3, VIDAS_R, 1, Direccion_Rana, 1);

	switch(_dificultad){
		case 1:
			_tiempoPerdido = 1;
			max = NIVEL_A;
			for(int i= 0; i<max; i++){
				_lista.push_back(new Hormiga((top++)*7, 12, VIDAS_H, 0, Direccion_Hormiga, i));
				_vivos++;
			}
			break;
		case 2:
			_tiempoPerdido = 1.5f;
			max = NIVEL_B;
			h = 4;
			g = 3;
			for(int i= 0; i<max; i++){

				int ran=rand()%(2);
				if(ran==0){
					if(h>0){
						_lista.push_back(new Hormiga((top++)*7, 12, VIDAS_H, 0, Direccion_Hormiga, i));
						h--;
					}else{
						_lista.push_back(new Grillo((top++)*7, 12, VIDAS_G, 0, Direccion_Grillo, i));
						g--;
					}
				}else if(ran==1){
					if(g>0){
						_lista.push_back(new Grillo((top++)*7, 12, VIDAS_G, 0, Direccion_Grillo, i));
						g--;
					}else{
						_lista.push_back(new Hormiga((top++)*7, 12, VIDAS_H, 0, Direccion_Hormiga, i));
						h--;
					}
				}
				_vivos++;

			}
			break;
		case 3:
			_tiempoPerdido = 2;
			max = NIVEL_C;
			h = 1+rand()%(9-1);
			g = 10 - h;
			for(int i= 0; i<max; i++){

					int ran=rand()%(2);
					if(ran==0){
						if(h>0){
							_lista.push_back(new Hormiga((top++)*7, 12, VIDAS_H, 0, Direccion_Hormiga, i));
							h--;
						}else{
							_lista.push_back(new Grillo((top++)*7, 12, VIDAS_G, 0, Direccion_Grillo, i));
							g--;
						}
					}else if(ran==1){
						if(g>0){
							_lista.push_back(new Grillo((top++)*7, 12, VIDAS_G, 0, Direccion_Grillo, i));
							g--;
						}else{
							_lista.push_back(new Hormiga((top++)*7, 12, VIDAS_H, 0, Direccion_Hormiga, i));
							h--;
						}
					}
					_vivos++;

			}
			break;
	}
	initial_time = time(NULL);
	clrscr();
}

void Juego::play(){
	init();
	hideCursor();
	marco(1,2,80,24);
	draw();
	while(!gameOver()){
		input();
		update();
		draw();
		miliSleep(200);
	}
	result();
}

void Juego::update(){
int hor=rand()%(_lista.size());
list<Animal*>::iterator iterVisible = _lista.begin();
	
	for (int i = 0; i < hor; i++) {
		iterVisible++;
	}

	static time_t lastTime = initial_time;
    time_t deltaTime;
    deltaTime = time(NULL) - lastTime;
    _tiempo -= deltaTime;
	_tiempoTotal += deltaTime;
    bicho_time += deltaTime;
	lastTime += deltaTime;

	if(bicho_time>=2){
		Animal* insecto = *iterVisible;
		if(insecto != NULL && insecto->getVisible()==0){
			insecto->setVisible(1);
			_visibles++;
			bicho_time = 0;
			_ultimo=hor;
		}
	}

	if (_presa <= TOPE) {

		list<Animal*>::iterator iterPresa = _lista.begin();
		for (int i = 0; i < _presa; i++) {
			iterPresa++;
		}
		Animal* presa = *iterPresa;

		if (presa != NULL) {
			if (presa->estaVivo() == true && presa->getVisible() == 1) {
				_aciertos++;
				if (_presa == _ultimo) {
					_depredador->Atacar(presa);
					presa->borrar();
				}
				if (presa->estaVivo() == false) {
					_vivos--;
				}
				presa->setVisible(0);
				_visibles--;
				if (_intentos > 0) {
					_intentos--;
				}
			}
			else if (presa->getVisible() == false || presa->estaVivo() == false) {
				_intentos++;
			}
		}
		if (_intentos == INTENTOS) {
			_tiempo = (_tiempo - _tiempoPerdido);
			_intentos = 0;
		}
		if (_tiempo < 0) {
			_tiempo = 0;
		}
	}
}

void Juego::result(){
	gotoxy(10,22);
	if(_gameOver){
		if(_vivos>0)
			cout<<"Perdiste !";
		else
			cout<<"Ganaste !";
		gotoxy(30,25);
		cout<<"game over  ";
		
		_arch->Salvar(_aciertos, _vecesPulsadas, _tiempoTotal);

		cin.get();
	}
}

void Juego::input(){
	if(_tecla=getKey(false)){
		if (_tecla > 47 && _tecla < 58)
		{
			_presa=_tecla-48;
			_vecesPulsadas++;
		}
		if(_tecla==KEY_ESC)
			_gameOver=true;
	}else
		_presa=32;
}

bool Juego::gameOver(){
	if(_vivos<=0||(_visibles>=_vivos && _vivos>1)||_tiempo<=0)
		_gameOver=true;

	return _gameOver;
}

void Juego::draw() {
list<Animal*>::iterator iterDibj = _lista.begin();
	_depredador->dibujar();
	for(int i=0;i<_lista.size();i++) {
		Animal* insecto = *iterDibj;

		if(insecto != NULL) {
			if(insecto->estaVivo() && insecto->getVisible()==1){
				insecto->dibujar();
			}
		}

		iterDibj++;
	}

	gotoxy(10,1);cout<<"Tiempo "<<_tiempo<<" ";

	gotoxy(25,1);cout<<"Visibles "<<_visibles;

	gotoxy(42,1);cout<<"Quedan "<<_vivos<<" Animales";

	gotoxy(65,1);cout<<"INTENTOS "<<_intentos;

	gotoxy(10,5);cout<<"COMELO! "<<_ultimo;
}