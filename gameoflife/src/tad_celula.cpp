#include "tad_celula.h"

#include <cstdlib>

celula crear_celula(bool viva) {
	celula c;

	c.edad = 0;
	c.vivira = viva;
	c.conoce_su_futuro = true;

	return c;
}

bool celula_vive(const celula & self) {
	return self.vive;
}

void celula_informar_vecinos(celula & self, int vecinos_vivos) {
	if (self.vive) {
		switch (vecinos_vivos) {
		case 2:
		case 3:
			self.vivira = true;
			break;
		default:
			self.vivira = false;
			break;
		}
	} else {
		switch (vecinos_vivos) {
		case 3:
			self.vivira = true;
			break;
		default:
			self.vivira = false;
			break;
		}
	}
	self.conoce_su_futuro = true;
}

int celula_valor(const celula & c) {
	int valor = 0;

	if (!c.vive)
		valor = 0;
	else if (!c.conoce_su_futuro)
		valor = 1;
	else if (c.vivira)
		if (c.edad == 1)
			valor = 2;
		else
			valor = 3;
	else
		valor = 4;

	return valor;
}

void celula_tick(celula & c) {
	if (c.conoce_su_futuro)
		c.vive = c.vivira;
	else
		c.vive = (rand() % 100) > 25;

	if (c.vive)
		c.edad++;
	else
		c.edad = 0;

	c.conoce_su_futuro = false;
}

