/**
ELEMENTOS DE PROGRAMACIÓN/FUNDAMENTOS DE PROGRAMACIÓN
Curso 2012/13

Nombre: CASILLA.H
Descripción: Especificación del TAD Casilla para el proyecto NenRaya
	     Almacena y manipula los datos de una casilla del tablero del juego
Autor:       Profesores de las asignaturas
Fecha de creación:	17/11/2012

*/
#ifndef TADCASILLA_H
#define TADCASILLA_H

struct casilla {
        bool vacia;  // indica si la casilla está vacía o no
        int color;   // si la casilla no está vacía, indica el color (de 1 a 5)
};

/**
PRE:
POST: Devuelve una casilla inicializada a vacía.
Complejidad: O(1)
*/
casilla crearCasilla();

/**
PRE: c es una casilla válida y _valor corresponde a un color válido (de 1 a 5)
POST: Colorea la casilla c con el valor pasado por parámetro
Complejidad: O(1)
*/
void colorearCasilla(casilla &c, int _color);


/**
PRE: c es una casilla válida
POST: Establece la casilla vacía
Complejidad: O(1)
*/
void vaciarCasilla (casilla &c);

/**
PRE: c es una casilla válida no vacía.
POST: Devuelve el color de la casilla c (de 1 a 5)
Complejidad: O(1)
*/
int queColorCasilla(casilla c);

/**
PRE: c es una casilla válida.
POST: Devuelve si la casilla c está vacía o no
Complejidad: O(1)
*/
bool esVaciaCasilla (casilla c);

#endif
