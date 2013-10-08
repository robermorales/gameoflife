/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2012/2013

	Nombre: main.cpp
	Descripción: Implementación del programa principal para el proyecto NenRaya_base
	     	 	 Encargado del funcionamiento del juego.
	Autor:	Profesores de las asignaturas
	Fecha:5/12/2012

*/
#include "entorno.h"
#include <iostream>

using namespace std;

int main(){
	  int col=0;  //columna seleccionada
	  bool salir=false; //controla el final del bucle
	  TipoTecla tecla=TNada;   //almacena la tecla pulsada
	  int num_filas, num_columnas;  //dimensiones del tablero
	  int num_fichas, num_jugadores;  //estas variables cargan información del fichero..
	  int comodin1,comodin2;		  //de configuración que no se van a utilizar

	  //Cargar los datos del fichero de configuración
	  if (!TEntornoCargarConfiguracion(num_filas,
			  	  	  	  	  	  	   num_columnas,
			  	  	  	  	  	  	   num_fichas,
			  	  	  	  	  	  	   num_jugadores,
			  	  	  	  	  	  	   comodin1, comodin2) ){
		  cout << "Error al cargar la configuración desde fichero [nenraya.cnf]."  << endl;
	  	  return false;
	  	  }
	  //Inicia el entorno gráfico y dibuja el tablero
	  if (!TEntornoIniciar (num_filas, num_columnas))
		  return false;

	  TEntornoMostrarMensaje(Zona2, "Si pulsas Enter se borran las fichas");

	  //Coloca la flecha sobre la primera columna
	  TEntornoActivarColumna (0);

	  //Colocamos cuatro fichas en el tablero
	  TEntornoPonerCasilla (0,0,1);
	  TEntornoPonerCasilla (1,1,2);
	  TEntornoPonerCasilla (2,2,1);
	  TEntornoPonerCasilla (3,3,2);

	  while (!salir){
	    tecla=TEntornoLeerTecla();

	    switch (tecla) {
	      case TDerecha: //la flecha se desplaza hacia la derecha
	    	  TEntornoDesactivarColumna(col);
	    	  if (col < num_columnas-1) col++;
	    	 	   TEntornoActivarColumna(col);
	      break;

	      case TIzquierda: //la flecha se desplaza hacia la izquierda
	    	  TEntornoDesactivarColumna(col);
	    	  if (col > 0) col--;
	    	  	   TEntornoActivarColumna(col);
				break;

	      case TEnter:  //se borran las 4 fichas que hay en el tablero
	    	    TEntornoEliminarCasilla (0,0);
	    		TEntornoEliminarCasilla (1,1);
	    		TEntornoEliminarCasilla (2,2);
	    		TEntornoEliminarCasilla (3,3);
	    		salir = true;
				break;

	      case TSalir:
	    	  	  salir=true;
   	  	  	  	  break;
	      default:
	      	  break;
	    }//Fin del switch

	  }//fin del while


	TEntornoMostrarMensajeFin("      ¡¡¡ A D I O S !!!");
	TEntornoLeerTecla();
    TEntornoTerminar();  //se cierra en entorno gráfico

	return 0;
}






