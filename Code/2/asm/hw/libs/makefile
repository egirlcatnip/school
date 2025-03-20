CC = gcc
CFLAGS = -Wall -Wextra
AR = ar
SRC_DIR = src
BUILD_DIR = build
OUT_DIR = out
LIB_DIR = out/lib

all: gonio matrix_test_static matrix_test_dynamic

gonio: $(OUT_DIR)/gonio.out

$(OUT_DIR)/gonio.out: $(BUILD_DIR)/gonio.o | mkdir
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/gonio.o: $(SRC_DIR)/gonio.c | mkdir
	$(CC) $(CFLAGS) -c $< -o $@

matrix_test_static: $(OUT_DIR)/matrix_static_test.out

$(OUT_DIR)/matrix_static_test.out: $(SRC_DIR)/matrix_test.c $(LIB_DIR)/libmatrix.a | mkdir
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lmatrix -lm -static

$(LIB_DIR)/libmatrix.a: $(BUILD_DIR)/matrix.o | mkdir
	$(AR) rcs $@ $<

matrix_test_dynamic: $(OUT_DIR)/matrix_dynamic_test.out

$(OUT_DIR)/matrix_dynamic_test.out: $(SRC_DIR)/matrix_test.c $(LIB_DIR)/libmatrix.so | mkdir
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lmatrix -lm -Wl,-rpath,'$$ORIGIN/lib'

$(LIB_DIR)/libmatrix.so: $(BUILD_DIR)/matrix.o | mkdir
	$(CC) $(CFLAGS) -shared -o $@ $< -lm

$(BUILD_DIR)/matrix.o: $(SRC_DIR)/matrix.c | mkdir
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

mkdir: $(BUILD_DIR) $(OUT_DIR) $(LIB_DIR)

$(BUILD_DIR) $(OUT_DIR) $(LIB_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(OUT_DIR)

.PHONY: all gonio matrix_test_static matrix_test_dynamic mkdir clean
