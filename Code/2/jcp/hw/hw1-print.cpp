#include <iostream> // For cout,cin
#include <print>    // For print and println (requires C++23)

// To std::print instead of " " for non-printable characters
#define NULL_CHAR " " // "Ø"

void print_hex_ascii_table() {
  // Table header
  std::print("      ");
  for (int i = 0; i < 16; i++) {
    std::print("{:X}  ", i);
  }
  std::println("");
  std::println("    ---------------------------------------------------");

  // Table body
  for (int i = 32; i < 128; i += 16) {
    std::print("{:3X} | ", i);
    for (int j = 0; j < 16; j++) {
      int ascii = i + j;
      if (ascii >= 32 && ascii <= 126) {
        std::print("{:c}  ", ascii);
      }
      else {
        std::print("{}", NULL_CHAR); // Character
        std::print("  ");            // Alignment
      }
    }
    std::println("|");
  }

  // Table footer
  std::println("    ---------------------------------------------------");
}

void print_dec_ascii_table() {
  // Table header
  std::print("      ");
  for (int i = 0; i < 10; i++) {
    std::print("{}  ", i);
  }

  std::println("");
  std::println("    ---------------------------------");

  // Table body
  for (int i = 30; i < 128; i += 10) {
    std::print("{:3d} | ", i);
    for (int j = 0; j < 10; j++) {
      int ascii = i + j;
      if (ascii >= 32 && ascii <= 126) {
        std::print("{:c}  ", ascii);
      }
      else {
        std::print("{}", NULL_CHAR); // Character
        std::print("  ");            // Alignment
      }
    }
    std::println("|");
  }

  // Table footer
  std::println("    ---------------------------------");
}

int main() {
  std::println("Choose ASCII table format:");
  std::println("[1] Hexadecimal");
  std::println("[2] Decimal");
  std::println("[*] Both");

  char choice;
  std::print("Chosen: ");

  std::cin.getline(&choice, 2);
  std::println("\n");

  switch (choice) {
  case '1':
    std::println("ASCII Table (Hexadecimal):\n");
    print_hex_ascii_table();
    break;
  case '2':
    std::println("ASCII Table (Decimal):\n");
    print_dec_ascii_table();
    break;
  default:
    std::println("ASCII Table (Hexadecimal):\n");
    print_hex_ascii_table();
    std::println("\n");
    std::println("ASCII Table (Decimal):\n");
    print_dec_ascii_table();
    break;
  }

  return 0;
}

// Konya

// Expected output:
/*
Choose ASCII table format:
[1] Hexadecimal
[2] Decimal
[*] Both
Chosen: 3

ASCII Table (Hexadecimal):
       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    ---------------------------------------------------
 20 |     !  "  #  $  %  &  '  (  )  *  +  ,  -  .  / |
 30 |  0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ? |
 40 |  @  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O |
 50 |  P  Q  R  S  T  U  V  W  X  Y  Z  [  \  ]  ^  _ |
 60 |  `  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o |
 70 |  p  q  r  s  t  u  v  w  x  y  z  {  |  }  ~    |
    ---------------------------------------------------

ASCII Table (Decimal):
       0  1  2  3  4  5  6  7  8  9
    ---------------------------------
 30 |           !  "  #  $  %  &  ' |
 40 |  (  )  *  +  ,  -  .  /  0  1 |
 50 |  2  3  4  5  6  7  8  9  :  ; |
 60 |  <  =  >  ?  @  A  B  C  D  E |
 70 |  F  G  H  I  J  K  L  M  N  O |
 80 |  P  Q  R  S  T  U  V  W  X  Y |
 90 |  Z  [  \  ]  ^  _  `  a  b  c |
100 |  d  e  f  g  h  i  j  k  l  m |
110 |  n  o  p  q  r  s  t  u  v  w |
120 |  x  y  z  {  |  }  ~          |
    ---------------------------------
*/
