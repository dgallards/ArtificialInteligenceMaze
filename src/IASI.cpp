//============================================================================
// Name        : IASI.cpp
// Author      : Diegox1998
// Version     : 0.2
// Copyright   : (C) <2019>  <Diegox1998>
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
// Description : Several heuristic search algorithms are performed over some mazes
//============================================================================

#include <iostream>
#include <unistd.h>
#include <ctime>
#include "Tablero.h"
#include "Nodo.h"
#include "IList.h"

using namespace std;
bool DEBUG = false;

void hijoMejor(Nodo *vectorA[100], Nodo *&mejor, int &contador) {
	//void *p;
	int mejorh = vectorA[0]->getDist();
	int pos = 0;
	for (int i = 0; i < contador; i++) {
		if (DEBUG)
			cout << i << ": " << vectorA[i]->getDist() << endl;
		if (mejorh > vectorA[i]->getDist()) {
			mejorh = vectorA[i]->getDist();
			mejor = vectorA[i];
			pos = i;
		}
	}
	if (DEBUG)
		cout << endl << "la mejor h es : " << mejorh << endl;
	//delete vectorA[pos];
	vectorA[pos] = NULL;
	for (int j = pos; j < contador; j++)
		vectorA[j] = vectorA[j + 1];

	contador--;

}
void hijoMejorAstar(Nodo *vectorA[100], Nodo *&mejor, int &contador) {

	int mejorVal = vectorA[0]->getValor();
	int mejorh = vectorA[0]->getDist();
	int pos = 0;
	for (int i = 0; i < contador; i++) {
		if (DEBUG)
			cout << i << ": " << vectorA[i]->getValor() << " "
					<< vectorA[i]->getDist() << endl;
		if (mejorVal > vectorA[i]->getValor()) {
			mejorVal = vectorA[i]->getValor();
			mejor = vectorA[i];
			pos = i;
		} else {
			if (mejorVal == vectorA[i]->getValor()) {
				//if(mejorh>=vectorA[i]->getDist()){
				mejorh = vectorA[i]->getDist();
				mejor = vectorA[i];
				pos = i;
				//}
			}
		}
	}
	if (DEBUG)
		cout << endl << "la mejor h es : " << mejorVal << " he ido por: " << pos
				<< endl;
	//delete vectorA[pos];
	vectorA[pos] = NULL;
	for (int j = pos; j < contador; j++)
		vectorA[j] = vectorA[j + 1];

	contador--;

}
bool in(Nodo *vectorA[100], int x, int y, int contador, int &pos) {
	bool esta = false;
	Posicion aux;
	int i = 0;
	while (i < contador) {
		aux = vectorA[i]->getPos();
		if (aux.getFila() == x && aux.getColumna() == y) {
			esta = true;
			pos = i;
		}
		i++;
	}
	return esta;
}

