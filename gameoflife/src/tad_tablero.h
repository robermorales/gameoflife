/*
 * Cabecera del tad tablero
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

#ifndef TAD_TABLERO_H
#define TAD_TABLERO_H

// cabeceras necesarias
#include "constantes.h"
#include "tad_celula.h"

// librerías necesarias
#include <string>
using namespace std;

// datos del tad
struct tablero {

	// número de iteraciones que ha vivido el tablero
	long long edad;

	// tamaño usado de la matriz
	int filas_usadas;
	int columnas_usadas;

	// matriz de celulas
	celula espacio_de_juego[MAX_NUM_FILAS][MAX_NUM_COLUMNAS];
};

// operaciones

/*
 * PRE:  self     (salida)  no necesita ser válido
 *
 *       filas    (entrada) entre 1 y MAX_NUM_FILAS
 *       columnas (entrada) entre 1 y MAX_NUM_COLUMNAS
 *
 * POST: inicializa un tablero dado su tamaño en filas y columnas
 *
 * Complejidad: O(filas * columnas)
 *
 */
void crear_tablero(tablero & self, int filas, int columnas);

/*
 * PRE: tablero (salida) es un tablero válido
 *
 *      nombre_fichero (entrada) es un nombre de fichero que existe
 *      y cumple con el siguiente formato:
 *
 * ANCHO
 * <ancho>
 * ALTO
 * <alto>
 * <patron>
 *
 * Siendo
 *  ancho: entre 1 y el número de filas    del tablero (incluidos)
 *  alto:  entre 1 y el número de columnas del tablero (incluidos)
 *  patron: <alto> líneas de <ancho> números separados por espacios.
 *          Los números serán: 1 para célula viva y 0 para muerta.
 *
 * POST: lee el patrón que contiene el fichero y lo vuelca en el tablero
 *
 * Complejidad: O(ancho * alto)
 *
 */
bool tablero_leer_patron(tablero & self, string nombre_fichero);

/*
 * PRE: tablero (entrada/salida) es un tablero válido
 *
 * POST: ejecuta una iteración del tablero del juego de la vida
 *
 * Complejidad: O(filas * columnas)
 *
 */
void tablero_tick(tablero & self);

/*
 * PRE: tablero (entrada) es un tablero válido
 *      i (entrada) i >= 0, i < el número de filas    del tablero
 *      j (entrada) j >= 0, j < el número de columnas del tablero
 *
 * POST: devuelve el valor de una célula del tablero, valor > 0, valor <= MAX_VALOR
 *
 * Complejidad: O(1)
 *
 */
int tablero_valor(const tablero & self, int i, int j);

#endif
