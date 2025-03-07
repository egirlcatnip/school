CC = gcc
CFLAGS = -Wall -Wextra

OUT_DIR = out
SRC_DIR = src
BUILD_DIR = build
TAR_SRC_DIR = files

TAR_FILES = 1.dat 2.dat 3.dat

all: mkdir mytar tar

mytar: mytar.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/*.o -o $(OUT_DIR)/mytar.out

mytar.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mytar.c -o $(BUILD_DIR)/mytar.o

mkdir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(BUILD_DIR)

tar:
	tar -cf $(OUT_DIR)/tar.tar -C $(TAR_SRC_DIR) $(TAR_FILES)

clean:
	rm -rf $(BUILD_DIR)/*.o
