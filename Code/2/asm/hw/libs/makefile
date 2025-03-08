CC = gcc
CFLAGS = -Wall -Wextra -fPIC
AR = ar
SRC_DIR = src
BUILD_DIR = build
OUT_DIR = out
LIB_DIR = lib

all: gonio_static gonio_dynamic matrix_test_static matrix_test_dynamic

gonio_static: gonio.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/gonio.o -o $(OUT_DIR)/gonio_static.out -lm -static

gonio_dynamic: gonio.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/gonio.o -o $(OUT_DIR)/gonio_dynamic.out -lm

gonio.o: mkdir
	$(CC) $(CFLAGS) -c $(SRC_DIR)/gonio.c -o $(BUILD_DIR)/gonio.o


matrix_test_static: libmatrix.a
	$(CC) $(CFLAGS) $(CFLAGS) $(SRC_DIR)/matrix_test.c -o $(OUT_DIR)/matrix_static_test.out -L$(LIB_DIR) -lmatrix -lm -static

matrix_test_dynamic: libmatrix.so
	$(CC) $(CFLAGS) $(CFLAGS) $(SRC_DIR)/matrix_test.c -o $(OUT_DIR)/matrix_dynamic_test.out -L$(LIB_DIR) -lmatrix -lm

libmatrix.a: matrix.o
	$(AR) rcs $(LIB_DIR)/libmatrix.a $(BUILD_DIR)/matrix.o

libmatrix.so: matrix.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/matrix.o -lm -shared -o $(LIB_DIR)/libmatrix.so

matrix.o: mkdir
	$(CC) $(CFLAGS) -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix.o

mkdir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(OUT_DIR)
