#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum Jednotka { KUS = 1, KG, LITR };

union Mnozstvi {
  int kus;
  float kg;
  float litr;
};

struct Potravina {
  string nazev;
  Jednotka jednotka;
  Mnozstvi mnozstvi;
};

Jednotka slovniNaJednotku(const string &s) {
  if (s == "kus")
    return KUS;
  if (s == "kg")
    return KG;
  if (s == "litr")
    return LITR;
  cout << s << endl;
  throw invalid_argument("Unknown unit: `" + s + "`");
}

float ziskatHodnotu(const Potravina &p) {
  if (p.jednotka == KUS)
    return p.mnozstvi.kus;
  if (p.jednotka == KG)
    return p.mnozstvi.kg;
  return p.mnozstvi.litr;
}

void nastavitHodnotu(Potravina &p, float hodnota) {
  if (p.jednotka == KUS)
    p.mnozstvi.kus = static_cast<int>(hodnota);
  else if (p.jednotka == KG)
    p.mnozstvi.kg = hodnota;
  else
    p.mnozstvi.litr = hodnota;
}

string jednotkaNaString(Jednotka j) {
  if (j == KUS)
    return "kus";
  if (j == KG)
    return "kg";
  return "litr";
}

void aktualizujZasoby(vector<Potravina> &V, const string &nazev,
                      Jednotka jednotka, float hodnota) {
  auto it = find_if(V.begin(), V.end(),
                    [&](const Potravina &p) { return p.nazev == nazev; });

  if (it == V.end()) {
    Potravina p;
    p.nazev = nazev;
    p.jednotka = jednotka;
    nastavitHodnotu(p, hodnota);
    V.push_back(p);
  } else {
    if (it->jednotka != jednotka)
      return;
    float novaHodnota = ziskatHodnotu(*it) + hodnota;
    if (novaHodnota <= 0.0001f)
      V.erase(it);
    else
      nastavitHodnotu(*it, novaHodnota);
  }
}

void vypisZasoby(const vector<Potravina> &V) {
  for (const auto &p : V) {
    cout << setw(12) << left << p.nazev << setw(6) << left
         << jednotkaNaString(p.jednotka) << fixed << setprecision(2);
    if (p.jednotka == KUS)
      cout << p.mnozstvi.kus << endl;
    else if (p.jednotka == KG)
      cout << p.mnozstvi.kg << endl;
    else
      cout << p.mnozstvi.litr << endl;
  }
}

int main() {
  char filename[] = "Pohyb";

  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Error: Unable to open file `" << filename << "`" << endl;
    return 1;
  }

  vector<Potravina> V;
  string radek;

  while (getline(in, radek)) {
    istringstream ss(radek);
    string nazev, jednotkaStr;
    float hodnota;
    ss >> nazev >> jednotkaStr >> hodnota;
    try {
      Jednotka j = slovniNaJednotku(jednotkaStr);
      aktualizujZasoby(V, nazev, j, hodnota);
    } catch (const exception &e) {
      cerr << "Line error: " << radek << " (" << e.what() << ")" << endl;
    }
  }

  sort(V.begin(), V.end(), [](const Potravina &a, const Potravina &b) {
    return a.nazev < b.nazev;
  });

  cout << "Sorted by name:" << endl;
  vypisZasoby(V);

  cout << "----------------------------------------" << endl;

  sort(V.begin(), V.end(), [](const Potravina &a, const Potravina &b) {
    if (a.jednotka != b.jednotka)
      return a.jednotka < b.jednotka;
    return a.nazev < b.nazev;
  });

  cout << "Sorted by unit and name:" << endl;
  vypisZasoby(V);
}

// Konya

// Expected output:
/*
Sorted by name:
brambory    kg    31.50
chleb       kg    15.50
cokolada    kus   8
cukr        kg    6.50
fazole      kg    4.50
kava        kg    8.50
kmin        kg    0.06
maso        kg    12.70
meloun      kg    19.30
merunky     kg    4.50
mleko       litr  24.50
mouka       kg    9.00
pivo        litr  26.00
rohlik      kus   41
salam       kg    6.20
sirup       litr  18.50
----------------------------------------
Sorted by unit and name:
cokolada    kus   8
rohlik      kus   41
brambory    kg    31.50
chleb       kg    15.50
cukr        kg    6.50
fazole      kg    4.50
kava        kg    8.50
kmin        kg    0.06
maso        kg    12.70
meloun      kg    19.30
merunky     kg    4.50
mouka       kg    9.00
salam       kg    6.20
mleko       litr  24.50
pivo        litr  26.00
sirup       litr  18.50
*/
