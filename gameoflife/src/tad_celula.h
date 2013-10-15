/*
 * Cabecera del tad célula
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

#ifndef TAD_CELULA_H
#define TAD_CELULA_H

// datos del tad
struct celula {

	// edad que ha vivido la célula (número de iteraciones)
	long long edad;

	// cierto si está viva en esta iteración
	bool vive;

	// cierto si vivirá en la siguiente iteración
	bool vivira;

	// cierto si el valor de 'vivira' es conocido
	bool conoce_su_futuro;
};

// operaciones

/*
 * PRE: viva (entrada) es un valor booleano
 *
 * POST: Devuelve una célula que, en la siguiente iteración, vivirá si "viva" es cierto
 *
 * Complejidad: O(1)
 *
 */
celula crear_celula(bool viva);

/*
 * PRE: self (entrada) es una célula válida.
 *
 * POST: Informa a la célula de los vecinos que tiene vivos
 *
 * Complejidad: O(1)
 *
 */
bool celula_vive(const celula & self);

/*
 * PRE: self (salida) es una célula válida
 *      vecinos_vivos es un número entero entre 0 y 8
 *
 * POST: Notifica a la célula acerca de sus vecinos para que decida vivir o morir
 *
 * Complejidad: O(1)
 *
 */
void celula_informar_vecinos(celula & self, int vecinos_vivos);

/*
 * PRE: self (entrada) es una celula válida.
 *
 * POST: Informa del valor a dibujar, valor > 0, valor <= MAX_VALOR
 *
 * Complejidad: O(1)
 *
 */
int celula_valor(const celula & self);

/*
 * PRE: self (entrada/salida) es una celula válida.
 *
 * POST: Itera una vez la vida de la celula
 *
 * Complejidad: O(1)
 *
 */
void celula_tick(celula & self);

#endif