void manual(Tablero *t) {

	t->mostrarTablero();
	t->usaFicha(0, 0);
	t->mostrarTablero();

	while (!t->distanciaAObjetivo() == 0) {
		char a;
		cin >> a;
		switch (a) {

		case 'a':
			if (t->getCol() > 0)
				t->moverIzq();
			t->mostrarTablero();
			cout << "la distancia al objetivo es: " << t->distanciaAObjetivo()
					<< endl;
			break;
		case 'd':
			if (t->getCol() < 9)
				t->moverDer();
			t->mostrarTablero();
			cout << "la distancia al objetivo es: " << t->distanciaAObjetivo()
					<< endl;
			break;
		case 'w':
			if (t->getFil() > 0)
				t->moverArr();
			t->mostrarTablero();
			cout << "la distancia al objetivo es: " << t->distanciaAObjetivo()
					<< endl;
			break;
		case 's':
			if (t->getFil() < 9)
				t->moverAbj();

			cout << "la distancia al objetivo es: " << t->distanciaAObjetivo()
					<< endl;
			break;
		}
		t->mostrarTablero();
	}
	cout << "ha llegado. " << t->getContador()<<"l de gasolina"<<endl;

	t->~Tablero();

}
void escaladaSimple(Tablero *t) {

	clock_t begin = clock();

	//t->mostrarTablero();
	t->usaFicha(0, 0);
	int contador = 0;
	while (!t->distanciaAObjetivo() == 0) {
		if (t->izq() < t->distanciaAObjetivo()) {
			contador++;
			t->moverIzq();
		}
		if (t->arr() < t->distanciaAObjetivo()) {
			contador++;
			t->moverArr();
		}
		if (t->der() < t->distanciaAObjetivo()) {
			contador++;
			t->moverDer();
		}
		if (t->abj() < t->distanciaAObjetivo()) {
			contador++;
			t->moverAbj();
		}
		if (DEBUG) {
			t->mostrarTablero();
			usleep(700000);
		}
	}
	t->mostrarTablero();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "ha gastado: " << t->getContador() << "l de gasolina" << endl;
	cout << "time elapsed: " << elapsed_secs << "s" << endl;
	cout << "numero de comparaciones: " << contador << endl;

	t->~Tablero();
}
void maximaPendienteMOD(Tablero *t) {

	clock_t begin = clock();
	//t->mostrarTablero();
	t->usaFicha(0, 0);
	bool encerrado = false;
	int contadorMemoria = 0;
	int contadorComparaciones = 0;
	int valores[4];
	while (!t->distanciaAObjetivo() == 0 && !encerrado) {
		for (int i = 0; i < 4; ++i) {
			contadorMemoria++;
			switch (i) {
			case 0:
				valores[i] = t->valorDer() + t->der();
				break;
			case 1:
				valores[i] = t->valorAbj() + t->abj();
				break;
			case 2:
				valores[i] = t->valorIzq() + t->izq();
				break;
			case 3:
				valores[i] = t->valorArr() + t->arr();
				break;
			}
		}
		int menor = valores[0];
		int pos = 0;
		for (int i = 1; i < 4; ++i) {
			contadorComparaciones++;
			if (valores[i] < menor) {
				menor = valores[i];
				pos = i;
			}
		}
		if (menor > 100) {
			encerrado = true;
		} else {
			switch (pos) {
			case 0:
				t->moverDer();
				break;
			case 1:
				t->moverAbj();
				break;
			case 2:
				t->moverIzq();
				break;
			case 3:
				t->moverArr();
				break;
			}
		}
		//
		if (DEBUG) {
			cout << endl;
			t->mostrarTablero();
			usleep(700000);
		}

	}
	t->mostrarTablero();

	if (encerrado) {
		cout << "mencerrao AIUDA" << endl;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "ha gastado: " << t->getContador() << "l de gasolina" << endl;
	cout << "time elapsed: " << elapsed_secs << "s" << endl;

	cout << "numero de comparaciones: " << contadorComparaciones << endl;

	cout << "numero de acessos a memoria: " << contadorMemoria << endl;

	t->~Tablero();

}
void maximaPendiente(Tablero *t) {

	clock_t begin = clock();
	//t->mostrarTablero();
	t->usaFicha(0, 0);

	int contadorMemoria = 0;
	int contadorComparaciones = 0;
	int valores[4];

	while (!t->distanciaAObjetivo() == 0) {
		for (int i = 0; i < 4; ++i) {
			contadorMemoria++;
			switch (i) {
			case 0:
				valores[i] = t->der();
				break;
			case 1:
				valores[i] = t->abj();
				break;
			case 2:
				valores[i] = t->arr();
				break;
			case 3:
				valores[i] = t->izq();
				break;
			}
		}
		int menor = valores[0];
		int pos = 0;
		for (int i = 0; i < 4; ++i) {
			contadorComparaciones++;
			if (valores[i] < menor && valores[i] != 666) {
				menor = valores[i];
				pos = i;
			}
		}

		switch (pos) {
		case 0:
			t->moverDer();
			break;
		case 1:
			t->moverAbj();
			break;
		case 2:
			t->moverArr();
			break;
		case 3:
			t->moverIzq();
			break;

		}

		if (DEBUG) {
			cout << endl;
			t->mostrarTablero();
			usleep(700000);
		}

	}
	t->mostrarTablero();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "ha gastado: " << t->getContador() << "l de gasolina" << endl;
	cout << "time elapsed: " << elapsed_secs << "s" << endl;
	cout << "numero de comparaciones: " << contadorComparaciones << endl;

	cout << "numero de acessos a memoria: " << contadorMemoria << endl;
	t->~Tablero();

}
void templeSimulado(Tablero *t) {
	clock_t begin = clock();
	//t->mostrarTablero();
	t->usaFicha(0, 0);

	int contadorMemoria = 0;
	int contadorComparaciones = 0;

	int valores[4];
	int iteraciones = 0;
	int veces = 4;
	bool acabado;
	int menor;
	int pos;
	int distActual;

	while (!t->distanciaAObjetivo() == 0 && !acabado) {

		for (int i = 0; i < 4; ++i) {
			contadorMemoria++;
			switch (i) {
			case 0:
				valores[i] = t->abj();
				break;
			case 1:
				valores[i] = t->der();
				break;
			case 2:
				valores[i] = t->arr();
				break;
			case 3:
				valores[i] = t->izq();
				break;
			}
		}

		iteraciones++;

		distActual = t->distanciaAObjetivo();

		if (iteraciones % 6 == 0 && veces > 1) {
			veces--;
		}
		pos = 0;
		menor = valores[0];
		for (int i = 0; i < veces; ++i) {
			if (valores[i] < menor && valores[i] != 666) {
				contadorComparaciones++;
				menor = valores[i];
				pos = i;
			}
		}

		switch (pos) {
		case 0:
			if (distActual >= t->abj()) {
				t->moverAbj();
			} else {
				acabado = true;
			}

			break;
		case 1:
			if (distActual >= t->der()) {
				t->moverDer();
			} else {
				acabado = true;
			}
			break;
		case 2:
			if (distActual >= t->arr()) {
				t->moverArr();
			} else {
				acabado = true;
			}
			break;
		case 3:
			if (distActual >= t->izq()) {
				t->moverIzq();
			} else {
				acabado = true;
			}
			break;

		}

		if (DEBUG) {
			cout << endl;
			t->mostrarTablero();
			usleep(700000);
		}

	}
	t->mostrarTablero();

	if (!acabado) {

		cout << "ha gastado: " << t->getContador() << "l de gasolina" << endl;

	} else {
		cout << "el algoritmo no encuentra solucion" << endl;

	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time elapsed: " << elapsed_secs << "s" << endl;

	cout << "numero de comparaciones: " << contadorComparaciones << endl;

	cout << "numero de acessos a memoria: " << contadorMemoria << endl;
	t->~Tablero();

}
void primeroMejor(Tablero *t) {
	Nodo *vectorA[100];
	int contadorA = 0;
	Nodo *vectorC[100];
	int contadorC = 0;
	bool mapaCerrados[10][10];
	int x, y;
	Nodo *padre = NULL;
	Nodo *hijo;

	Posicion aux;
	bool enc = false;
	//filas
	int dirX[4] = { 0, 0, 1, -1 };
	//columnas
	int dirY[4] = { -1, 1, 0, 0 };
	//izq,der,abj,arr
	clock_t begin = clock();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			mapaCerrados[i][j] = false;
	}

	y = x = 0;
	padre = new Nodo(0, t->distanciaAObjetivo(x, y), 0, padre, x, y);
	vectorC[0] = padre;
	contadorC++;
	mapaCerrados[x][y] = true;

	while (!enc) {
		if (DEBUG)
			cout << "entro al while" << endl;
		for (int i = 0; i < 4; i++) {
			if (DEBUG)
				cout << "entro al for" << endl;
			if (x + dirX[i] >= 0 && x + dirX[i] <= 9 && y + dirY[i] >= 0
					&& y + dirY[i] <= 9) {

				if (!mapaCerrados[x + dirX[i]][y + dirY[i]]) {
					if (DEBUG)
						cout << "compruebo posiciones: " << x + dirX[i]
								<< y + dirY[i] << endl;
					hijo = new Nodo(0,
							t->distanciaAObjetivo(x + dirX[i], y + dirY[i]), 0,

							padre, x + dirX[i], y + dirY[i]);
					if (DEBUG)
						cout << "creo un nodo" << endl;
					mapaCerrados[x + dirX[i]][y + dirY[i]] = true;
					vectorA[contadorA] = hijo;
					contadorA++;
				}
			}
		}

		hijoMejor(vectorA, hijo, contadorA);
		if (DEBUG)
			cout << "termino hijo mejor" << endl;
		padre = hijo;
		vectorC[contadorC] = padre;
		contadorC++;
		aux = hijo->getPos();
		x = aux.getFila();
		y = aux.getColumna();
		if (t->getValorFicha(x, y) == 0) {
			enc = true;
		}
		if (DEBUG)
			cout << "voy por: " << x << " " << y << " " << endl;
	}
	if (DEBUG)
		cout << "encontrado" << endl;

	//t->mostrarTablero();
	Nodo *auxiliar = NULL;
	while (!(x == 0 && y == 0)) {
		aux = padre->getPos();
		padre->getPadre(auxiliar);
		padre = auxiliar;

		x = aux.getFila();
		y = aux.getColumna();
		t->usaFicha(x, y);
		if (DEBUG) {
			t->mostrarTablero();
			usleep(700000);
		}
	}
	t->mostrarTablero();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "ha gastado: " << t->getContador() << "l de gasolina" << endl;
	cout << "time elapsed: " << elapsed_secs << "s" << endl;

	cout << "numero de nodos en memoria: " << contadorA + contadorC << endl;
	t->~Tablero();

}
void aStar(Tablero *t) {
	Nodo *vectorA[100];
	int contadorA = 0;
	Nodo *vectorC[100];
	int contadorC = 0;
	bool mapaCerrados[10][10];
	int x, y;
	Nodo *padre = NULL;
	Nodo *hijo;
	int pos;

	Posicion aux;
	bool enc = false;
	//filas
	int dirX[4] = { 0, 0, 1, -1 };
	//columnas
	int dirY[4] = { -1, 1, 0, 0 };
	//izq,der,abj,arr
	clock_t begin = clock();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			mapaCerrados[i][j] = false;
	}

	y = x = 0;
	padre = new Nodo(0, t->distanciaAObjetivo(x, y), 0, padre, x, y);
	vectorC[0] = padre;
	contadorC++;
	mapaCerrados[x][y] = true;

	while (!enc) {
		if (DEBUG)
			cout << "entro al while" << endl;
		for (int i = 0; i < 4; i++) {
			if (DEBUG)
				cout << "entro al for" << endl;
			if (x + dirX[i] >= 0 && x + dirX[i] <= 9 && y + dirY[i] >= 0
					&& y + dirY[i] <= 9) {

				if (!mapaCerrados[x + dirX[i]][y + dirY[i]]) {
					if (DEBUG)
						cout << "compruebo posiciones: " << x + dirX[i] << " "
								<< y + dirY[i] << endl;
					hijo = new Nodo(padre->getAcum() + padre->getCoste(),
							t->distanciaAObjetivo(x + dirX[i], y + dirY[i]),
							t->getValorFicha(x + dirX[i], y + dirY[i]),

							padre, x + dirX[i], y + dirY[i]);
					if (DEBUG)
						cout << "creo un nodo" << endl;
					mapaCerrados[x + dirX[i]][y + dirY[i]] = true;
					vectorA[contadorA] = hijo;
					contadorA++;
				} else {
					if (in(vectorA, x + dirX[i], y + dirY[i], contadorA, pos)) {
						vectorA[pos]->actualizarPadre(padre);
					}
				}
			}
		}

		hijoMejorAstar(vectorA, hijo, contadorA);
		if (DEBUG)
			cout << "termino hijo mejor" << endl;
		padre = hijo;
		vectorC[contadorC] = padre;
		contadorC++;
		aux = hijo->getPos();
		x = aux.getFila();
		y = aux.getColumna();
		if (t->getValorFicha(x, y) == 0) {
			enc = true;
		}
		if (DEBUG)
			cout << "voy por: " << x << " " << y << " " << endl;
	}
	if (DEBUG)
		cout << "encontrado";

	//t->mostrarTablero();
	Nodo *auxiliar = NULL;
	while (!(x == 0 && y == 0)) {
		aux = padre->getPos();
		padre->getPadre(auxiliar);
		padre = auxiliar;

		x = aux.getFila();
		y = aux.getColumna();
		t->usaFicha(x, y);
		if (DEBUG) {
			t->mostrarTablero();
			usleep(700000);

		}
	}
	t->mostrarTablero();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "ha gastado: " << t->getContador() << "l de gasolina" << endl;
	cout << "time elapsed: " << elapsed_secs << "s" << endl;
	cout << "numero de nodos en memoria: " << contadorA + contadorC << endl;
	t->~Tablero();
}

