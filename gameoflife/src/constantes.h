#ifndef CONSTANTES_H_
#define CONSTANTES_H_

// Tamaño de la ventana del juego
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;

// Definición de constantes para posicionar los números en el tablero
const int ORIGEN_X = 0;  // Origen de las x
const int ORIGEN_Y = 0;  // Origen de las y
const int DISTANCIA_COLS = 5;  // Distancia entre columnas
const int DISTANCIA_FILAS = 5;  // Distancia entre filas

// Dimensiones máximas y mínimas del tablero
const int MAX_NUM_FILAS    = ( ALTO_VENTANA  - 2 * ORIGEN_X ) / DISTANCIA_FILAS;
const int MAX_NUM_COLUMNAS = ( ANCHO_VENTANA - 2 * ORIGEN_Y ) / DISTANCIA_COLS;

// Máximo número de colores
const int MAX_FICHAS = 5;


#endif /* CONSTANTES_H_ */
