#include <climits>
#include <iostream>

using namespace std;

class Structure {
public:
  virtual bool add(int) = 0;
  virtual bool remove(int &) = 0;
  virtual void print() = 0;
  virtual ~Structure() {}
};

class Stack : public Structure {
private:
  int *array;
  int capacity;
  int head = -1;

public:
  Stack(int capacity) : capacity(capacity) { array = new int[capacity]; }

  ~Stack() { delete[] array; }

  bool add(int value) override {
    if (head >= capacity - 1)
      return false;

    head++;
    array[head] = value;
    return true;
  }

  bool remove(int &value) override {
    if (head < 0)
      return false;
    value = array[head--];
    return true;
  }

  void print() override {
    cout << "[";
    for (int i = 0; i <= head; i++) {
      cout << array[i];
      if (i < head) {
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
};

int AddNumbers(Structure &s, int array[], int count) {
  int successfullyAdded = 0;
  for (int i = 0; i < count; i++) {
    if (s.add(array[i])) {
      successfullyAdded++;
    } else {
      break;
    }
  }
  return successfullyAdded;
}

int RemoveAndPrint(Structure &s, int count = INT_MAX) {
  int successfullyRemoved = 0, value;
  while (successfullyRemoved < count && s.remove(value)) {
    cout << value << " ";
    successfullyRemoved++;
  }
  cout << endl;
  return successfullyRemoved;
}

// Main program
int main() {
  int stack_size = 6;

  int actually_added = 0;
  int actually_removed = 0;

  Stack S = Stack(stack_size);

  int array1[] = {5, 9, 1, 0, 4};
  int array1_size = sizeof(array1) / sizeof(array1[0]);

  cout << "Stack of size: " << stack_size << endl;

  S.print();

  cout << "Adding 5 elements: " << endl;
  actually_added = AddNumbers(S, array1, array1_size);
  cout << "Actually added: " << actually_added << endl;

  S.print();

  cout << "Removing 3 elements: " << endl;
  actually_removed = RemoveAndPrint(S, 3);
  cout << "Actually removed: " << actually_removed << endl;

  S.print();

  cout << endl;

  int array2[] = {3, 6, 7, 5, 2, 8};
  int array2_size = sizeof(array2) / sizeof(array2[0]);

  S.print();

  cout << "Adding 6 elements: " << endl;
  actually_added = AddNumbers(S, array2, array2_size);
  cout << "Actually added: " << actually_added << endl;

  S.print();

  cout << "Removing all elements: " << endl;
  actually_removed = RemoveAndPrint(S);
  cout << "Actually removed: " << actually_removed << endl;

  S.print();

  return 0;
}