int main() {

	int n, m;
	bool valido = false;
	bool continuar = false;
	cout << "Introduzca un numero del 1 al 14:" << endl;
	cin >> m;

	while (!continuar) {

		while (!valido) {

			cout << "Elija que algoritmo desea evaluar: " << endl
					<< "1: Escalada simple" << endl << "2: Maxima pendiente"
					<< endl << "3: Maxima pendiente MODIFICADO" << endl
					<< "4: Temple simulado" << endl << "5: Primero mejor"
					<< endl << "6: A estrella" << endl << "7: Salir" << endl;
			if (DEBUG)
				cout << "9: Manual" << endl;
			cin >> n;
			switch (n) {
			case 1: {
				Tablero * a = new Tablero(m);
				escaladaSimple(a);
			}
				break;
			case 2: {
				Tablero *b = new Tablero(m);
				maximaPendiente(b);
			}
				break;
			case 3: {
				Tablero *c = new Tablero(m);
				maximaPendienteMOD(c);
			}
				break;
			case 4: {
				Tablero *f = new Tablero(m);
				templeSimulado(f);
			}
				break;
			case 5: {
				Tablero *d = new Tablero(m);
				primeroMejor(d);
			}
				break;
			case 6: {
				Tablero *e = new Tablero(m);
				//e->TableroAleat();
				aStar(e);
			}
				break;
			case 7:
				valido = continuar = true;
				break;
			case 9:
				if (DEBUG) {
					Tablero *g = new Tablero(m);

					manual(g);
				} else {
					valido = false;
				}
				break;

			case 1234567890:
				valido = false;
				DEBUG = true;
				break;

			default:
				valido = false;
				break;
			}
			if (!continuar) {
				cout << "Desea evaluar otro algoritmo? 1:Yes Else:No" << endl;
				cin >> n;
				if (n != 1) {
					continuar = true;
					return 0;
				} else {
					cout << "Desea cambiar de laberinto? 1:Yes Else:No" << endl;
					cin >> n;
					if (n == 1) {
						cout << "Introduzca un numero del 1 al 14:" << endl;
						cin >> m;
					}
				}
			}
		}
	}
}
