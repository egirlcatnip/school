#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { BYTE, BIT } Unit;

typedef struct {
  char name;
  float totalMemory;
  float usedMemory;
  Unit unitType;
} Drive;

static inline float bit_to_byte(float bits) { return bits / 8.0; }
static inline float byte_to_bit(float bytes) { return bytes * 8.0; }

static inline float to_bytes(float memory, Unit unit) {
  return (unit == BIT) ? bit_to_byte(memory) : memory;
}

static inline float to_bits(float memory, Unit unit) {
  return (unit == BYTE) ? byte_to_bit(memory) : memory;
}

char drive_memory_unit(Drive d) { return (d.unitType == BYTE) ? 'B' : 'b'; }

void print_drive(const Drive *d) {
  printf("Drive %c:\n", d->name);

  printf("  Total memory:     %.2f %c\t (%07.2f B %04.0f b)\n", d->totalMemory,
         drive_memory_unit(*d), to_bytes(d->totalMemory, d->unitType),
         to_bits(d->totalMemory, d->unitType));

  printf("  Used memory:      %.2f %c\t (%07.2f B %04.0f b)\n", d->usedMemory,
         drive_memory_unit(*d), to_bytes(d->usedMemory, d->unitType),
         to_bits(d->usedMemory, d->unitType));

  float remaining = d->totalMemory - d->usedMemory;
  printf("  Remaining memory: %.2f %c\t (%07.2f B %04.0f b)\n", remaining,
         drive_memory_unit(*d), to_bytes(remaining, d->unitType),
         to_bits(remaining, d->unitType));
}

void print_all_drives(const Drive drives[], int count) {
  for (int i = 0; i < count; i++) {
    print_drive(&drives[i]);
    printf("\n");
  }
}

Drive *find_drive_with_max_memory(Drive drives[], int count) {
  int maxIndex = 0;
  float maxValue = to_bytes(drives[0].totalMemory, drives[0].unitType);

  for (int i = 1; i < count; i++) {
    float current = to_bytes(drives[i].totalMemory, drives[i].unitType);
    if (current > maxValue) {
      maxValue = current;
      maxIndex = i;
    }
  }
  return &drives[maxIndex];
}

Drive *find_drive_with_max_available_memory(Drive drives[], int count) {
  int maxIndex = 0;
  float maxAvailable = to_bytes(drives[0].totalMemory - drives[0].usedMemory,
                                drives[0].unitType);

  for (int i = 1; i < count; i++) {
    float available = to_bytes(drives[i].totalMemory - drives[i].usedMemory,
                               drives[i].unitType);
    if (available > maxAvailable) {
      maxAvailable = available;
      maxIndex = i;
    }
  }
  return &drives[maxIndex];
}

void increase_allocated_memory(Drive drives[], int count, char name,
                               float amount, Unit unit) {
  for (int i = 0; i < count; i++) {
    if (drives[i].name == name) {
      float adjustedAmount =
          (drives[i].unitType == unit)
              ? amount
              : (unit == BIT ? bit_to_byte(amount) : byte_to_bit(amount));

      float newUsedMemory = drives[i].usedMemory + adjustedAmount;
      if (newUsedMemory > drives[i].totalMemory) {
        fprintf(stderr, "Error: Not enough space on drive %c.\n", name);
        return;
      }
      drives[i].usedMemory = newUsedMemory;
      return;
    }
  }
  fprintf(stderr, "Drive %c not found.\n", name);
}

void decrease_allocated_memory(Drive drives[], int count, char name,
                               float amount, Unit unit) {
  for (int i = 0; i < count; i++) {
    if (drives[i].name == name) {
      float adjustedAmount =
          (drives[i].unitType == unit)
              ? amount
              : (unit == BIT ? bit_to_byte(amount) : byte_to_bit(amount));

      float newUsedMemory = drives[i].usedMemory - adjustedAmount;
      if (newUsedMemory < 0) {
        fprintf(stderr, "Error: Used memory cannot be negative on drive %c.\n",
                name);
        return;
      }
      drives[i].usedMemory = newUsedMemory;
      return;
    }
  }
  fprintf(stderr, "Drive %c not found.\n", name);
}

void sort_drives(Drive drives[], int count) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      float first = to_bytes(drives[j].totalMemory, drives[j].unitType);
      float second =
          to_bytes(drives[j + 1].totalMemory, drives[j + 1].unitType);
      if (first < second) {
        Drive temp = drives[j];
        drives[j] = drives[j + 1];
        drives[j + 1] = temp;
      }
    }
  }
}

