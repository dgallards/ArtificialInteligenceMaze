/*
 * Posicion.h
 *
 *  Created on: 12 mar. 2019
 *      Author: diegopc
 */

#ifndef POSICION_H_
#define POSICION_H_

namespace std {

class Posicion {
	int fila;
	int columna;
public:
	Posicion();
	Posicion(int fila, int columna);
	~Posicion();
	int getColumna() const;
	void setColumna(int columna);
	int getFila() const;
	void setFila(int fila);
	bool posicionIgual(Posicion a,Posicion b);
};

} /* namespace std */

#endif /* POSICION_H_ */
