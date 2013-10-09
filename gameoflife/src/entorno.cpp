/**

 INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
 Curso 2012/2013

 Nombre: entorno.cpp
 Descripción: Implementación del TAD Entorno para el proyecto NenRaya.
 Encargado del manejo de la interfaz del juego.
 Autor:	Profesores de las asignaturas
 Fecha:	25/11/2012

 */

#include "entorno.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------
// Definición de colores que usa el entorno
const int COLOR_BLANCO = 0;
const int COLOR_ROJO = 1;
const int COLOR_NEGRO = 2;
const int COLOR_AMARILLO = 3;
const int COLOR_VERDE = 4;

// string para borrar mensajes
const string b_string = "                                        ";

// Imágenes de fichas que se usan en el tablero
BITMAP *fichas[MAX_FICHAS + 1]; // vector que contiene enlace a las imágenes de las fichas
string nombres[MAX_FICHAS + 1]; //vector que guarda los nombres de los jugadores

// -------------------------------------------------------------
// Declaración de módulos PRIVADOS
// -------------------------------------------------------------

// define el color en función de los valores makecol - allegro library
int makecolor2(int color);

// Dibuja en la pantalla el borde de un tablero con el ancho indicado
void TEntornoPintarRejilla(int f, int c);

// Invierte fila/columna.  El tablero gráfico (entorno) se dibuja por
// Columnas/Filas, mientras en C++ se trata con matrices en Filas/Columnas.
// Para que sea transparente al uso de matrices se invierte en el entorno
void InvertirFC(int &fila, int &columna);

// -------------------------------------------------------------
// Definición de módulos PRIVADOS
// -------------------------------------------------------------

int makecolor2(int color) {

	int col;

	switch (color) {
	case COLOR_BLANCO:
		col = makecol(255, 255, 255);
		break;
	case COLOR_ROJO:
		col = makecol(255, 0, 0);
		break;
	case COLOR_NEGRO:
		col = makecol(0, 0, 0);
		break;
	case COLOR_AMARILLO:
		col = makecol(200, 200, 50);
		break;
	default:
		col = makecol(255, 255, 255);
		break; //color blanco
	}

	return col;
}

void TEntornoPintarRejilla(int filas, int columnas) {
	// Comenzamos en la 0,0
	int i;

	acquire_screen();

	// horizontales
	for (i = 1; i <= filas; i++)
		line(screen, ORIGEN_X + 0 * DISTANCIA_COLS,
				ORIGEN_Y + i * DISTANCIA_FILAS,
				ORIGEN_X + columnas * DISTANCIA_COLS,
				ORIGEN_Y + i * DISTANCIA_FILAS, makecol(255, 255, 255));

	//verticales
	for (i = 0; i <= columnas; i++)
		line(screen, ORIGEN_X + i * DISTANCIA_COLS,
				ORIGEN_Y + 0 * DISTANCIA_FILAS, ORIGEN_X + i * DISTANCIA_COLS,
				ORIGEN_Y + filas * DISTANCIA_FILAS, makecol(255, 255, 255));

	textout_ex(screen, font, "Derecha: Disparar", 500, 140,
			makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex(screen, font, "Escape: Salir", 500, 180, makecol(255, 255, 255),
			makecol(0, 0, 0));

	release_screen();

}

void InvertirFC(int &fila, int &columna) {

	int aux = columna;
	columna = fila;
	fila = aux;

}

// -------------------------------------------------------------
// Definición de la interfaz PÚBLICA
// -------------------------------------------------------------

bool TEntornoIniciar(int filas, int col) {

	char nomfig[20];

	// Iniciar el entorno
	allegro_init();
	install_keyboard();
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

	// Pintar rejilla
//	TEntornoPintarRejilla(filas, col);

	//inicio del vector de fichas a NULL

	for (int i = 0; i <= MAX_FICHAS; i++) {
		sprintf(nomfig, "f%d.bmp", i); // asigna el nombre de la figura a  cargar
		fichas[i] = load_bitmap(nomfig, NULL);
	}

	// Para poder usar números aleatorios
	srand(time(0));

	return true;
}

//Escribe el nombre de los jugadores a la derecha de la pantalla
void TEntornoEscribirNombres(int n) {
	int i;
	int fila = 3;
	int columna = 9;

	for (i = 0; i < n; i++) {
		TEntornoPonerCasilla(fila + i, columna, i + 1);
		textout_ex(screen, font, nombres[i].c_str(), 600,
				250 + i * DISTANCIA_FILAS, makecol(255, 255, 255),
				makecol(0, 0, 0));

	}

}

void TEntornoTerminar() {
	clear_keybuf();
	for (int i = 0; i <= MAX_FICHAS; i++)
		if (fichas[i] != NULL)
			destroy_bitmap(fichas[i]);

}

// Cargar la configuración inicial desde un archivo
bool TEntornoCargarConfiguracion(string nombre_fichero, int &n_filas,
		int &n_columnas, string & patron_inicial) {

	ifstream entrada;
	string comentario;

	entrada.open(nombre_fichero.c_str());

	if (entrada == 0) {
		cout << "Fichero de configuración no encontrado (nenraya.cnf)." << endl;
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

void TEntornoActivarColumna(int columna) {
	int fila = -1;
	char cad[20];
	int color = COLOR_ROJO;

	InvertirFC(fila, columna);

	sprintf(cad, "%d-%d", fila, columna);

	// Pinta de trazo distinto la celda
	acquire_screen();

	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + 1,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 1,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + 2,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + 3,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 3,
			makecolor2(color));

	InvertirFC(fila, columna);
	draw_sprite(screen, fichas[0], ORIGEN_X + columna * DISTANCIA_COLS + 3,
			ORIGEN_Y + fila * DISTANCIA_FILAS + 3);

	release_screen();
}

void TEntornoActivarCasilla(int fila, int columna) {
	char cad[20];
	int color = COLOR_ROJO;

	InvertirFC(fila, columna);

	sprintf(cad, "%d-%d", fila, columna);

	// Pinta de trazo distinto la celda
	acquire_screen();

	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + 1,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 1,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + 2,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + 3,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 3,
			makecolor2(color));

	release_screen();
}

void TEntornoDesactivarColumna(int columna) {
	int fila = -1;
	int color = COLOR_NEGRO;

	InvertirFC(fila, columna);

	// Pinta de trazo distinto la celda
	acquire_screen();

	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + 1,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 1,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + 2,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			makecolor2(color));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + 3,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 3,
			makecolor2(color));

	InvertirFC(fila, columna);
	rectfill(screen, ORIGEN_X + columna * DISTANCIA_COLS + 1,
			ORIGEN_Y + fila * DISTANCIA_FILAS + 1,
			ORIGEN_X + columna * DISTANCIA_COLS + DISTANCIA_COLS - 1,
			ORIGEN_Y + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 1,
			makecol(0, 0, 0));

	release_screen();
}

