
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
#include <fstream>
#include <cstring>


using namespace std;

// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------
// Definición de colores que usa el entorno
const int COLOR_BLANCO    = 0;
const int COLOR_ROJO      = 1;
const int COLOR_NEGRO     = 2;
const int COLOR_AMARILLO  = 3;
const int COLOR_VERDE     = 4;

// Tamaño de la ventana del juego
const int ANCHO_VENTANA   = 800;
const int ALTO_VENTANA    = 600;

// Definicón de constantes para posicionar los números en el tablero
const int DISTANCIA_COLS  = 500/MAX_NUM_COLUMNAS;  // Distancia entre columnas
const int DISTANCIA_FILAS = 450/MAX_NUM_FILAS;  // Distancia entre filas
const int ORIGEN_X        = 20;  // Origen de las x
const int ORIGEN_Y        = 20+40;  // Origen de las y


// Imágenes de fichas que se usan en el tablero
BITMAP *fichas[MAX_FICHAS];  // vector que contiene enlace a las imágenes de las fichas
TipoCadena Nombres[MAX_FICHAS+1]; //vector que guarda los nombres de los jugadores

// -------------------------------------------------------------
// Declaración de módulos PRIVADOS
// -------------------------------------------------------------

// define el color en función de los valores makecol - allegro library
int makecolor2 (int color);

// Dibuja en la pantalla el borde de un tablero con el ancho indicado
void TEntornoPintarRejilla (int f, int c);

// Invierte fila/columna.  El tablero gráfico (entorno) se dibuja por
// Columnas/Filas, mientras en C++ se trata con matrices en Filas/Columnas.
// Para que sea transparente al uso de matrices se invierte en el entorno
void InvertirFC (int &fila, int &columna);


// -------------------------------------------------------------
// Definición de módulos PRIVADOS
// -------------------------------------------------------------

int makecolor2 (int color) {

  int col;

  switch (color) {
    case COLOR_BLANCO:   col = makecol( 255, 255, 255); break;
    case COLOR_ROJO:     col = makecol( 255,   0,   0); break;
    case COLOR_NEGRO:    col = makecol( 0, 0, 0); break;
    case COLOR_AMARILLO: col = makecol( 200, 200,  50); break;
    default:             col = makecol( 255, 255, 255); break; //color blanco
  }

  return col;
}


void TEntornoPintarRejilla (int filas, int columnas) {
    // Comenzamos en la 0,0
	int  i;

	acquire_screen();

	// horizontales
	for (i = 1; i <= filas; i++)
	  line( screen, ORIGEN_X+0*DISTANCIA_COLS, ORIGEN_Y+i*DISTANCIA_FILAS, ORIGEN_X+columnas*DISTANCIA_COLS, ORIGEN_Y+i*DISTANCIA_FILAS, makecol( 255, 255, 255));

	//verticales
	for (i = 0;i <= columnas; i++)
	  line( screen, ORIGEN_X+i*DISTANCIA_COLS, ORIGEN_Y+0*DISTANCIA_FILAS, ORIGEN_X+i*DISTANCIA_COLS, ORIGEN_Y+filas*DISTANCIA_FILAS, makecol( 255, 255, 255));
	
	textout_ex (screen, font, "*** N en Raya ***",    500,  50, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "PROYECTO DE PROGRAMACIÓN",  500,  70, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "TECLAS:",                   500, 120, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Drcha:  Flecha derecha",    500, 140, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Izqda:  Flecha izquierda",  500, 160, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Salir:  Escape",            500, 180, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Poner Ficha: Enter",    500, 200, makecol(255, 255, 255), makecol(0, 0, 0));

	release_screen();

}

void InvertirFC (int &fila, int &columna) {

	int aux = columna;
	columna = fila;
	fila    = aux;

}

// -------------------------------------------------------------
// Definición de la interfaz PÚBLICA
// -------------------------------------------------------------

bool TEntornoIniciar (int filas, int col) {

  char nomfig[20];


  // Iniciar el entorno
  allegro_init();
  install_keyboard();
  set_color_depth(16);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

  // Pintar rejilla
  TEntornoPintarRejilla(filas, col);

  //inicio del vector de fichas a NULL

  fichas[0] = load_bitmap("flecha.bmp", NULL);
  for (int i = 1; i <= MAX_FICHAS; i++) {
    sprintf(nomfig, "f%d.bmp", i);  // asigna el nombre de la figura a  cargar
    fichas[i] = load_bitmap(nomfig, NULL);
  }

  return true;
}

