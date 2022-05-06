/*
 * Tablero.cpp
 *
 *  Created on: 4 mar. 2019
 *      Author: diegopc
 */

#include "Tablero.h"
#include <cmath>

using namespace std;

// PARTE PRIVADA
void Tablero::cargarTablero(string laberinto) {

}

Posicion Tablero::encuentraObjetivo() {
	int i = 0, j;
	Posicion objetivo;
	bool bandera = false;
	while (!bandera && i < MAX) {
		while (!bandera && j < MAX) {

			if (tablero[i][j]->getValor() == 0) {
				bandera = true;
				objetivo = Posicion(i, j);

			}

			j++;
		}
		j = 0;
		i++;
	}
	return objetivo;
}

//PARTE PUBLICA

Tablero::Tablero() {
	this->usuario = Posicion(0, 0);
	this->umbral = 0;
	this->contador = 0;
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			this->tablero[i][j] = new Ficha();
		}
	}
	this->objetivo = encuentraObjetivo();

}

Tablero::Tablero(int n) {
	//Tablero();
	this->usuario = Posicion(0, 0);
	this->contador = 0;

	if (n > 0 && n < 16) {

		ifstream fEnt;
		string umbral, num1, num2, num3, num4, num5, num6, num7, num8, num9,
				num10;
		int i, j;
		i = 0;
		j = 0;
		fEnt.open("laberinto" + to_string(n) + ".txt");
		if (fEnt.is_open()) {
			getline(fEnt, umbral);
			this->umbral = atoi(umbral.c_str());

			while (!fEnt.eof() || (j < 10 && i < 10)) {
				getline(fEnt, num1, ',');
				if (!fEnt.eof()) {
					tablero[i][j] = new Ficha(atoi(num1.c_str()));
					j++;

					getline(fEnt, num2, ',');
					tablero[i][j] = new Ficha(atoi(num2.c_str()));
					j++;

					getline(fEnt, num3, ',');
					tablero[i][j] = new Ficha(atoi(num3.c_str()));
					j++;

					getline(fEnt, num4, ',');
					tablero[i][j] = new Ficha(atoi(num4.c_str()));
					j++;

					getline(fEnt, num5, ',');
					tablero[i][j] = new Ficha(atoi(num5.c_str()));
					j++;

					getline(fEnt, num6, ',');
					tablero[i][j] = new Ficha(atoi(num6.c_str()));
					j++;

					getline(fEnt, num7, ',');
					tablero[i][j] = new Ficha(atoi(num7.c_str()));
					j++;

					getline(fEnt, num8, ',');
					tablero[i][j] = new Ficha(atoi(num8.c_str()));
					j++;

					getline(fEnt, num9, ',');
					tablero[i][j] = new Ficha(atoi(num9.c_str()));
					j++;

					getline(fEnt, num10);
					tablero[i][j] = new Ficha(atoi(num10.c_str()));
					j = 0;
					i++;
				}
			}
		}

		this->objetivo = encuentraObjetivo();
	} else {
		umbral = -1;
		cout << "error" << endl;
	}

}

void Tablero::TableroAleat(){
	srand (time(NULL));
	this->usuario = Posicion(0, 0);
		this->umbral = rand() % 50;
		this->contador = 0;
		for (int i = 0; i < MAX; ++i) {
			for (int j = 0; j < MAX; ++j) {
				this->tablero[i][j] = new Ficha( (rand() % 9) +1 );
			}
		}

		this->tablero[rand() % 10][rand() % 10]->setValor(0);



		this->objetivo = encuentraObjetivo();
}

int Tablero::getValorFicha(int x, int y) {
	return tablero[x][y]->getValor();
}

bool Tablero::isUsadoFicha(int x, int y) {
	return tablero[x][y]->isUsado();
}

void Tablero::usaFicha(int x, int y) {
	tablero[x][y]->setUsado(true);
	contador += tablero[x][y]->getValor();

}

int Tablero::getUmbral() const {
	return umbral;
}

void Tablero::setUmbral(int umbral) {
	this->umbral = umbral;
}

int Tablero::distanciaAObjetivo() {
	int a, b;
	a = abs(usuario.getColumna() - objetivo.getColumna());
	b = abs(usuario.getFila() - objetivo.getFila());
	return a + b;
	//return max(a,b);
}

