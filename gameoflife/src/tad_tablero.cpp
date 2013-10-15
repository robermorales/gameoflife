/*
 * Implementación del tad tablero
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

// cabeceras necesarias
#include "tad_tablero.h"

// librerías necesarias
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
using namespace std;

// implementación de las operaciones

void crear_tablero(tablero & self, int filas, int columnas) {

	self.edad = 0;
	self.filas_usadas = filas;
	self.columnas_usadas = columnas;

	for (int i = 0; i < self.filas_usadas; i++)
		for (int j = 0; j < self.columnas_usadas; j++)
			self.espacio_de_juego[i][j] = crear_celula(false); //rand() % 2
}

bool tablero_leer_patron(tablero & self, string nombre_fichero) {

	int filas, columnas;
	string comentario;
	ifstream archivo;

	archivo.open(nombre_fichero.c_str());

	if (!archivo)
		return false;

	archivo >> comentario;
	archivo >> columnas;
	archivo >> comentario;
	archivo >> filas;

	if (filas > self.filas_usadas || columnas > self.columnas_usadas) {
		cout << "El patrón no puede ser más grande que el tablero: "
				<< nombre_fichero << endl;
		return false;
	}

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			int valor;
			archivo >> valor;
			self.espacio_de_juego[i][j] = crear_celula(valor != 0);
		}
	}
	return true;
}

int tablero_valor(const tablero & self, int fila, int columna) {
	return celula_valor(self.espacio_de_juego[fila][columna]);
}

void tablero_tick(tablero & self) {
	int vecinos_vivos;

	self.edad++;

	for (int i = 0; i < self.filas_usadas; i++)
		for (int j = 0; j < self.columnas_usadas; j++)
			celula_tick(self.espacio_de_juego[i][j]);

	for (int i = 0; i < self.filas_usadas; i++) {
		for (int j = 0; j < self.columnas_usadas; j++) {

			vecinos_vivos = 0;

			for (int offset_i = -1; offset_i <= 1; offset_i++) {
				for (int offset_j = -1; offset_j <= 1; offset_j++) {
					if (offset_i != 0 || offset_j != 0) {

						int vecina_i = (i + offset_i + self.filas_usadas)
								% self.filas_usadas;
						int vecina_j = (j + offset_j + self.columnas_usadas)
								% self.columnas_usadas;

						celula vecina =
								self.espacio_de_juego[vecina_i][vecina_j];

						if (celula_vive(vecina))
							vecinos_vivos++;
					}
				}
			}
			celula_informar_vecinos(self.espacio_de_juego[i][j], vecinos_vivos);
		}
	}
}
