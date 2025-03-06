CC = gcc
CFLAGS = -Wall -Wextra

OUT_DIR = out
SRC_DIR = src
TAR_SRC_DIR = files

TAR_FILES = 1.dat 2.dat 3.dat

all: mkdir mytar tar

mytar:
	$(CC) $(CFLAGS) $(SRC_DIR)/mytar.c -o $(OUT_DIR)/mytar.out

mkdir:
	mkdir -p $(OUT_DIR)

tar:
	tar -cf $(OUT_DIR)/tar.tar -C $(TAR_SRC_DIR) $(TAR_FILES)

clean:
	rm -rf $(BUILD_DIR)/*.o
