/*
 * ficha.cpp
 *
 *  Created on: 4 mar. 2019
 *      Author: diegopc
 */

#include "Ficha.h"


Ficha::Ficha() {
	valor=-1;
	usado=false;
	distanciaAPadre=-1;
	// TODO Auto-generated constructor stub

}
Ficha::Ficha(int valor) {
	this->valor=valor;
	usado=false;
	distanciaAPadre=-1;
	// TODO Auto-generated constructor stub

}


bool Ficha::isUsado() const {
	return usado;
}

void Ficha::setUsado(bool usado) {
	this->usado = usado;
}

int Ficha::getValor() const {
	return valor;
}

void Ficha::setValor(int valor) {
	this->valor = valor;
}

void Ficha::show() {
	if(this->isUsado()){
		cout<<"*";
	}
	else{
		if(this->getValor()==999){
			cout<<"#";
		}else{
		cout<<this->getValor();
		}
	}
}

int Ficha::getDistanciaAPadre() const {
	return distanciaAPadre;
}

void Ficha::setDistanciaAPadre(int distanciaAPadre) {
	this->distanciaAPadre = distanciaAPadre;
}



Ficha::~Ficha() {
	// TODO Auto-generated destructor stub
}