//Escribe el nombre de los jugadores a la derecha de la pantalla
void TEntornoEscribirNombres (int n){
	int i;
	int fila =3;
	int columna=9;

	for (i=0;i <n; i++){
		TEntornoPonerCasilla(fila+i,columna,i+1);
		textout_ex (screen, font, Nombres[i],600, 250+i*DISTANCIA_FILAS, makecol(255, 255, 255), makecol(0, 0, 0));

		}

}

void TEntornoTerminar () {
  clear_keybuf();
  for (int i = 0; i <= MAX_FICHAS; i++)
     if (fichas[i] != NULL)
      destroy_bitmap(fichas[i]);

}

// Cargar la configuración inicial desde un archivo
bool TEntornoCargarConfiguracion (int     &n_filas,
								  int     &n_columnas,
								  int     &n_fichas,
								  int	  &n_jugadores,
								  int 	  &comodin1,
		                          int     &comodin2
		                        ) {

	ifstream  entrada;
	TipoCadena   cad;

	entrada.open("nenraya.cnf");
	if (entrada == 0 ){
		cout << "Fichero de configuración no encontrado (nenraya.cnf)." << endl;
		cout << "Formato:"           << endl;
		cout << "\t[Num- de filas del tablero]" << endl;
		cout << "\t[Num- de columnas del tablero]" << endl;
		cout << "\t[Num- de fichas iguales necesarias para ganar]" << endl;
		cout << "\t[Num- de jugadores]" << endl;
		cout << "\t[Dos comodines para posibles ampliaciones del juego]"      << endl;
		cout << "\t[Los nombres de los 5 posibles jugadores]"      << endl;
		return false;
	}

	entrada.getline(cad, MAX_CADENA-1);
	n_filas = atoi(cad);  // número de filas de la mitad superior del tablero

	entrada.getline(cad, MAX_CADENA-1);
	n_columnas = atoi(cad);

	entrada.getline(cad, MAX_CADENA-1);
	n_fichas = atoi(cad);

	entrada.getline(cad, MAX_CADENA-1);
	n_jugadores = atoi(cad);

	entrada.getline(cad, MAX_CADENA-1);
	comodin1 = atoi(cad);

	entrada.getline(cad, MAX_CADENA-1);
	comodin2 = atoi(cad);

	for (int i=0;i < n_jugadores; i++){
		entrada.getline(Nombres[i],MAX_CADENA-1);
	}
	entrada.close();

	return true;
}

void TEntornoActivarColumna (int columna) {
	int fila = -1;
    char cad[20];
    int  color = COLOR_ROJO;
    
    InvertirFC (fila, columna);

    sprintf(cad, "%d-%d", fila, columna);

    // Pinta de trazo distinto la celda
    acquire_screen();
    
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS,   ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS,   makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+1, ORIGEN_Y + columna*DISTANCIA_COLS+1, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-1, makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+2, ORIGEN_Y + columna*DISTANCIA_COLS+2, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-2, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-2, makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+3, ORIGEN_Y + columna*DISTANCIA_COLS+3, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-3, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-3, makecolor2(color));

    InvertirFC (fila, columna);
    draw_sprite( screen, fichas[0],ORIGEN_X+columna*DISTANCIA_COLS + 3 , ORIGEN_Y+fila*DISTANCIA_FILAS +3);

    release_screen();
}

void TEntornoActivarCasilla (int fila, int columna) {
    char cad[20];
    int  color = COLOR_ROJO;

    InvertirFC (fila, columna);

    sprintf(cad, "%d-%d", fila, columna);

    // Pinta de trazo distinto la celda
    acquire_screen();

    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS,   ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS,   makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+1, ORIGEN_Y + columna*DISTANCIA_COLS+1, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-1, makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+2, ORIGEN_Y + columna*DISTANCIA_COLS+2, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-2, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-2, makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+3, ORIGEN_Y + columna*DISTANCIA_COLS+3, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-3, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-3, makecolor2(color));

    release_screen();
}

void TEntornoDesactivarColumna(int columna) {
	int fila = -1;
	int color = COLOR_NEGRO;

	InvertirFC (fila, columna);

  // Pinta de trazo distinto la celda
  acquire_screen();

  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS,   ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS,   makecolor2(color));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+1, ORIGEN_Y + columna*DISTANCIA_COLS+1, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-1, makecolor2(color));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+2, ORIGEN_Y + columna*DISTANCIA_COLS+2, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-2, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-2, makecolor2(color));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+3, ORIGEN_Y + columna*DISTANCIA_COLS+3, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-3, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-3, makecolor2(color));

  InvertirFC (fila, columna);
  rectfill( screen, ORIGEN_X+columna*DISTANCIA_COLS+1, ORIGEN_Y+fila*DISTANCIA_FILAS+1, ORIGEN_X+columna*DISTANCIA_COLS +DISTANCIA_COLS-1,ORIGEN_Y+fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1 , makecol( 0, 0, 0));

  release_screen();
}