void TEntornoDesactivarCasilla(int fila, int columna) {

	int color1 = COLOR_BLANCO;
	int color2 = COLOR_NEGRO;
	InvertirFC(fila, columna);

	// Pinta de trazo distinto la celda
	acquire_screen();

	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(color1));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + 1,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 1,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 1,
			makecolor2(color2));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + 2,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			makecolor2(color2));
	rect(screen, ORIGEN_X + fila * DISTANCIA_FILAS + 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + 3,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 3,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS - 3,
			makecolor2(color2));

	release_screen();
}

void TEntornoPonerCasilla(int fila, int columna, int valor) {

	acquire_screen();
	draw_sprite(screen, fichas[valor], ORIGEN_X + columna * DISTANCIA_COLS,
			ORIGEN_Y + fila * DISTANCIA_FILAS);
	release_screen();

}

void TEntornoEliminarCasilla(int fila, int columna) {

	rectfill(screen, ORIGEN_X + columna * DISTANCIA_COLS + 1,
			ORIGEN_Y + fila * DISTANCIA_FILAS + 1,
			ORIGEN_X + columna * DISTANCIA_COLS + DISTANCIA_COLS - 1,
			ORIGEN_Y + fila * DISTANCIA_FILAS + DISTANCIA_FILAS - 1,
			makecol(0, 0, 0));
}

void TEntornoMostrarMensaje(TipoZona zona, string msg) {

	int fila;

	switch (zona) {

	case Zona1:
		fila = 520;
		break;
	case Zona2:
		fila = 540;
		break;
	case Zona3:
		fila = 560;
		break;

	default:
		return;

	}

	textout_ex(screen, font, b_string.c_str(), 500, fila, makecol(255, 0, 0),
			makecol(0, 0, 0));
	textout_ex(screen, font, msg.c_str(), 500, fila, makecol(255, 255, 0),
			makecol(0, 0, 0));

}

void TEntornoMostrarMensajeconNumero(TipoZona zona, string msg, int n) {

	int fila;
	stringstream ss;
	ss << msg << n;

	switch (zona) {
	case Zona1:
		fila = 520;
		break;
	case Zona2:
		fila = 540;
		break;
	case Zona3:
		fila = 560;
		break;
	default:
		return;
	}

	textout_ex(screen, font, b_string.c_str(), 500, fila, makecol(255, 0, 0),
			makecol(0, 0, 0));
	textout_ex(screen, font, ss.str().c_str(), 500, fila, makecol(255, 255, 0),
			makecol(0, 0, 0));

}

void TEntornoMostrarMensajeFin(string cad) {

	int i, j;

	// Borrar un rectangulo
	rectfill(screen, 200, 200, 620, 440, makecol(0, 0, 0));

	// Efecto
	for (i = 0, j = 0; i < 40 && j < 40; i += 4, j += 4) {
		rect(screen, i + 220, j + 240, 600 - i, 400 - j,
				makecolor2(COLOR_VERDE));
		rect(screen, i + 222, j + 242, 598 - i, 398 - j,
				makecolor2(COLOR_BLANCO));
		usleep(25000); // 25 milisegundos
	}

	// Mensaje
	textout_ex(screen, font, cad.c_str(), 280, 320, makecolor2(COLOR_BLANCO),
			makecolor2(COLOR_NEGRO));

}

TipoTecla TEntornoLeerTeclaSiPulsada() {

	TipoTecla tecla = TNada;

	if (keypressed())
		tecla = TEntornoLeerTecla();

	return tecla;
}

TipoTecla TEntornoLeerTecla() {

	TipoTecla tecla = TNada;

//	clear_keybuf();
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
	else if (key[__allegro_KEY_X])
		tecla = TX;

	return tecla;

}

void TEntornoObtenerNombre(string & nombre, int n) {
	nombre = nombres[n - 1];
}

void TEntornoPausa(int d_segundo) {
	usleep(d_segundo * 100000);
}
