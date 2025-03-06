CC = gcc
CFLAGS = -Wall -Wextra -fPIC
AR = ar
BUILD_DIR = build
LIB_DIR = lib
OUT_DIR = out
SRC_DIR = src

all: mkdir gonio_static gonio_dynamic matrix_static matrix_dynamic matrix_static_test matrix_dynamic_test

gonio_static: mkdir
	$(CC) $(CFLAGS) $(SRC_DIR)/gonio.c -o $(OUT_DIR)/gonio_static.out -lm -static

gonio_dynamic: mkdir
	$(CC) $(CFLAGS) $(SRC_DIR)/gonio.c -o $(OUT_DIR)/gonio_dynamic.out -lm

matrix_static_test: matrix_static
	$(CC) $(CFLAGS) $(SRC_DIR)/test.c -o $(OUT_DIR)/matrix_static_test.out -L$(LIB_DIR) -lmatrix -lm -static

matrix_dynamic_test: matrix_dynamic
	$(CC) $(CFLAGS) $(SRC_DIR)/test.c -o $(OUT_DIR)/matrix_dynamic_test.out -L$(LIB_DIR) -lmatrix -lm -Wl,-rpath,$(LIB_DIR)

matrix_static: mkdir
	$(CC) $(CFLAGS) -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix.o
	$(AR) rcs $(LIB_DIR)/libmatrix.a $(BUILD_DIR)/matrix.o

matrix_dynamic: mkdir
	$(CC) $(CFLAGS) -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix.o
	$(CC) $(CFLAGS) -shared -o $(LIB_DIR)/libmatrix.so $(BUILD_DIR)/matrix.o

mkdir:
	mkdir -p $(BUILD_DIR) $(LIB_DIR) $(OUT_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o
	rm -f $(OUT_DIR)/*.out
	rm -f $(LIB_DIR)/libmatrix.a
	rm -f $(LIB_DIR)/libmatrix.so