void Tablero::mostrarTablero() {

	cout << "umbral: " << this->umbral << endl;
	for (int i = 0; i < MAX; ++i) {
		cout << "-----------------------" << endl;
		for (int j = 0; j < MAX; ++j) {
			tablero[i][j]->show();
			cout << "|";
		}
		cout << endl;

	}
}

int Tablero::getCol() {
	return usuario.getColumna();
}

int Tablero::getFil() {
	return usuario.getFila();
}

int Tablero::izq() {
	Posicion aux;
	aux = this->usuario;
	int a, b;
	if (this->getCol() > 0) {
		aux.setColumna(this->getCol() - 1);
		a = abs(aux.getColumna() - objetivo.getColumna());
		b = abs(aux.getFila() - objetivo.getFila());
		return a + b;
	} else {
		return 666;
	}
}

int Tablero::der() {
	Posicion aux;
	aux = this->usuario;
	int a, b;
	if (this->getCol() < 9) {
		aux.setColumna(this->getCol() + 1);
		a = abs(aux.getColumna() - objetivo.getColumna());
		b = abs(aux.getFila() - objetivo.getFila());
		return a + b;
	} else {
		return 666;
	}
}

int Tablero::arr() {
	Posicion aux;
	aux = this->usuario;
	int a, b;
	if (this->getFil() > 0) {
		aux.setFila(this->getFil() - 1);
		a = abs(aux.getColumna() - objetivo.getColumna());
		b = abs(aux.getFila() - objetivo.getFila());
		return a + b;
	} else {
		return 666;
	}
}

int Tablero::abj() {
	Posicion aux;
	aux = this->usuario;
	int a, b;
	if (this->getFil() < 9) {
		aux.setFila(this->getFil() + 1);
		a = abs(aux.getColumna() - objetivo.getColumna());
		b = abs(aux.getFila() - objetivo.getFila());
		return a + b;
	} else {
		return 666;
	}
}

int Tablero::getContador() const {
	return this->contador;
}


Tablero::~Tablero() {
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			delete this->tablero[i][j];
		}
	}
}

void Tablero::moverIzq() {
	usuario.setColumna(usuario.getColumna() - 1);
	this->usaFicha(usuario.getFila(), usuario.getColumna());
}

void Tablero::moverDer() {
	usuario.setColumna(usuario.getColumna() + 1);
	this->usaFicha(usuario.getFila(), usuario.getColumna());
}

void Tablero::moverArr() {
	usuario.setFila(usuario.getFila() - 1);
	this->usaFicha(usuario.getFila(), usuario.getColumna());
}

void Tablero::moverAbj() {
	usuario.setFila(usuario.getFila() + 1);
	this->usaFicha(usuario.getFila(), usuario.getColumna());
}

int Tablero::valorIzq() {
	if (this->getCol() > 0
			&& !this->isUsadoFicha(this->getFil(), this->getCol() - 1)) {
		return this->getValorFicha(this->getFil(), this->getCol() - 1);
	} else {
		return 666;
	}
}

int Tablero::valorDer() {
	if (this->getCol() < 9
			&& !this->isUsadoFicha(this->getFil(), this->getCol() + 1)) {
		return this->getValorFicha(this->getFil(), this->getCol() + 1);
	} else {
		return 666;
	}
}

int Tablero::valorArr() {
	if (this->getFil() > 0
			&& !this->isUsadoFicha(this->getFil() - 1, this->getCol())) {
		return this->getValorFicha(this->getFil() - 1, this->getCol());
	} else {
		return 666;
	}
}

int Tablero::valorAbj() {
	if (this->getFil() < 9
			&& !this->isUsadoFicha(this->getFil() + 1, this->getCol())) {

		return this->getValorFicha(this->getFil() + 1, this->getCol());
	} else {
		return 666;
	}
}

int Tablero::distanciaAObjetivo(int x, int y) {
	int a, b;
	Posicion usuario = Posicion(x, y);

	a = abs(usuario.getColumna() - objetivo.getColumna());
	b = abs(usuario.getFila() - objetivo.getFila());
	//return max(a, b);
	return a + b;

}
