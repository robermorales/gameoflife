/*
 * Implementación del programa principal
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

// librería gráfica, para controlar la pantalla
#include "entorno.h"

// librería con el tad tablero, para controlar la lógica del juego
#include "tad_tablero.h"

// inicio del programa principal
int main() {

	// nombre del fichero de configuración
	string fichero_configuracion = "gameoflife.cnf";

	// variables a leer del fichero de configuración
	int num_filas, num_columnas;  // dimensiones del tablero
	string patron_inicial; // nombre del fichero con el patrón inicial

	// variables de la dinámica de juego
	tablero juego; // almacena el tablero de juego
	TipoTecla tecla = TNada;  // almacena la tecla pulsada

	// leer configuración
	if (!TEntornoCargarConfiguracion(fichero_configuracion, num_filas,
			num_columnas, patron_inicial))
		return false;

	// crear tablero de juego y leer el patrón inicial de un archivo
	crear_tablero(juego, num_filas, num_columnas);
	tablero_leer_patron(juego, patron_inicial);

	// iniciar entorno gráfico
	if (!TEntornoIniciar(num_filas, num_columnas))
		return false;

	// mientras no pulsemos escape
	while (tecla != TSalir) {

		// leemos la tecla pulsada
		tecla = TEntornoLeerTeclaSiPulsada();

		// y actuamos en consecuencia
		switch (tecla) {

		// si pulsamos ENTER
		case TEnter:

			// comienza el juego de nuevo
			crear_tablero(juego, num_filas, num_columnas);
			tablero_leer_patron(juego, patron_inicial);

			break;

		// si no pulsamos ninguna tecla programada
		default:

			// iteramos el juego un tick
			tablero_tick(juego);

			// pintamos en pantalla las celdas
			for (int i = 0; i < num_filas; i++)
				for (int j = 0; j < num_columnas; j++) {
					int valor = tablero_valor(juego, i, j);
					TEntornoPonerCasilla(i, j, valor);
				}

			break;
		}  // fin del switch
	}  // fin del while

	// aquí llegamos si pulsamos escape
	TEntornoMostrarMensajeFin("pulsa una tecla para salir");

	// leemos una tecla más antes de salir
	TEntornoLeerTecla();

	// cerramos el entorno gráfico
	TEntornoTerminar();

	return 0;
}

