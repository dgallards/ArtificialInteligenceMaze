/*
 * Nodo.cpp
 *
 *  Created on: 4 abr. 2019
 *      Author: diegopc
 */

#include "Nodo.h"
#include <iostream>

using namespace std;

Nodo::Nodo() {
	this->dist = -1;
	this->coste = -1;
	this->acum = -1;
	this->padre = new Nodo();
	this->valor = -1;
	this->pos = Posicion();
}

Nodo::Nodo(int acum, int dist,int coste, Nodo *&padre,int x, int y) {
	this->dist=dist;
	this->coste=coste;
	this->acum=acum;
	this->padre=padre;
	this->valor=acum+dist+coste;
	this->pos=Posicion(x,y);
}


int Nodo::getValor() const {
	return valor;
}

void Nodo::setValor(int valor) {
	this->valor = valor;
}

const Posicion& Nodo::getPos() const {
	return pos;
}

void Nodo::actualizarPadre(Nodo* padre) {
	if(this->getValor()>padre->getValor()){
		//cout<<"he actualizado un valor"<<endl;
	this->setAcum(padre->getValor());
	this->padre=padre;
	}
}

Nodo::~Nodo(){
	delete this->padre;
}

int Nodo::getAcum() const {
	return acum;
}

void Nodo::setAcum(int acum) {
	this->acum = acum;
}

int Nodo::getDist() const {
	return dist;
}

void Nodo::setDist(int dist) {
	this->dist = dist;
}

int Nodo::getCoste() const {
	return coste;
}

void Nodo::setCoste(int coste) {
	this->coste = coste;
}

void Nodo::setPos(const Posicion& pos) {
	this->pos = pos;
}

void Nodo::getPadre(Nodo *&abuelo){
	abuelo=this->padre;
}
