/*
 * ficha.h
 *
 *  Created on: 4 mar. 2019
 *      Author: diegopc
 */

#ifndef FICHA_H_
#define FICHA_H_
#include <iostream>

using namespace std;

class Ficha {
	int valor;
	bool usado;

	int distanciaAPadre; //Una ficha debe saber su padre y poder cambiarlo.
						 //una ficha tambien debe saber cuanta gasolina lleva usada
public:
	Ficha();
	Ficha(int valor);
	bool isUsado() const;
	void setUsado(bool usado);
	int getValor() const;
	void setValor(int valor);
	void show();
	~Ficha();

	int getDistanciaAPadre() const;
	void setDistanciaAPadre(int distanciaAPadre);

};

#endif /* FICHA_H_ */
