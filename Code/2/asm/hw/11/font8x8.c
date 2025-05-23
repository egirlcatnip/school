#include <stdint.h>
#include "font8x8.h"

void fb_put_pixel(uint16_t *buf, int x, int y, uint16_t color);


void fb_draw_char(uint16_t *buf, uint16_t color, char c)
{
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (font8x8_basic[(int)c][y] & (1 << x))
				fb_put_pixel(buf, x, y, color);
		}
	}
}

void fb_draw_text_scrolled(uint16_t *buf, uint16_t color, char *s, int position)
{
	if ((position % 8) == 0) {
		fb_draw_char(buf, color, s[position / 8]); 
		return;
	}

	char c1 = s[position / 8];
	char c2 = s[(position / 8) + 1];


	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			uint8_t mask_1 = font8x8_basic[(int)c1][y];
			uint8_t mask_2 = font8x8_basic[(int)c2][y];
			uint16_t mask = (mask_2 << 8) | mask_1;
			int xc = x + position % 8;
			if (mask & (1 << xc)) fb_put_pixel(buf, x, y, color);
		}
	}
}
