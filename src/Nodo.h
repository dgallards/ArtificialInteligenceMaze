/*
 * Nodo.h
 *
 *  Created on: 4 abr. 2019
 *      Author: diegopc
 */

#ifndef NODO_H_
#define NODO_H_
#include "Posicion.h"

using namespace std;

class Nodo {

	Nodo *padre;
	Posicion pos;
	int acum, dist, coste, valor; //acum=g(n), dist= h(n), coste= coste del nodo, valor=acum+dist+coste

public:
	Nodo();

	Nodo(int acum, int dist, int coste, Nodo *&padre, int x, int y);
	void actualizarPadre(Nodo *padre);
	const Posicion& getPos() const;
	int getAcum() const;
	void setAcum(int acum);
	int getDist() const;
	void setDist(int dist);
	int getValor() const;
	void setValor(int valor);
	void setPos(const Posicion& pos);
	int getCoste() const;
	void setCoste(int coste);

	~Nodo();
	void getPadre(Nodo *&abuelo);
};

#endif /* NODO_H_ */
