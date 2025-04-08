#include <cctype>
#include <cfloat>
#include <cstring>
#include <iostream>
#include <ostream>

struct Zbozi {
  char *nazev;
  float cena;

  Zbozi(const char *name, float price) : cena(price) {
    nazev = new char[strlen(name) + 1];
    strcpy(nazev, name);
  }

  Zbozi() : nazev(nullptr), cena(0.0f) {}

  ~Zbozi() { delete[] nazev; }
};

typedef Zbozi *ZboziP;

class Cenik {
  ZboziP *zbozi;
  unsigned capacity;
  unsigned count;

  static bool equalNames(const char *a, const char *b) {
    if (strlen(a) != strlen(b))
      return false;
    for (unsigned i = 0; a[i] && b[i]; i++) {
      if (std::tolower(a[i]) != std::tolower(b[i]))
        return false;
    }
    return true;
  }

public:
  Cenik(unsigned size = 10) : capacity(size), count(0) {
    zbozi = new ZboziP[capacity]{nullptr};
  }

  ~Cenik() {
    for (unsigned i = 0; i < count; i++)
      delete zbozi[i];
    delete[] zbozi;
  }

  int operator()(const char *name, float price) {
    for (unsigned i = 0; i < count; i++) {
      if (equalNames(zbozi[i]->nazev, name)) {
        zbozi[i]->cena = price;
        return -1;
      }
    }
    if (count < capacity) {
      zbozi[count++] = new Zbozi(name, price);
      return 1;
    }
    return 0;
  }

  bool operator()(const char *name) {
    for (unsigned i = 0; i < count; i++) {
      if (equalNames(zbozi[i]->nazev, name)) {
        delete zbozi[i];
        for (unsigned j = i; j < count - 1; j++) {
          zbozi[j] = zbozi[j + 1];
        }
        zbozi[--count] = nullptr;
        return true;
      }
    }
    return false;
  }

  float operator[](const char *name) const {
    for (unsigned i = 0; i < count; i++) {
      if (equalNames(zbozi[i]->nazev, name))
        return zbozi[i]->cena;
    }
    return FLT_MIN;
  }

  const Zbozi *operator[](unsigned index) const {
    return (index < count) ? zbozi[index] : nullptr;
  }

  unsigned operator+() const { return count; }
};

const char *return_value(int res) {
  switch (res) {
  case 1:
    return "Přidáno";
  case -1:
    return "Změna ceny";
  default:
    return "Nepodařilo se přidat";
  }
}

int main() {
  Cenik cenik(5);
  int res;

  std::cout << "Přidání zboží:\n";

  res = cenik("Meloun", 50.0f);
  std::cout << "Meloun - " << cenik["Meloun"] << " Kč - " << return_value(res)
            << std::endl;

  res = cenik("Jablko", 30.0f);
  std::cout << "Jablko - " << cenik["Jablko"] << " Kč - " << return_value(res)
            << std::endl;

  res = cenik("Banan", 20.0f);
  std::cout << "Banan - " << cenik["Banan"] << " Kč - " << return_value(res)
            << std::endl;

  std::cout << std::endl;

  res = cenik("Meloun", 60.0f);
  std::cout << "Meloun - " << cenik["Meloun"] << " Kč - " << return_value(res)
            << std::endl;

  std::cout << "\nPočet položek v ceníku: " << +cenik << std::endl;

  std::cout << std::endl;

  std::cout << "Vyhledání cen";
  std::cout << "Cena Melounu: " << cenik["MELOUN"] << " Kč\n";
  std::cout << "Cena Jablka: " << cenik["jAbLkO"] << " Kč\n";
  std::cout << "Cena Hrušky: " << cenik["Hruska"] << " Kč\n";

  std::cout << std::endl;

  std::cout << "Smazání zboží:";
  std::cout << "Odstranění Jablka: "
            << (cenik("Jablko") ? "Úspěšné" : "Neúspěšné") << std::endl;
  std::cout << "Odstranění Hrušky: "
            << (cenik("Hruska") ? "Úspěšné" : "Neúspěšné") << std::endl;

  std::cout << "Počet položek v ceníku po smazání: " << +cenik << std::endl;

  std::cout << std::endl;

  std::cout << "Výpis všech položek:" << std::endl;

  for (unsigned i = 0; i < +cenik; i++) {
    const Zbozi *z = cenik[i];
    if (z) {
      std::cout << z->nazev << " - " << z->cena << " Kč" << std::endl;
    }
  }

  return 0;
}
