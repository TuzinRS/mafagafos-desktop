#include "global.h"
int dpi_w = 0;
int dpi_h = 0;
int dpi = 0;

void SCREEN_update_dpi(int width,int height) {
	dpi_w = width / 100;
	dpi_h = height / 100;
	dpi = (dpi_w + dpi_h) / 2;
}
