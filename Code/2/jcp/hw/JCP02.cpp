#include <iomanip>  // For hex, dec, uppercase, setw
#include <iostream> // For std::cout,cin

// To print instead of " " for non-printable characters
#define NULL_CHAR " " // "Ø"

void print_hex_ascii_table() {
  // Table header
  std::cout << "      ";
  for (int i = 0; i < 16; i++) {
    std::cout << std::setw(2) << std::hex << std::uppercase << i << " ";
  }
  std::cout << std::endl;
  std::cout << "    ---------------------------------------------------"
            << std::endl;

  // Table body
  for (int i = 32; i < 128; i += 16) {
    std::cout << std::setw(3) << std::hex << std::uppercase << i << " | ";
    for (int j = 0; j < 16; j++) {
      int ascii = i + j;
      if (ascii >= 32 && ascii <= 126) {
        std::cout << std::setw(2) << char(ascii) << " ";
      } else {
        std::cout << NULL_CHAR << "  "; // Character and alignment
      }
    }
    std::cout << "|" << std::endl;
  }

  // Table footer
  std::cout << "    ---------------------------------------------------"
            << std::endl;
}

void print_dec_ascii_table() {
  // Table header
  std::cout << "      ";
  for (int i = 0; i < 10; i++) {
    std::cout << std::setw(2) << i << " ";
  }
  std::cout << std::endl;
  std::cout << "    ---------------------------------" << std::endl;

  // Table body
  for (int i = 30; i < 128; i += 10) {
    std::cout << std::setw(3) << std::dec << i << " | ";
    for (int j = 0; j < 10; j++) {
      int ascii = i + j;
      if (ascii >= 32 && ascii <= 126) {
        std::cout << std::setw(2) << char(ascii) << " ";
      } else {
        std::cout << NULL_CHAR << "  "; // Character and alignment
      }
    }
    std::cout << "|" << std::endl;
  }

  // Table footer
  std::cout << "    ---------------------------------" << std::endl;
}

int main() {
  std::cout << "Choose ASCII table format:" << std::endl;
  std::cout << "[1] Hexadecimal" << std::endl;
  std::cout << "[2] Decimal" << std::endl;
  std::cout << "[*] Both" << std::endl;

  char choice;
  std::cout << "Chosen: ";

  std::cin.getline(&choice, 2);
  std::cout << std::endl;

  switch (choice) {
  case '1':
    std::cout << "ASCII Table (Hexadecimal):" << std::endl;
    print_hex_ascii_table();
    break;
  case '2':
    std::cout << "ASCII Table (Decimal):" << std::endl;
    print_dec_ascii_table();
    break;
  default:
    std::cout << "ASCII Table (Hexadecimal):" << std::endl;
    print_hex_ascii_table();
    std::cout << std::endl;
    std::cout << "ASCII Table (Decimal):" << std::endl;
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
