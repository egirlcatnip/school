#include <poll.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define STDIN_FILENO 0

//
//
// definice standardne popsane v hlavickovem souboru termios.h
//
//

typedef unsigned int tcflag_t;
typedef unsigned int speed_t;
typedef unsigned char cc_t;
#define TCGETS 0x5401
#define TCSETS 0x5402
#define TIOCWINSZ 0x5413
#define ISIG 0x0001

#define RED "\033[31m"
#define RESET "\033[0m"

/*
struct winsize {
        unsigned short 	ws_row;
        unsigned short 	ws_col;
        unsigned short 	ws_xpixel;
        unsigned short 	ws_ypixel;
};
*/
#define NCCS 32
struct termios {
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  cc_t c_line;
  cc_t c_cc[NCCS];
  speed_t c_ispeed;
  speed_t c_ospeed;
};

//
//
// Sada funkci pracujici s terminalem
//
//

/** vymaze obsah terminalu */
void term_clear() { puts("\033[2J\033[1;1H"); }

/** zjisti velikost terminalu */
void term_get_size(int *rows, int *cols) {
  struct winsize w;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
  *rows = w.ws_row;
  *cols = w.ws_col;
}

/** prepne terminal do rezimu, kdy nevypisuje zadane znaky a neprovadi
 * bufferovani */
tcflag_t term_noncanon() {
  struct termios ctrl;
  ioctl(STDIN_FILENO, TCGETS, &ctrl);
  tcflag_t old = ctrl.c_lflag;
  ctrl.c_lflag = ISIG;
  ioctl(STDIN_FILENO, TCSETS, &ctrl);
  return old;
}

/** prepne terminal do puvodniho stavu, pracuje s hodnotou vracenou funkci
 * term_noncanon */
void term_canon(tcflag_t old) {
  struct termios ctrl;
  ioctl(STDIN_FILENO, TCGETS, &ctrl);
  ctrl.c_lflag = old;
  ioctl(STDIN_FILENO, TCSETS, &ctrl);
}

/** precte jeden znak z terminalu, pouziva pasivni cekani, pokud neni znak
 * precten po dobu danou argumentem timeout, vraci 0 */
char term_read_char(int timeout) {
  char c;
  struct pollfd pfd;
  pfd.fd = STDIN_FILENO;
  pfd.events = POLLIN;

  int state = poll(&pfd, 1, timeout);
  if (state < 0)
    return -1;
  if (pfd.revents & POLLIN) {
    int cnt = read(STDIN_FILENO, &c, 1);
    if (cnt > 0)
      return c;
  }
  return 0;
}

/** presune kurzor na zadane souradnice */
void term_moveto(int r, int c) { printf("\033[%i;%iH", r + 1, c + 1); }

//
//
// Implementace hry PONG
//
//

#define PLAYER_SIZE (5)
#define PLAYER_UP (-1)
#define PLAYER_DOWN (1)
#define SIDE_LEFT (-1)
#define SIDE_RIGHT (1)
#define SIDE_NONE (0)

/** reprezentuje stav hry */
struct {
  int rows;
  int cols;
  int ball_r;
  int ball_c;

  int ball_dir_r;
  int ball_dir_c;

  int player1;
  int player2;
} game;

/** posune micek a vraci, jestli nektera ze stran vyhrala, nebo ne */
int move_ball() {
  term_moveto(game.ball_r, game.ball_c);
  puts(" ");
  game.ball_r += game.ball_dir_r;
  game.ball_c += game.ball_dir_c;

  term_moveto(game.ball_r, game.ball_c);
  puts("*");
  if ((game.ball_r == 1) || (game.ball_r == game.rows - 2))
    game.ball_dir_r *= -1;
  if ((game.ball_c == 3) && (game.ball_r >= game.player1) &&
      (game.ball_r < game.player1 + PLAYER_SIZE)) {
    game.ball_dir_c *= -1;
  }

  if ((game.ball_c == game.cols - 4) && (game.ball_r >= game.player2) &&
      (game.ball_r < game.player2 + PLAYER_SIZE)) {
    game.ball_dir_c *= -1;
  }

  if (game.ball_c == 1)
    return SIDE_LEFT;
  if (game.ball_c == game.cols - 3)
    return SIDE_RIGHT;
  return SIDE_NONE;
}

/** vykresli hrace */
void draw_player(int position, int side) {
  int column = side == SIDE_LEFT ? 2 : game.cols - 3;
  for (int i = 0; i < PLAYER_SIZE; i++) {
    term_moveto(position + i, column);
    puts("X");
  }
}

/** vykresli mantinely hriste */
void draw_game() {
  for (int c = 0; c < game.cols; c++) {
    term_moveto(0, c);
    puts(RED);
    puts("#");
    term_moveto(game.rows - 1, c);
    puts("#");
  }

  for (int r = 0; r < game.rows; r++) {
    term_moveto(r, 0);
    puts("#");
    term_moveto(r, game.cols - 1);
    puts("#");
  }
}

/** posune hrace na dane strane danym smerem */
void move_player(int side, int dir) {
  int column = side == SIDE_LEFT ? 2 : game.cols - 3;
  int *player = side == SIDE_LEFT ? &game.player1 : &game.player2;

  if (dir == PLAYER_UP) {
    if (*player == 1)
      return;
    term_moveto(*player + PLAYER_SIZE - 1, column);
    puts(" ");
    *player = *player - 1;
    term_moveto(*player, column);
    puts("X");
  }

  if (dir == PLAYER_DOWN) {
    if (*player + PLAYER_SIZE == game.rows - 1)
      return;
    term_moveto(*player, column);
    puts(" ");
    *player = *player + 1;
    term_moveto(*player + PLAYER_SIZE - 1, column);
    puts("X");
  }
}

int main() {
  term_clear();
  term_get_size(&game.rows, &game.cols);
  game.rows--;

  // potlaci hodnoty ziskane s pomoci term_get_size
  game.rows = 20;
  game.cols = 40;

  game.ball_r = game.rows / 2;
  game.ball_c = game.cols / 2;
  game.ball_dir_r = 1;
  game.ball_dir_c = 1;
  game.player1 = game.rows / 2 - PLAYER_SIZE / 2;
  game.player2 = game.rows / 2 - PLAYER_SIZE / 2;

  draw_game();
  draw_player(game.player1, SIDE_LEFT);
  draw_player(game.player2, SIDE_RIGHT);

  tcflag_t old = term_noncanon();

  while (1) {
    char c = term_read_char(100);
    if (c == 'x')
      break;
    if (c == 'q')
      move_player(SIDE_LEFT, PLAYER_UP);
    if (c == 'a')
      move_player(SIDE_LEFT, PLAYER_DOWN);
    if (c == 'p')
      move_player(SIDE_RIGHT, PLAYER_UP);
    if (c == 'l')
      move_player(SIDE_RIGHT, PLAYER_DOWN);

    int side = move_ball();
    if (side) {
      term_moveto(game.rows / 2, game.cols / 2 - 5);
      puts("Game over!");
      break;
    }
  }
  term_canon(old);

  return 0;
}
