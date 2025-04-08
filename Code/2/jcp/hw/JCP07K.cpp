#include <fstream>
#include <iostream>
#include <string>

template <class P, class D> class PFronta {
  struct Prvek {
    P priorita;
    D data;
    Prvek(P p, const D &d) : priorita(p), data(d) {}
  };

  Prvek **pole;
  unsigned kapacita;
  unsigned velikost;

  void zvetsiKapacitu() {
    unsigned novaKapacita = kapacita * 2;
    Prvek **novePole = new Prvek *[novaKapacita];
    for (unsigned i = 0; i < velikost; i++)
      novePole[i] = pole[i];
    delete[] pole;
    pole = novePole;
    kapacita = novaKapacita;
  }

public:
  PFronta(unsigned kap) : kapacita(kap), velikost(0) {
    pole = new Prvek *[kapacita];
  }

  ~PFronta() {
    for (unsigned i = 0; i < velikost; i++)
      delete pole[i];
    delete[] pole;
  }

  void vlozit(const P &priorita, const D &data) {
    if (velikost == kapacita)
      zvetsiKapacitu();
    unsigned i = velikost;
    while (i > 0 && pole[i - 1]->priorita < priorita) {
      pole[i] = pole[i - 1];
      i--;
    }
    pole[i] = new Prvek(priorita, data);
    velikost++;
  }

  bool odebrat(D &data) {
    if (velikost == 0)
      return false;
    data = pole[0]->data;
    delete pole[0];
    for (unsigned i = 1; i < velikost; i++)
      pole[i - 1] = pole[i];
    velikost--;
    return true;
  }

  unsigned operator+() const { return kapacita; }
};

int main() {
  char file[] = "Jmena";
  std::ifstream soubor(file, std::ios::binary);
  if (!soubor) {
    std::cerr << "Error opening file `" << file << "`" << std::endl;
    return 1;
  }

  PFronta<unsigned char, std::string> fronta(5);

  while (!soubor.eof()) {
    unsigned char priorita, delka;
    if (!soubor.read(reinterpret_cast<char *>(&priorita), 1) ||
        !soubor.read(reinterpret_cast<char *>(&delka), 1))
      break;

    std::string jmeno(delka, '\0');
    soubor.read(&jmeno[0], delka);

    fronta.vlozit(priorita, jmeno);
  }

  soubor.close();

  std::string jmeno;
  int pocitadlo = 0;
  while (fronta.odebrat(jmeno)) {
    std::cout << jmeno << " ";
    if (++pocitadlo % 5 == 0)
      std::cout << "\n";
  }

  return 0;
}

// Konya

// Expected output:
/*
Marek Nikola Pavel Irena Roman
Lucie Pavla Jana Hana Jan
Zuzana Eva Petr Tereza
*/
