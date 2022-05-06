/*
 * Posicion.cpp
 *
 *  Created on: 12 mar. 2019
 *      Author: diegopc
 */

#include "Posicion.h"

namespace std {

Posicion::Posicion() {
	columna = 0;
	fila = 0;

}

Posicion::Posicion(int fila, int columna) {
	this->columna = columna;
	this->fila = fila;
}
int Posicion::getColumna() const {
	return columna;
}

void Posicion::setColumna(int columna) {
	this->columna = columna;
}

int Posicion::getFila() const {
	return fila;
}

void Posicion::setFila(int fila) {
	this->fila = fila;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

bool Posicion::posicionIgual(Posicion a, Posicion b) {
	return(a.getColumna()==b.getColumna()&&a.getFila()==b.getFila());
}

} /* namespace std */
