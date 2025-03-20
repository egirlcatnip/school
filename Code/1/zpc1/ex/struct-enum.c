#include <stdio.h>

typedef enum { LEFT, RIGHT, CENTER } position;

typedef struct {
  char full_name[255];
  int wage;
} Person;

void print_pos(position type) {
  switch (type) {
  case LEFT: {
    printf("Left\n");
    break;
  }
  case RIGHT: {
    printf("Right\n");
    break;
  }
  case CENTER: {
    printf("Center\n");
    break;
  }
  }
};

void print_person(Person person) {
  if (person.wage > 10000) {
    printf("Person named %s is rich\n", person.full_name);
  } else if (person.wage < 0) {
    printf("Person named %s is loosing weight\n", person.full_name);
  } else {
    printf("Person named %s is middle class\n", person.full_name);
  }
};

int main(void) {

  print_pos(LEFT);
  print_pos(CENTER);
  print_pos(RIGHT);

  Person person = {
      .full_name = "Tom Dom",
      .wage = 50,
  };

  print_person(person);

  return 0;
}

// Konya

/*
Left
Center
Right
Person named Tom Dom is middle class
*/
