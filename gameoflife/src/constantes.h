/*
 * Constantes comunes al entorno gráfico y a la lógica del juego
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

// Tamaño de la ventana del juego
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;

// Definición de constantes para posicionar los números en el tablero
const int MARGEN_X = 0;  // Origen de las x
const int MARGEN_Y = 0;  // Origen de las y
const int ALTO_CASILLA = 6;  // Distancia entre filas
const int ANCHO_CASILLA = 6;  // Distancia entre columnas

// Dimensiones máximas y mínimas del tablero
const int MAX_NUM_FILAS    = ( ALTO_VENTANA  - 2 * MARGEN_X ) / ALTO_CASILLA;
const int MAX_NUM_COLUMNAS = ( ANCHO_VENTANA - 2 * MARGEN_Y ) / ANCHO_CASILLA;

// Máximo número de colores
const int NUM_VALOR = 6;

#endif /* CONSTANTES_H_ */
