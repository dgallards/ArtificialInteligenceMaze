/*
 * Tablero.h
 *
 *  Created on: 4 mar. 2019
 *      Author: diegopc
 */

#ifndef TABLERO_H_
#define TABLERO_H_
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Ficha.h"
#include "Posicion.h"

using namespace std;

const int MAX = 10;

class Tablero {

	Ficha *tablero[MAX][MAX];
	int umbral, contador;

	Posicion objetivo, usuario;

	void cargarTablero(string laberinto);
	Posicion encuentraObjetivo();

public:
	Tablero();
	Tablero(int n);
	void TableroAleat();

	int getContador() const;
	int getUmbral() const;
	void setUmbral(int umbral);
	int getValorFicha(int x, int y);
	bool isUsadoFicha(int x, int y);
	void usaFicha(int x, int y);

	int getCol();
	int getFil();
	void moverIzq();
	void moverDer();
	void moverArr();
	void moverAbj();
	int izq();
	int der();
	int arr();
	int abj();
	int valorIzq();
	int valorDer();
	int valorArr();
	int valorAbj();

	int distanciaAObjetivo();

	int distanciaAObjetivo(int x,int y);

	void mostrarTablero();

	~Tablero();

};

#endif /* TABLERO_H_ */
