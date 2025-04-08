#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

enum Pohlavi { MUZ = 1, ZENA, BEZ };

struct Jmeno {
  std::string j;
  Pohlavi p = BEZ;
};

Jmeno J[134];

bool operator<(const Jmeno &a, const Jmeno &b) {
  if (a.p != b.p)
    return a.p == ZENA;
  return a.j < b.j;
}

int readFile(const std::string &fileName) {
  std::ifstream file(fileName, std::ios::binary);
  if (!file) {
    std::cerr << "Error opening file `" << fileName << "`" << std::endl;
    return 0;
  }

  int count = 0;
  while (true) {
    unsigned char delka;
    if (!file.read((char *)(&delka), 1))
      break;

    Pohlavi p;
    if (delka >= 50) {
      delka -= 50;
      p = ZENA;
    } else {
      p = MUZ;
    }

    char buffer[50];
    if (!file.read(buffer, delka))
      break;
    std::string jmeno(buffer, delka);

    bool existuje = false;
    for (int i = 1; i < count; i++) {
      if (J[i].j == jmeno) {
        existuje = true;
        break;
      }
    }

    if (!existuje && count < 134) {
      J[count].j = jmeno;
      J[count].p = p;
      count++;
    }
  }

  file.close();
  return count;
}

void Vypsat(const Jmeno pole[], int n, Pohlavi filtr = BEZ) {
  int count = 0;
  for (int i = 1; i < n; i++) {
    if (filtr == BEZ || pole[i].p == filtr) {
      std::cout << pole[i].j << " ";
      count++;
      if (count % 10 == 0)
        std::cout << std::endl;
    }
  }
  if (count % 10 != 0)
    std::cout << std::endl;
}

int main() {

  int name_count = readFile("Jmena-08");

  if (name_count == 0) {
    std::cerr << "No names found or error reading file." << std::endl;
    return 1;
  }

  std::cout << "All before sort: " << std::endl;
  std::cout << std::endl;

  Vypsat(J, name_count);

  std::cout << std::endl;

  std::cout << "First before sort: " << J[0].j << std::endl;

  std::cout << std::endl;

  std::cout << "Sorting..." << std::endl;

  std::cout << std::endl;

  std::sort(J, J + name_count);

  std::cout << "All after sort: " << std::endl;
  std::cout << std::endl;
  Vypsat(J, name_count);

  std::cout << std::endl;

  std::cout << "First after sort: " << J[0].j << std::endl;

  std::cout << std::endl;

  std::cout << "Women: " << std::endl;
  std::cout << std::endl;

  Vypsat(J, name_count, ZENA);

  std::cout << std::endl;

  std::cout << "Men: " << std::endl;
  std::cout << std::endl;

  Vypsat(J, name_count, MUZ);

  return 0;
}

// Konya

// Expected output:
/*
All before sort:

Marie Jan Jana Sabina Petr Josef Pavel Jaroslav Martin Miroslav
Eva Anna Hana Karel Lenka Milan Michal Alena Petra Irena
Lucie Jaroslava Ludmila Helena David Ladislav Jitka Martina Jakub Veronika
Jarmila Stanislav Michaela Ivana Roman Monika Adam Tereza Zuzana Radek
Vlasta Marcela Marek Dagmar Dana Daniel Marta Miroslava Barbora Pavla
Miloslav Olga Andrea Iveta Filip Blanka Milada Ivan Zdenka Libor
Renata Rudolf Vlastimil Nikola Gabriela Radka Simona Milena Miloslava Iva
Daniela Patrik Bohumil Denisa Robert Aneta Ilona Dominik Stanislava Emilie
Radim Richard Kamila Ivo Rostislav Vladislav Bohuslav Alois Vit Kamil
Vendula Bohumila Viktor Emil Eduard Dominika Marcel Julie Antonie Alice
Peter Dalibor Kristina Otakar Karla Hedvika Alexandra Silvie Nela Vratislav
Leona Jolana Margita Bohuslava Radovan Linda Igor

First before sort: Marie

Sorting...

All after sort:

Alena Alexandra Alice Andrea Aneta Anna Antonie Barbora Blanka Bohumila
Bohuslava Dagmar Dana Daniela Denisa Dominika Emilie Eva Gabriela Hana
Hedvika Helena Ilona Irena Iva Ivana Iveta Jana Jarmila Jaroslava
Jitka Jolana Julie Kamila Karla Kristina Lenka Leona Linda Lucie
Ludmila Marcela Margita Marie Marta Martina Michaela Milada Milena Miloslava
Miroslava Monika Nela Nikola Olga Pavla Petra Radka Renata Sabina
Silvie Simona Stanislava Tereza Vendula Veronika Vlasta Zdenka Zuzana Adam
Alois Bohumil Bohuslav Dalibor Daniel David Dominik Eduard Emil Filip
Igor Ivan Ivo Jakub Jan Jaroslav Josef Kamil Karel Ladislav
Libor Marcel Marek Martin Michal Milan Miloslav Miroslav Otakar Patrik
Pavel Peter Petr Radek Radim Radovan Richard Robert Roman Rostislav
Rudolf Stanislav Viktor Vit Vladislav Vlastimil Vratislav

First after sort: Alena

Women:

Alena Alexandra Alice Andrea Aneta Anna Antonie Barbora Blanka Bohumila
Bohuslava Dagmar Dana Daniela Denisa Dominika Emilie Eva Gabriela Hana
Hedvika Helena Ilona Irena Iva Ivana Iveta Jana Jarmila Jaroslava
Jitka Jolana Julie Kamila Karla Kristina Lenka Leona Linda Lucie
Ludmila Marcela Margita Marie Marta Martina Michaela Milada Milena Miloslava
Miroslava Monika Nela Nikola Olga Pavla Petra Radka Renata Sabina
Silvie Simona Stanislava Tereza Vendula Veronika Vlasta Zdenka Zuzana

Men:

Adam Alois Bohumil Bohuslav Dalibor Daniel David Dominik Eduard Emil
Filip Igor Ivan Ivo Jakub Jan Jaroslav Josef Kamil Karel
Ladislav Libor Marcel Marek Martin Michal Milan Miloslav Miroslav Otakar
Patrik Pavel Peter Petr Radek Radim Radovan Richard Robert Roman
Rostislav Rudolf Stanislav Viktor Vit Vladislav Vlastimil Vratislav
*/
