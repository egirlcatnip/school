#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { BYTE, BIT } Unit;

typedef struct {
  char name;
  int memoryAllocated;
  int memoryUsed;
  Unit unitType;
} Drive;

// Conversion functions
static inline int byte_to_bit(int bytes) {
  return bytes * 8;
}

static inline int bit_to_byte(int bits) {
  return bits / 8;
}

// Convert any memory value to bits for unified comparison.
static inline int to_bits(int memory, Unit unit) {
  return (unit == BYTE) ? byte_to_bit(memory) : memory;
}

// Printing functions
void print_drive(const Drive *d) {
  printf("Drive %c:\n", d->name);
  if (d->unitType == BIT) {
    printf("  Used memory:      %d Bits (%d Bytes)\n", d->memoryUsed, bit_to_byte(d->memoryUsed));
    printf("  Allocated memory: %d Bits (%d Bytes)\n", d->memoryAllocated, bit_to_byte(d->memoryAllocated));
    printf("  Unit: Bits\n");
  }
  else { // BYTE
    printf("  Used memory:      %d Bytes (%d Bits)\n", d->memoryUsed, byte_to_bit(d->memoryUsed));
    printf("  Allocated memory: %d Bytes (%d Bits)\n", d->memoryAllocated, byte_to_bit(d->memoryAllocated));
    printf("  Unit: Bytes\n");
  }
  printf("\n");
}

void print_all_drives(const Drive drives[], int count) {
  for (int i = 0; i < count; i++) {
    print_drive(&drives[i]);
  }
}

// Drive selection functions
Drive *find_drive_with_max_memory(Drive drives[], int count) {
  if (count <= 0) {
    fprintf(stderr, "No drives available.\n");
    exit(EXIT_FAILURE);
  }
  int maxIndex = 0;
  int maxValue = to_bits(drives[0].memoryAllocated, drives[0].unitType);
  for (int i = 1; i < count; i++) {
    int current = to_bits(drives[i].memoryAllocated, drives[i].unitType);
    if (current > maxValue) {
      maxValue = current;
      maxIndex = i;
    }
  }
  return &drives[maxIndex];
}

Drive *find_drive_with_max_available_memory(Drive drives[], int count) {
  if (count <= 0) {
    fprintf(stderr, "No drives available.\n");
    exit(EXIT_FAILURE);
  }
  int maxIndex = 0;
  int maxAvailable = to_bits(drives[0].memoryAllocated - drives[0].memoryUsed, drives[0].unitType);
  for (int i = 1; i < count; i++) {
    int available = to_bits(drives[i].memoryAllocated - drives[i].memoryUsed, drives[i].unitType);
    if (available > maxAvailable) {
      maxAvailable = available;
      maxIndex = i;
    }
  }
  return &drives[maxIndex];
}

Drive *find_drive_with_min_memory(Drive drives[], int count) {
  if (count <= 0) {
    fprintf(stderr, "No drives available.\n");
    exit(EXIT_FAILURE);
  }
  int minIndex = 0;
  int minValue = to_bits(drives[0].memoryAllocated, drives[0].unitType);
  for (int i = 1; i < count; i++) {
    int current = to_bits(drives[i].memoryAllocated, drives[i].unitType);
    if (current < minValue) {
      minValue = current;
      minIndex = i;
    }
  }
  return &drives[minIndex];
}

Drive *find_drive_with_min_available_memory(Drive drives[], int count) {
  if (count <= 0) {
    fprintf(stderr, "No drives available.\n");
    exit(EXIT_FAILURE);
  }
  int minIndex = 0;
  int minAvailable = to_bits(drives[0].memoryAllocated - drives[0].memoryUsed, drives[0].unitType);
  for (int i = 1; i < count; i++) {
    int available = to_bits(drives[i].memoryAllocated - drives[i].memoryUsed, drives[i].unitType);
    if (available < minAvailable) {
      minAvailable = available;
      minIndex = i;
    }
  }
  return &drives[minIndex];
}

// Memory allocation adjustment functions
void increase_allocated_memory(Drive drives[], int count, char name, int amount) {
  for (int i = 0; i < count; i++) {
    if (drives[i].name == name) {
      drives[i].memoryAllocated += amount;
      return;
    }
  }
  fprintf(stderr, "Drive %c not found.\n", name);
}

void decrease_allocated_memory(Drive drives[], int count, char name, int amount) {
  for (int i = 0; i < count; i++) {
    if (drives[i].name == name) {
      if (drives[i].memoryAllocated - amount <= 0) {
        fprintf(stderr, "Drive %c can't have non-positive memory size.\n", name);
        exit(EXIT_FAILURE);
      }
      if (drives[i].memoryAllocated - amount < drives[i].memoryUsed) {
        fprintf(stderr, "Drive %c: allocated memory cannot be smaller than memory used.\n", name);
        exit(EXIT_FAILURE);
      }
      drives[i].memoryAllocated -= amount;
      return;
    }
  }
  fprintf(stderr, "Drive %c not found.\n", name);
}

// Sorting functions
void sort_drives(Drive drives[], int count, bool descending) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      int first = to_bits(drives[j].memoryAllocated, drives[j].unitType);
      int second = to_bits(drives[j + 1].memoryAllocated, drives[j + 1].unitType);
      if ((descending && first < second) || (!descending && first > second)) {
        Drive temp = drives[j];
        drives[j] = drives[j + 1];
        drives[j + 1] = temp;
      }
    }
  }
}

// Returns the nth largest drive (1-indexed) after sorting descending.
Drive *nth_biggest(Drive drives[], int count, int nth) {
  if (nth <= 0 || nth > count) {
    fprintf(stderr, "Invalid nth value.\n");
    exit(EXIT_FAILURE);
  }
  sort_drives(drives, count, true);
  return &drives[nth - 1];
}

int main(void) {

  Drive A = {'A', .memoryAllocated = 100, .memoryUsed = 100, BYTE};
  Drive B = {'B', .memoryAllocated = 200, .memoryUsed = 100, BYTE};
  Drive C = {'C', .memoryAllocated = 300, .memoryUsed = 150, BIT};
  Drive D = {'D', .memoryAllocated = 400, .memoryUsed = 200, BYTE};
  Drive E = {'E', .memoryAllocated = 500, .memoryUsed = 250, BIT};

  Drive drives[] = {A, B, C, D, E};
  int driveCount = sizeof(drives) / sizeof(drives[0]);

  printf("=== All Drives ===\n");
  print_all_drives(drives, driveCount);

  // Sorting drives by allocated memory (largest first)
  printf("=== Drives Sorted by Allocated Memory (>) ===\n");
  sort_drives(drives, driveCount, true);
  print_all_drives(drives, driveCount);

  // Find and print the drive with the maximum allocated memory.
  Drive *maxDrive = find_drive_with_max_memory(drives, driveCount);
  printf("=== Drive with Maximum Allocated Memory ===\n");
  print_drive(maxDrive);

  // Find and print the drive with the maximum available memory.
  Drive *maxAvailableDrive = find_drive_with_max_available_memory(drives, driveCount);
  printf("=== Drive with Maximum Available Memory ===\n");
  print_drive(maxAvailableDrive);

  // Example: Get the 2nd biggest drive.
  int nth = 2;
  Drive *nthDrive = nth_biggest(drives, driveCount, nth);
  printf("=== The %d. Biggest Drive by allocated memory ===\n", nth);
  print_drive(nthDrive);

  return 0;
}

// Konya
