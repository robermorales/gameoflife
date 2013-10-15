/*
 * Cabecera del tad entorno
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

#ifndef _ENTORNO_H_
#define _ENTORNO_H_

// cabeceras necesarias
#include "constantes.h"

// librerías necesarias
#include <string>
using namespace std;

// datos del tad

// tipo devuelto por la operacion LeerTecla para representar teclas pulsadas
enum TipoTecla {
	TNada, TIzquierda, TDerecha, TArriba, TAbajo, TSalir, TEnter
};

// operaciones

/**
 PRE:  1 <= filas <= MAX_NUM_FILAS,
 PRE:  1 <= columnas <= MAX_NUM_COLUMNAS,
 POST: Inicia la pantalla de juego, incluyendo una rejilla cuadrada de filas*columnas
 Devuelve:
 true:  Si se inicio correctamente
 false: Si hay algún problema al iniciar
 */
bool TEntornoIniciar(int filas, int col);

/**
 PRE:
 POST: Destruye el contexto del entorno gráfico.
 */
void TEntornoTerminar();

/**
 PRE: nombre_fichero es el nombre correcto de un archivo en la carpeta raíz del proyecto
 (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
 POST: Carga la configuración inicial desde un archivo
 Devuelve:
 true:  si se carga correctamente la configuración del juego,
 false: en caso contrario.

 Si la configuración se lee de forma correcta se devolverán como parámetros de salida:
  n_filas:       	número de filas del tablero (sin contar el reflejo)
  n_columnas:		número de columnas del tablero
  patron_inicial:    el nombre de archivo con la configuración inicial

 */
bool TEntornoCargarConfiguracion(string nombre_fichero, int &n_filas,
		int &n_columnas, string & patron_inicial);

/**
 PRE:  0 <= fila < MAX_NUM_FILAS,
 PRE:  0 <= columna < MAX_NUM_COLUMNAS,
 PRE: fila y columna son coordenadas válidas en el entorno.
 POST: Coloca en una casilla la ficha indicada por "valor"
 */
void TEntornoPonerCasilla(int fila, int columna, int valor);

/**
 PRE:  msg es una cadena de caracteres a mostrar
 POST: Muestra un mensaje para indicar el final de la partida.
 */
void TEntornoMostrarMensajeFin(string msg);

/**
 PRE:
 POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado o TNada si no hay tecla pulsada
 */
TipoTecla TEntornoLeerTeclaSiPulsada();

/**
 PRE:
 POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado
 */
TipoTecla TEntornoLeerTecla();

#endif
