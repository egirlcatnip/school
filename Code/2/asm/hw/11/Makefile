CFLAGS=-g -Wall -O2

all: led joystick

led: led.c font8x8.o
	gcc $(CFLAGS) -o led led.c font8x8.o -lnetpbm

font8x8.o: font8x8.c font8x8.h
	gcc $(CFLAGS) -c font8x8.c

joystick: joystick.c
	gcc $(CFLAGS) -o joystick joystick.c

clean:
	rm -f *.o
	rm -f led
	rm -f joystick
