CC = gcc
CFLAGS = -Wall -Wextra

OUT_DIR = out
SRC_DIR = src
TAR_SRC_DIR = src/files
BUILD_DIR = build

TAR_FILES = $(TAR_SRC_DIR)/*
TAR_PATH = $(OUT_DIR)/tar.tar

all: mytar tar

mytar: $(OUT_DIR)/mytar.out

$(OUT_DIR)/mytar.out: $(BUILD_DIR)/mytar.o | mkdir
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/mytar.o: $(SRC_DIR)/mytar.c | mkdir
	$(CC) $(CFLAGS) -c $< -o $@

tar: $(TAR_PATH)

$(TAR_PATH): $(TAR_FILES) | mkdir
	cd $(TAR_SRC_DIR) && tar -cf ../../$(TAR_PATH) *
	touch $(TAR_PATH)

mkdir: $(BUILD_DIR) $(OUT_DIR)

$(BUILD_DIR) $(OUT_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OUT_DIR)

.PHONY: all mytar tar mkdir clean
