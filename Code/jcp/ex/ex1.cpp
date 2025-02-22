#include <print>

using namespace std;

int main() {
  int x = 42;
  int *ptr = &x;

  printf("%p\n", ptr);
  println("{:0>16X}", (uintptr_t)ptr);

  return 0;
}
