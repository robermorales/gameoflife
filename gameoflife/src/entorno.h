/**

 INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
 Curso 2012/2013

 Nombre: entorno.h
 Descripción: Especificación del TAD Entorno para el proyecto GameOfLife.
 Encargado del manejo de la interfaz del juego.
 Autor:	Profesores de las asignaturas
 Fecha:08/10/2013

 */

#ifndef _ENTORNO_H_
#define _ENTORNO_H_

#include "constantes.h"

#include <allegro.h>

#include <string>
using namespace std;

// -------------------------------------------------------------
// Definicion de constantes públicas
// -------------------------------------------------------------

// Máximo tamaño de un mensaje a imprimir en el entorno
const int MAX_MENSAJE = 50;

// -------------------------------------------------------------
// Definicion de tipos
// -------------------------------------------------------------

/**
 *   Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
 *   de los cursores que se ha pulsado
 */
enum TipoTecla {
	TNada, TIzquierda, TDerecha, TArriba, TAbajo, TSalir, TEnter, TX
};

/**
 *   Zonas en el entorno para imprimir mensajes. Existen 3 zonas delimitadas para imprimir un
 *   mensaje en la pantalla del entorno. Se pueden usar para imprimir mensajes de estado de
 *   diferentes tipos (p.e. fichas borradas, puntos obtenidos, etc.)
 */
enum TipoZona {
	Zona1, Zona2, Zona3
};

// -------------------------------------------------------------
// Declaración de interfaz (módulos) PÚBLICA
// -------------------------------------------------------------

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
 PRE: 1 <= n_jugadores <= MAX_FICHAS
 POST: Escribe los nombres de los jugadores a la derecha de la pantalla y dibuja sus fichas
 */
void TEntornoEscribirNombres(int n_jugadores);

/**
 PRE:
 POST: Destruye el contexto del entorno gráfico.
 */
void TEntornoTerminar();

/**
 PRE: Archivo gameoflife.cnf correcto y en la carpeta raíz del proyecto
 (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
 POST: Devuelve:
 true:  si se carga correctamente la configuración del juego,
 false: en caso contrario.

 Si la configuración se lee de forma correcta se devolverá:
 n_filas:       	número de filas del tablero (sin contar el reflejo)
 n_columnas:		número de columnas del tablero
 patron_inicial:    el nombre de archivo con la configuración inicial

 */
bool TEntornoCargarConfiguracion(string nombre_fichero, int &n_filas,
		int &n_columnas, string & patron_inicial);

/**
 PRE:  fila y columna son coordenadas válidas en el entorno.
 PRE:  1 <= filas <= MAX_NUM_FILAS,
 PRE:  1 <= columnas <= MAX_NUM_COLUMNAS,
 POST: Enmarca una casilla con coordenadas fila, columna en un rectángulo rojo.
 */
void TEntornoActivarCasilla(int fila, int columna);

/**
 *  PRE:  1 <= fila <= MAX_NUM_FILAS,
 PRE:  1 <= columna <= MAX_NUM_COLUMNAS,
 PRE: fila y columna son coordenadas válidas en el entorno.
 POST: Enmarca una casilla con coordenadas fila, columna en un rectángulo blanco
 */
void TEntornoDesactivarCasilla(int fila, int columna);

/**
 PRE:  1 <= fila <= MAX_NUM_FILAS,
 PRE:  1 <= columna <= MAX_NUM_COLUMNAS,
 PRE: fila y columna son coordenadas válidas en el entorno.
 POST: Coloca en una casilla la ficha indicada por "valor"

 */
void TEntornoPonerCasilla(int fila, int columna, int valor);

/**
 PRE: fila y columna son coordenadas válidas en el tablero
 POST: Elimina del entorno la ficha que existe en la casilla cuyas coordenadas son fila, columna.
 */
void TEntornoEliminarCasilla(int fila, int columna);

/**
 PRE: El módulo recibe la zona en la que imprimir el mensaje (TipoZona) y una cadena de caracteres.
 POST:Escribe el mensaje pasado por parámetro en el entorno, concretamente, en la zona especificada.
 */
void TEntornoMostrarMensaje(TipoZona zona, string msg);

/**
 PRE: El módulo recibe la zona en la que imprimir el mensaje (TipoZona), una cadena de caracteres y un número.
 POST:Escribe el mensaje pasado seguido por el número en el entorno, en la zona especificada.
 */
void TEntornoMostrarMensajeconNumero(TipoZona zona, string msg, int n);

/**
 PRE:  msg es una cadena de caracteres a mostrar
 POST: Muestra un mensaje para indicar el final de la partida.
 */
void TEntornoMostrarMensajeFin(string msg);

/**
 PRE:
 POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado
 */
TipoTecla TEntornoLeerTecla();

/**
 PRE:
 POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado o TNada si no hay tecla pulsada
 */
TipoTecla TEntornoLeerTeclaSiPulsada();

/**
 PRE: 1 <= n <= MAX_FICHAS
 POST:Devuelve en Nombre el nombre del jugador número n
 */
void TEntornoObtenerNombre(string &nombre, int n);

/**
 PRE: 1 <= decimas_seg
 POST:Interrumpe la ejecución del juego una determinada cantidad de décimas de segundo
 */
void TEntornoPausa(int decimas_seg);

#endif

