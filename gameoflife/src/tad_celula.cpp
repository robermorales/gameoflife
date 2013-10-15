/*
 * Implementación del tad célula
 *
 * Proyecto: gameoflife - Juego de la vida
 * Autores: profesores de la asignatura
 * Fecha: octubre de 2013
 *
 */

// cabeceras necesarias
#include "tad_celula.h"

// implementación de las operaciones

celula crear_celula(bool viva) {
	celula self;

	self.edad = 0;
	self.vivira = viva;
	self.conoce_su_futuro = true;

	return self;
}

bool celula_vive(const celula & self) {
	return self.vive;
}

void celula_informar_vecinos(celula & self, int vecinos_vivos) {

	// La célula sigue viviendo si tiene 2 o 3 vecinos
	if (self.vive)
		self.vivira = (vecinos_vivos == 2 || vecinos_vivos == 3);

	// La célula nace si está muerta y tiene exactamente 3 vecinos
	else
		self.vivira = (vecinos_vivos == 3);

	self.conoce_su_futuro = true;
}

int celula_valor(const celula & self) {
	int valor;

	if (!self.vive)
		valor = 1;
	else if (!self.vivira)
		if (self.edad == 1)
			valor = 5;
		else
			valor = 6;
	else {
		if (self.edad == 1)
			valor = 2;
		else if( self.edad == 2)
			valor = 4;
		else
			valor = 3;
	}

	return valor;
}

void celula_tick(celula & self) {
	if (self.conoce_su_futuro)
		self.vive = self.vivira;

	if (self.vive)
		self.edad++;
	else
		self.edad = 0;

	self.conoce_su_futuro = false;
}