Drive *ith_biggest(Drive drives[], int count, int i) {
  if (i <= 0 || i > count) {
    fprintf(stderr, "Error: Invalid i-th value.\n");
    exit(EXIT_FAILURE);
  }
  sort_drives(drives, count);
  return &drives[i - 1];
}

int main(void) {
  Drive drives[] = {{'A', 100, 20, BYTE},
                    {'B', 200, 90, BYTE},
                    {'C', 300, 50, BIT},
                    {'D', 400, 2, BYTE},
                    {'E', 500, 480, BIT}};
  int driveCount = sizeof(drives) / sizeof(drives[0]);

  printf("=== Drives Before Sorting ===\n");
  print_all_drives(drives, driveCount);

  sort_drives(drives, driveCount);
  printf("=== Drives After Sorting ===\n");
  print_all_drives(drives, driveCount);

  printf("=== Drive with Maximum Total Memory ===\n");
  print_drive(find_drive_with_max_memory(drives, driveCount));

  printf("\n");

  printf("=== Drive with Maximum Available Memory ===\n");
  print_drive(find_drive_with_max_available_memory(drives, driveCount));

  printf("\n");

  int nth = 2;
  printf("=== The %d. Biggest Drive ===\n", nth);
  print_drive(ith_biggest(drives, driveCount, nth));

  return 0;
}

// Konya

// Expected outcome:

/*
=== Drives Before Sorting ===
Drive A:
  Total memory:     100.00 B	 (0100.00 B 0800 b)
  Used memory:      20.00 B	 (0020.00 B 0160 b)
  Remaining memory: 80.00 B	 (0080.00 B 0640 b)

Drive B:
  Total memory:     200.00 B	 (0200.00 B 1600 b)
  Used memory:      90.00 B	 (0090.00 B 0720 b)
  Remaining memory: 110.00 B	 (0110.00 B 0880 b)

Drive C:
  Total memory:     300.00 b	 (0037.50 B 0300 b)
  Used memory:      50.00 b	 (0006.25 B 0050 b)
  Remaining memory: 250.00 b	 (0031.25 B 0250 b)

Drive D:
  Total memory:     400.00 B	 (0400.00 B 3200 b)
  Used memory:      2.00 B	 (0002.00 B 0016 b)
  Remaining memory: 398.00 B	 (0398.00 B 3184 b)

Drive E:
  Total memory:     500.00 b	 (0062.50 B 0500 b)
  Used memory:      480.00 b	 (0060.00 B 0480 b)
  Remaining memory: 20.00 b	 (0002.50 B 0020 b)

=== Drives After Sorting ===
Drive D:
  Total memory:     400.00 B	 (0400.00 B 3200 b)
  Used memory:      2.00 B	 (0002.00 B 0016 b)
  Remaining memory: 398.00 B	 (0398.00 B 3184 b)

Drive B:
  Total memory:     200.00 B	 (0200.00 B 1600 b)
  Used memory:      90.00 B	 (0090.00 B 0720 b)
  Remaining memory: 110.00 B	 (0110.00 B 0880 b)

Drive A:
  Total memory:     100.00 B	 (0100.00 B 0800 b)
  Used memory:      20.00 B	 (0020.00 B 0160 b)
  Remaining memory: 80.00 B	 (0080.00 B 0640 b)

Drive E:
  Total memory:     500.00 b	 (0062.50 B 0500 b)
  Used memory:      480.00 b	 (0060.00 B 0480 b)
  Remaining memory: 20.00 b	 (0002.50 B 0020 b)

Drive C:
  Total memory:     300.00 b	 (0037.50 B 0300 b)
  Used memory:      50.00 b	 (0006.25 B 0050 b)
  Remaining memory: 250.00 b	 (0031.25 B 0250 b)

=== Drive with Maximum Total Memory ===
Drive D:
  Total memory:     400.00 B	 (0400.00 B 3200 b)
  Used memory:      2.00 B	 (0002.00 B 0016 b)
  Remaining memory: 398.00 B	 (0398.00 B 3184 b)

=== Drive with Maximum Available Memory ===
Drive D:
  Total memory:     400.00 B	 (0400.00 B 3200 b)
  Used memory:      2.00 B	 (0002.00 B 0016 b)
  Remaining memory: 398.00 B	 (0398.00 B 3184 b)

=== The 2. Biggest Drive ===
Drive B:
  Total memory:     200.00 B	 (0200.00 B 1600 b)
  Used memory:      90.00 B	 (0090.00 B 0720 b)
  Remaining memory: 110.00 B	 (0110.00 B 0880 b)
*/
