CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = src
BUILD_DIR = build
OUT_DIR = out

SRC_FILES = $(SRC_DIR)/matrix.c $(SRC_DIR)/test.c
OBJ_FILES = $(BUILD_DIR)/matrix.o $(BUILD_DIR)/test.o

all: O3 O2 O1 O0

O3: mkdir O3_o
	$(CC) $(CFLAGS) -O3 -lm $(BUILD_DIR)/*_O3.o -o $(OUT_DIR)/matrix_O3.out

O2: mkdir O2_o
	$(CC) $(CFLAGS) -O2 -lm $(BUILD_DIR)/*_O2.o -o $(OUT_DIR)/matrix_O2.out

O1: mkdir O1_o
	$(CC) $(CFLAGS) -O1 -lm $(BUILD_DIR)/*_O1.o -o $(OUT_DIR)/matrix_O1.out

O0: mkdir O0_o
	$(CC) $(CFLAGS) -O0 -lm $(BUILD_DIR)/*_O0.o -o $(OUT_DIR)/matrix_O0.out

O3_o:
	$(CC) $(CFLAGS) -O3 -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix_O3.o
	$(CC) $(CFLAGS) -O3 -c $(SRC_DIR)/test.c   -o $(BUILD_DIR)/test_O3.o

O2_o:
	$(CC) $(CFLAGS) -O2 -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix_O2.o
	$(CC) $(CFLAGS) -O2 -c $(SRC_DIR)/test.c   -o $(BUILD_DIR)/test_O2.o

O1_o:
	$(CC) $(CFLAGS) -O1 -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix_O1.o
	$(CC) $(CFLAGS) -O1 -c $(SRC_DIR)/test.c   -o $(BUILD_DIR)/test_O1.o

O0_o:
	$(CC) $(CFLAGS) -O0 -c $(SRC_DIR)/matrix.c -o $(BUILD_DIR)/matrix_O0.o
	$(CC) $(CFLAGS) -O0 -c $(SRC_DIR)/test.c   -o $(BUILD_DIR)/test_O0.o

mkdir:
	mkdir -p $(BUILD_DIR) $(OUT_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(OUT_DIR)/matrix_*.out
