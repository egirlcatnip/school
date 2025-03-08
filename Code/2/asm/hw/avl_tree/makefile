CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = src
OUT_DIR = out
BUILD_DIR = build

all: mkdir tree_test

tree_test: tree_test.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/*.o -o $(OUT_DIR)/tree_test.out

tree_test.o: avl_tree.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/tree_test.c -o $(BUILD_DIR)/tree_test.o

avl_tree.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/avl_tree.c -o $(BUILD_DIR)/avl_tree.o

valgrind: all
	valgrind --leak-check=full $(TARGET)

gdb: all
	gdb $(TARGET)

mkdir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OUT_DIR)
