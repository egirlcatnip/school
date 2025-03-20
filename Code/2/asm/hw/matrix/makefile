CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

SRC_DIR = src
BUILD_DIR = build
OUT_DIR = out

OPTIMIZATION_LEVELS = O3 O2 O1 O0

all: $(OPTIMIZATION_LEVELS)

$(OPTIMIZATION_LEVELS): %: $(OUT_DIR)/matrix_%.out

$(OUT_DIR)/matrix_%.out: $(BUILD_DIR)/matrix_%.o $(BUILD_DIR)/test_%.o | mkdir
	$(CC) $(CFLAGS) -$* $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/matrix_%.o: $(SRC_DIR)/matrix.c | mkdir
	$(CC) $(CFLAGS) -$* -c $< -o $@

$(BUILD_DIR)/test_%.o: $(SRC_DIR)/test.c | mkdir
	$(CC) $(CFLAGS) -$* -c $< -o $@

mkdir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OUT_DIR)

.PHONY: all $(OPTIMIZATION_LEVELS) mkdir clean
