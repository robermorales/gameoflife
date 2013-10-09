#ifndef TAD_TABLERO_H
#define TAD_TABLERO_H

#include "constantes.h"
#include "tad_celula.h"

#include <string>
using namespace std;

struct tablero{

	// número de iteraciones que ha vivido el tablero
	long long edad;

	// tamaño usado de la matriz
	int filas_usadas;
	int columnas_usadas;

	// matriz de celulas
	celula espacio_de_juego[MAX_NUM_FILAS][MAX_NUM_COLUMNAS];
};

void crear_tablero( tablero & t, int filas, int columnas );
bool tablero_leer_patron( tablero & t, string nombre_fichero );
void tablero_tick( tablero & t );
int tablero_valor( const tablero & t, int i, int j );

#endif
