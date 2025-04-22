#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::map<std::string, int *> vars;
int PC = 0;

struct Instr {
  char oper;
  int *var;
  union {
    int *var2;
    int i;
  } z;

  Instr(char o, const char *v, int i) : oper(o) {
    std::string name(v);
    if (!vars.count(name))
      vars[name] = new int(0);
    var = vars[name];
    z.i = i;
  }

  Instr(char o, const char *v, const char *v2) : oper(o) {
    std::string name1(v), name2(v2);
    if (!vars.count(name1))
      vars[name1] = new int(0);
    if (!vars.count(name2))
      vars[name2] = new int(0);
    var = vars[name1];
    z.var2 = vars[name2];
  }
};

std::vector<Instr> program;

void loadProgram(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Unable to open file: `" << filename << "`" << std::endl;
    exit(1);
  }

  std::string line;
  while (getline(file, line)) {
    std::istringstream iss(line);
    char op;
    std::string v1;
    std::string v2;
    int value;

    iss >> op >> v1 >> v2;
    if (v1.empty() || v2.empty())
      continue;

    if (isdigit(v2[0]) || v2[0] == '-') {
      value = stoi(v2);
      program.emplace_back(op, v1.c_str(), value);
    } else {
      program.emplace_back(op, v1.c_str(), v2.c_str());
    }
  }
}

void interpret() {
  while ((unsigned long)PC < program.size()) {
    Instr &inst = program[PC];
    switch (inst.oper) {
    case 'a':
      *inst.var = inst.z.i;
      break;
    case 'c':
      *inst.var = *inst.z.var2;
      break;
    case '+':
      *inst.var += *inst.z.var2;
      break;
    case '-':
      *inst.var -= *inst.z.var2;
      break;
    case '*':
      *inst.var *= *inst.z.var2;
      break;
    case '/':
      *inst.var /= *inst.z.var2;
      break;
    case '%':
      *inst.var %= *inst.z.var2;
      break;
    case 'g':
      if (*inst.var > 0) {
        PC += inst.z.i + 1;
        continue;
      }
      break;
    case 'e':
      if (*inst.var == 0) {
        PC += inst.z.i + 1;
        continue;
      }
      break;
    case 'w':
      std::cout << std::string(*inst.var, ' ') << *inst.z.var2;
      break;
    case 'x':
      if (*inst.var == *inst.z.var2) {
        std::cout << std::endl;
        return;
      }
      break;
    default:
      std::cerr << "Unknown instruction: " << inst.oper << std::endl;
      break;
    }
    PC++;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
    return 1;
  }

  std::cout << "Loading program `" << argv[1] << "`" << std::endl;
  std::cout << "----------------------------------------" << std::endl;

  loadProgram(argv[1]);
  interpret();
  return 0;
}

// Konya

// Expected output (Prvocisla1000):
/*
Loading program `./Code/2/jcp/hw/Prvocisla1000`
----------------------------------------
 2  3  5  7  11  13  17  19  23  29  31  37  41  43  47  53  59  61  67  71  73
79  83  89  97  101  103  107  109  113  127  131  137  139  149  151  157 163
167  173  179  181  191  193  197  199  211  223  227  229  233  239  241  251
257  263  269  271  277  281  283  293  307  311  313  317  331  337  347  349
353  359  367  373  379  383  389  397  401  409  419  421  431  433  439  443
449  457  461  463  467  479  487  491  499  503  509  521  523  541  547  557
563  569  571  577  587  593  599  601  607  613  617  619  631  641  643  647
653  659  661  673  677  683  691  701  709  719  727  733  739  743  751  757
761  769  773  787  797  809  811  821  823  827  829  839  853  857  859  863
877  881  883  887  907  911  919  929  937  941  947  953  967  971  977  983
991  997
*/

// Expected output (Faktorial5):

/*
Loading program `./Code/2/jcp/hw/Faktorial5`
----------------------------------------
  120
*/
