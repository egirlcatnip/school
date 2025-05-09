#include <fcntl.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <netpbm/ppm.h>

#define HEIGHT (8)
#define WIDTH (8)

/** vycisti obsah framebufferu zadanou barvou */
void fb_clear(uint16_t *buf, uint16_t color) {
  for (int i = 0; i < HEIGHT * WIDTH; i++)
    buf[i] = color;
}

/** vlozi pixel zadane barvy na da souradnice x, y */
void fb_put_pixel(uint16_t *buf, int x, int y, uint16_t color) {
  buf[y * WIDTH + x] = color;
}

/** vykresli jeden znak do framebufferu */
void fb_draw_char(uint16_t *buf, uint16_t color, char c);

/** vykresli cast textu do framebufferu, position udava pozici vykreslovaneho
 * pismene krat 8 */
void fb_draw_text_scrolled(uint16_t *buf, uint16_t color, char *s,
                           int position);

char *text = "Hello world!";

/** prevede RGB barvu na format 5:6:5, max_val udava maximalni hodnotu slozek r,
 * g, b */
uint16_t scale_RGB_to_16b(unsigned int r, unsigned int g, unsigned b,
                          unsigned int max_val) {
  double d = max_val;
  // protoze pro mene vyznamne bity jsou zmeny barev minimalni
  // preskalujeme na mensi rozsah, aby nizsi bity byly 0
  uint16_t sr = (r / d) * 16;
  uint16_t sg = (g / d) * 32;
  uint16_t sb = (b / d) * 16;

  return (sr << 11) | (sg << 5) | sb;
}

/** vykresli ve formatu ppm  obrazek 8x8 do framebufferu*/
int fb_show_img(uint16_t *fb, char *path) {
  FILE *f = fopen(path, "r");
  if (!f)
    return -1;

  int cols, rows;
  pixval max_val;
  pixel **pixels = ppm_readppm(f, &cols, &rows, &max_val);
  if ((cols < WIDTH) || (rows < HEIGHT)) {
    fclose(f);
    return -1;
  }

  for (int r = 0; r < HEIGHT; r++) {
    for (int c = 0; c < HEIGHT; c++) {
      pixel p = pixels[r][c];
      fb_put_pixel(fb, c, r, scale_RGB_to_16b(p.r, p.g, p.b, max_val));
    }
  }

  fclose(f);
  return 0;
}
int main() {
  // frame buffer Sense HAT
  int fd = open("/dev/fb1", O_RDWR);
  if (fd < 0) {
    printf("unable to open framebuffer");
    return EXIT_FAILURE;
  }

  // pres ioctl je mozne zpristupnit informace o zarizeni
  // viz https://www.kernel.org/doc/Documentation/fb/api.txt
  struct fb_fix_screeninfo fb_info;
  if (ioctl(fd, FBIOGET_FSCREENINFO, &fb_info) == -1) {
    printf("unable to obtain device info\n");
    return EXIT_FAILURE;
  }

  printf("FB ID: %s\n", fb_info.id);

  // namapujeme pamet
  uint16_t *fb =
      mmap(NULL, HEIGHT * WIDTH * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (fb == NULL) {
    printf("unable to map framebuffer");
    return EXIT_FAILURE;
  }

  // vykreslujeme
  /*
          while (1) {
                  for (int i = 0; i < WIDTH; i ++) {
                          fb_put_pixel(fb, i, i, 0xffff);
                          usleep(100000);
                          fb_put_pixel(fb, i, i, 0);

                  }
          }
  */

  // postupne vypsana pismenka
  /*
          for (int i = 0; i < strlen(text); i++) {
                  fb_clear(fb, 0x00);
                  fb_draw_char(fb, 0xff, text[i]);
                  usleep(100000);

          }
  */

  // vykresleni plovouciho textu
  for (int i = 0; i < strlen(text) * 8; i++) {
    fb_clear(fb, 0x00);
    fb_draw_text_scrolled(fb, 0xff, text, i);
    usleep(100000);
  }

  // zobrazeni obrazku ze souboru
  /*
          fb_show_img(fb, "face.ppm");
  */

  munmap(fb, HEIGHT * WIDTH * 2);
  close(fd);
}
