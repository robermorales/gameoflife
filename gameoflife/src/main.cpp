#include "entorno.h"
#include "tad_tablero.h"

int main() {

	string fichero_configuracion = "gameoflife.cnf";
	string patron_inicial;
	int num_filas, num_columnas;  //dimensiones del tablero
	tablero juego;
	TipoTecla tecla = TNada;   //almacena la tecla pulsada

	if (!TEntornoCargarConfiguracion(fichero_configuracion, num_filas,
			num_columnas, patron_inicial))
		return false;

	crear_tablero(juego, num_filas, num_columnas);
	tablero_leer_patron(juego, patron_inicial);

	if (!TEntornoIniciar(num_filas, num_columnas))
		return false;

	while (tecla != TSalir) {
		tecla = TEntornoLeerTeclaSiPulsada();

		switch (tecla) {

		case TEnter:  // comienza el juego de nuevo
			crear_tablero(juego, num_filas, num_columnas);
			tablero_leer_patron(juego, "patron3.gol");
			break;

		default:
			tablero_tick(juego);
			for (int i = 0; i < num_filas; i++)
				for (int j = 0; j < num_columnas; j++) {
					int valor = tablero_valor(juego, i, j);
					TEntornoPonerCasilla(i, j, valor);
				}
			break;
		}  //Fin del switch
	}  //fin del while

	TEntornoMostrarMensajeFin("pulsa una tecla para salir");
	TEntornoLeerTecla();
	TEntornoTerminar();  //se cierra en entorno gráfico

	return 0;
}

