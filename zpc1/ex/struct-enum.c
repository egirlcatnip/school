#include <stdio.h>

enum position { left, right, center };

typedef struct {
  char full_name[255];
  int wage;
} Person;

void print_pos(enum position type) {
  switch (type) {
  case left: {
    printf("Left\n");
    break;
  }
  case right: {
    printf("Right\n");
    break;
  }
  case center: {
    printf("Center\n");
    break;
  }
  }
};

void print_person(Person person) {
  if (person.wage > 10000) {
    printf("Person named %s is rich\n", person.full_name);
  }
  else if (person.wage < 0) {
    printf("Person named %s is loosing weight\n", person.full_name);
  }
  else {
    printf("Person named %s is middle class\n", person.full_name);
  }
};

int main(void) {

  print_pos(left);
  print_pos(center);
  print_pos(right);

  Person person = {
      .full_name = "Tom Dom",
      .wage = 50,
  };

  print_person(person);

  return 0;
}

/*
//
*/