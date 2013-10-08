/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2012/2013

	Nombre: entorno.h
	Descripción: Especificación del TAD Entorno para el proyecto NenRaya.
	     	 	 Encargado del manejo de la interfaz del juego.
	Autor:	Profesores de las asignaturas
	Fecha:25/11/2012

*/


#ifndef ENTORNO_H_
#define ENTORNO_H_


#include <allegro.h>

// -------------------------------------------------------------
// Definicion de constantes públicas
// -------------------------------------------------------------

// Número de imágenes de fichas que se usan en el tablero y número de jugadores
const int MAX_FICHAS      = 5;

// Dimensiones máximas y mínimas del tablero

const int MAX_NUM_FILAS		= 90;
const int MAX_NUM_COLUMNAS	= 80;

// Máximo tamaño de un mensaje a imprimir en el entorno y de los nombres de los jugadores
const int MAX_MENSAJE   = 50;
const int MAX_CADENA    = 20;

// -------------------------------------------------------------
// Definicion de tipos
// -------------------------------------------------------------

/**
 *   Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
 *   de los cursores que se ha pulsado
 */
enum TipoTecla {TNada, TIzquierda, TDerecha, TArriba, TAbajo, TSalir, TEnter, TX};

/**
 *   Zonas en el entorno para imprimir mensajes. Existen 3 zonas delimitadas para imprimir un
 *   mensaje en la pantalla del entorno. Se pueden usar para imprimir mensajes de estado de
 *   diferentes tipos (p.e. fichas borradas, puntos obtenidos, etc.)
 */
enum TipoZona {Zona1, Zona2, Zona3};

/**
 *   Tipos para los mensajes a imprimir en pantalla y para los nombres de los jugadores
 */
typedef char TipoMensaje [MAX_MENSAJE];
typedef char TipoCadena [MAX_CADENA];


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
bool TEntornoIniciar (int filas, int col);

/**
  	 PRE: 1 <= n_jugadores <= MAX_FICHAS
 	 POST: Escribe los nombres de los jugadores a la derecha de la pantalla y dibuja sus fichas
*/
void TEntornoEscribirNombres (int n_jugadores);

/**
	PRE:
	POST: Destruye el contexto del entorno gráfico.
*/
void TEntornoTerminar();


/**
	PRE: Archivo nenraya.cnf correcto y en la carpeta raíz del proyecto
	     (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
	POST: Devuelve:
	         TRUE:  si se carga correctamente la configuración del juego,
		     FALSE: en caso contrario.

		Si la configuración se lee de forma correcta se devolverá:
		   n_filas:       	número de filas del tablero (sin contar el reflejo)
		   n_columnas:		número de columnas del tablero
		   n_fichas:  		número de fichas iguales para hacer n en raya
		   n_jugadores:		número de jugadores
		   comodin1 y 2:    2 números para posibles ampliaciones

 */
bool TEntornoCargarConfiguracion (int 		&n_filas,
								  int 		&n_columnas,
								  int       &n_fichas,
								  int		&n_jugadores,
								  int 		&comodin1,
		                          int 		&comodin2);
/**
	PRE:  columna es una coordenada válida en el entorno
	PRE:  1 <= columna <= MAX_NUM_COLUMNAS,
	POST: Coloca una flecha enmarcada en un rectángulo rojo en la parte superior de una columna
*/
void TEntornoActivarColumna(int columna);

/**
	PRE:  fila y columna son coordenadas válidas en el entorno.
	PRE:  1 <= filas <= MAX_NUM_FILAS,
	PRE:  1 <= columnas <= MAX_NUM_COLUMNAS,
	POST: Enmarca una casilla con coordenadas fila, columna en un rectángulo rojo.
*/
void TEntornoActivarCasilla(int fila, int columna);

/**
 * 	PRE:  1 <= columna <= MAX_NUM_COLUMNAS,
    PRE:  columna es una coordenada válida en el entorno.
	POST: Elimina la flecha de la parte superior de una columna
*/
void TEntornoDesactivarColumna(int columna);

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
void TEntornoPonerCasilla (int fila, int columna, int valor);

/**
PRE: fila y columna son coordenadas válidas en el tablero
POST: Elimina del entorno la ficha que existe en la casilla cuyas coordenadas son fila, columna.
*/
void TEntornoEliminarCasilla(int fila, int columna);

/**
PRE: El módulo recibe la zona en la que imprimir el mensaje (TipoZona) y una cadena de caracteres.
POST:Escribe el mensaje pasado por parámetro en el entorno, concretamente, en la zona especificada.
*/
void TEntornoMostrarMensaje (TipoZona zona, TipoMensaje msg);

/**
PRE: El módulo recibe la zona en la que imprimir el mensaje (TipoZona), una cadena de caracteres y un número.
POST:Escribe el mensaje pasado seguido por el número en el entorno, en la zona especificada.
*/
void TEntornoMostrarMensajeconNumero (TipoZona zona, TipoMensaje msg, int n);

/**
PRE:  msg es una cadena de caracteres a mostrar
POST: Muestra un mensaje para indicar el final de la partida.
*/
void TEntornoMostrarMensajeFin (TipoMensaje msg);

/**
PRE:
POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado
*/
TipoTecla TEntornoLeerTecla();

/**
PRE: 1 <= n <= MAX_FICHAS
POST:Devuelve en Nombre el nombre del jugador número n
*/
void TEntornoObtenerNombre (TipoCadena &Nombre,int n);

/**
PRE: 1 <= decimas_seg
POST:Interrumpe la ejecución del juego una determinada cantidad de décimas de segundo
*/
void TEntornoPausa (int decimas_seg);

#endif

