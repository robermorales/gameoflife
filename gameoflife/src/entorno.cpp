/*
 * Implementación del tad entorno
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

// cabeceras necesarias
#include "entorno.h"

// librerías necesarias
#include <allegro.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;

// datos privados

// vector que contiene enlace a las imágenes de las fichas que se usan en el tablero
BITMAP *fichas[NUM_VALOR];

// implementación de las operaciones

bool TEntornoIniciar(int filas, int col) {

	// inicio del entorno allegro
	allegro_init();
	install_keyboard();
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

	// inicio del vector de fichas desde los archivos BMP
	for (int i = 1; i <= NUM_VALOR; i++) {
		stringstream ss_nombre;
		ss_nombre << "f" << i << ".bmp";
		fichas[i - 1] = load_bitmap(ss_nombre.str().c_str(), NULL);
	}

	return true;
}

void TEntornoTerminar() {

	clear_keybuf();
	for (int i = 1; i <= NUM_VALOR; i++)
		if (fichas[i - 1] != NULL)
			destroy_bitmap(fichas[i - 1]);

}

bool TEntornoCargarConfiguracion(string nombre_fichero, int &n_filas,
		int &n_columnas, string & patron_inicial) {

	ifstream entrada;
	string comentario;

	entrada.open(nombre_fichero.c_str());

	if (entrada == 0) {
		cout << "Fichero de configuración no encontrado: " << nombre_fichero << endl;
		cout << "Formato:" << endl;
		cout << "\tcolumnas" << endl;
		cout << "\t[Num- de columnas del tablero]" << endl;
		cout << "\tfilas" << endl;
		cout << "\t[Num- de columnas del tablero]" << endl;
		cout << "\tsemilla" << endl;
		cout << "\t[Archivo con el patrón inicial]" << endl;
		return false;
	}

	entrada >> comentario >> n_columnas;
	entrada >> comentario >> n_filas;
	entrada >> comentario >> patron_inicial;

	if (n_filas > MAX_NUM_FILAS) {
		cout << "filas exceden máximo: " << MAX_NUM_FILAS;
		return false;
	}

	if (n_columnas > MAX_NUM_COLUMNAS) {
		cout << "columnas exceden máximo: " << MAX_NUM_COLUMNAS;
		return false;
	}

	entrada.close();

	return true;
}

void TEntornoPonerCasilla(int fila, int columna, int valor) {

	acquire_screen();
	draw_sprite(screen, fichas[valor - 1], MARGEN_X + columna * ANCHO_CASILLA,
			MARGEN_Y + fila * ALTO_CASILLA);
	release_screen();

}

void TEntornoMostrarMensajeFin(string cad) {

	int i, j;

	// Borrar un rectangulo
	rectfill(screen, 200, 200, 620, 440, makecol(0, 0, 0));

	// Efecto
	for (i = 0, j = 0; i < 40 && j < 40; i += 2, j += 2) {
		rect(screen, i + 220, j + 240, 600 - i, 400 - j,
				makecol(255, 255, 255));
		usleep(25000); // 25 milisegundos
	}

	// Mensaje
	textout_ex(screen, font, cad.c_str(), 280, 320, makecol(255, 255, 255),
			makecol(0, 0, 0));
}

TipoTecla TEntornoLeerTeclaSiPulsada() {

	TipoTecla tecla = TNada;

	if (keypressed())
		tecla = TEntornoLeerTecla();

	return tecla;
}

TipoTecla TEntornoLeerTecla() {

	TipoTecla tecla = TNada;
	readkey();

	if (key[__allegro_KEY_UP])
		tecla = TArriba;
	else if (key[__allegro_KEY_DOWN])
		tecla = TAbajo;
	else if (key[__allegro_KEY_RIGHT])
		tecla = TDerecha;
	else if (key[__allegro_KEY_LEFT])
		tecla = TIzquierda;
	else if (key[__allegro_KEY_ENTER])
		tecla = TEnter;
	else if (key[__allegro_KEY_ESC])
		tecla = TSalir;

	return tecla;
}
