#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>


#define JOYSTICK_DEVID "Raspberry Pi Sense HAT Joystick"
#define INPUT_DEV_PATH "/dev/input"

/**
 * Vyzkousi otevrit zarizeni a podle jmena overi, jestli se jedna joystick.
 * Pokud ano, vrati otevreny file descriptor, jinak vraci -1.
 */
static int try_joystick_dev(char *dev_path) {
  int fd = open(dev_path, O_RDONLY);
  if (fd < 0)
    return -1;

  // zkontrolujeme jmeno
  char name[64];
  if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) == -1) {
    close(fd);
    return -1;
  }

  if (!strcmp(name, JOYSTICK_DEVID))
    return fd;

  close(fd);
  return -1;
}

/**
 * Mezi vstupnimi zarizenimi najde joystick a vrati jeho file descriptor.
 * Jinak vraci -1.
 */
static int find_joystick_dev() {
  struct dirent *dir;
  DIR *d = opendir(INPUT_DEV_PATH);
  if (!d) {
    printf("Unable to open dev. directory\n");
    return -1;
  }

  int fd = -1;
  while ((dir = readdir(d)) != NULL) {
    char *name = dir->d_name;
    if (!strncmp(name, "event", 5)) {
      char *full_path = malloc(strlen(INPUT_DEV_PATH) + strlen(name) + 2);
      strcpy(full_path, INPUT_DEV_PATH);
      strcat(full_path, "/");
      strcat(full_path, name);
      fd = try_joystick_dev(full_path);
      if (fd >= 0) {
        printf("Joystick found as device: %s\n", full_path);
        break;
      }
    }
  }
  closedir(d);
  return fd;
}

static int process_event(int fd) {
  struct input_event ev;
  int cnt = read(fd, &ev, sizeof(ev));
  if (cnt < sizeof(ev)) {
    printf("read error\n");
    return -1;
  } else {
    if (ev.type == EV_KEY) {
      // printf("T:%i:%i:%i\n", ev.type, ev.code, ev.value);
      switch (ev.code) {
      case KEY_UP:
        printf("up");
        break;
      case KEY_DOWN:
        printf("down");
        break;
      case KEY_LEFT:
        printf("left");
        break;
      case KEY_RIGHT:
        printf("right");
        break;
      }
      if (ev.value == 1)
        printf(" pressed\n");
      if (ev.value == 2)
        printf(" hold\n");
    }
  }
  return 0;
}

int main() {
  int timeout = 1000;
  int fd = find_joystick_dev();

  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLIN;

  while (1) {
    int x = poll(&pfd, 1, timeout);
    if (x < 0)
      return -1;
    if (pfd.revents & POLLIN) {
      int status = process_event(fd);
      if (status == -1)
        break;
    }
  }

  close(fd);
}
