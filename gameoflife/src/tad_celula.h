#ifndef TAD_CELULA_H
#define TAD_CELULA_H

#include "constantes.h"

struct celula {
	long long edad;
	bool vive;
	bool vivira;
	bool conoce_su_futuro;
};

/**
 * PRE: viva es un valor booleano
 * POST: Devuelve una célula cuya vida depende del valor de "viva"
 * Complejidad: O(1)
 */
celula crear_celula( bool viva );

/**
 * PRE: self es una célula válida.
 * POST: Informa a la célula de los vecinos que tiene vivos
 * Complejidad: O(1)
 */
bool celula_vive( const celula & self );

/**
 * PRE: self es una célula válida
 *      vecinos_vivos es un número entero entre 0 y 8
 * POST: Notifica a la célula acerca de sus vecinos para que decida vivir o morir
 * Complejidad: O(1)
 */
void celula_informar_vecinos( celula & self, int vecinos_vivos );

/**
 * PRE: self es una celula válida.
 * POST: Informa del valor a dibujar
 * Complejidad: O(1)
 */
int celula_valor( const celula & self );

/**
 * PRE: self es una celula válida.
 * POST: Itera una vez la vida de la celula
 * Complejidad: O(1)
 */
void celula_tick( celula & self );

#endif