void TEntornoDesactivarCasilla(int fila,int columna) {

	int color1 = COLOR_BLANCO;
    int color2 = COLOR_NEGRO;
	InvertirFC (fila, columna);

  // Pinta de trazo distinto la celda
  acquire_screen();

  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS,   ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS,   makecolor2(color1));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+1, ORIGEN_Y + columna*DISTANCIA_COLS+1, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-1, makecolor2(color2));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+2, ORIGEN_Y + columna*DISTANCIA_COLS+2, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-2, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-2, makecolor2(color2));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+3, ORIGEN_Y + columna*DISTANCIA_COLS+3, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-3, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-3, makecolor2(color2));

  release_screen();
}

void TEntornoPonerCasilla(int fila, int columna,int valor) {

        		acquire_screen();
        		draw_sprite( screen, fichas[valor],ORIGEN_X+columna*DISTANCIA_COLS + 3 , ORIGEN_Y+fila*DISTANCIA_FILAS +3);
        		release_screen();

}

void TEntornoEliminarCasilla(int fila, int columna) {

  rectfill( screen, ORIGEN_X+columna*DISTANCIA_COLS+1, ORIGEN_Y+fila*DISTANCIA_FILAS+1, ORIGEN_X+columna*DISTANCIA_COLS +DISTANCIA_COLS-1,ORIGEN_Y+fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1 , makecol( 0, 0, 0));
}

void TEntornoMostrarMensaje (TipoZona zona, TipoMensaje msg) {

	int fila;

	switch (zona) {

		case Zona1: fila = 520; break;
		case Zona2: fila = 540; break;
		case Zona3: fila = 560; break;

		default:  return;

	}

	textout_ex( screen, font, "                                        ",  500,fila , makecol( 255,   0, 0), makecol(0, 0, 0));
	textout_ex( screen, font, msg,500,fila , makecol( 255, 255, 0), makecol(0, 0, 0));

}

void TEntornoMostrarMensajeconNumero (TipoZona zona, TipoMensaje msg, int n) {

	int fila;
    TipoMensaje msg2,num;
	switch (zona) {

		case Zona1: fila = 520; break;
		case Zona2: fila = 540; break;
		case Zona3: fila = 560; break;

		default:  return;

	}
	sprintf(num,"%d",n);
    strcpy(msg2,msg);
    strcat(msg2,num);

	textout_ex( screen, font, "                                        ",  500,fila , makecol( 255,   0, 0), makecol(0, 0, 0));
	textout_ex( screen, font, msg2,500,fila , makecol( 255, 255, 0), makecol(0, 0, 0));

}

void TEntornoMostrarMensajeFin (TipoMensaje cad) {

  int  i, j;

  // Borrar un rectangulo
  rectfill (screen, 200, 200, 620, 440, makecol(0, 0, 0));

  // Efecto
  for (i = 0, j = 0; i < 40 && j < 40; i+=4, j+=4) {
	  rect( screen, i + 220, j + 240, 600 - i, 400 - j, makecol( 255,   0,   0));
	  rect( screen, i + 222, j + 242, 598 - i, 398 - j, makecol( 255, 255, 255));
	  usleep(25000); // 25 milisegundos
  }

  // Mensaje
  textout_ex(screen, font, cad,  280, 320 , makecol( 255, 255, 0), makecol(0, 0, 0));

}

TipoTecla TEntornoLeerTecla () {

	TipoTecla tecla = TNada;

	readkey();
	
	if      (key[KEY_UP])    tecla = TArriba;
	else if (key[KEY_DOWN])  tecla = TAbajo;
	else if (key[KEY_RIGHT]) tecla = TDerecha;
	else if (key[KEY_LEFT])  tecla = TIzquierda;
	else if (key[KEY_ENTER]) tecla = TEnter;
	else if (key[KEY_ESC])   tecla = TSalir;
	else if (key[KEY_X])     tecla = TX;
	
	clear_keybuf();

	return tecla;

}


void TEntornoObtenerNombre (TipoCadena &Nombre,int n){
	strcpy(Nombre, Nombres[n-1]);

}

void TEntornoPausa (int d_segundo){
	usleep(d_segundo * 100000);
}
