#include <cmath>
#include <print>

// A small threshold to consider two floating-point numbers equal
const long double EPSILON = 0.00001;

class cm {
private:
  long double value;

public:
  cm(long double value) : value(value) {}

  // Getter for cm
  long double getCm() const { return value; }

  // Convert Cm to Inches
  long double toInches() const { return value / 2.54; }

  long double difference(const cm &other) {
    long double diff = std::abs(value - other.value);

    if (diff < EPSILON) {
      return 0;
    } else {
      return diff;
    }
  }
};

class in {
private:
  long double value;

public:
  in(long double value) : value(value) {}

  // Getter for inches
  double getInches() const { return value; }

  // Convert Inches to Cm
  long double toCm() const { return value * 2.54; }

  long double difference(const in &other) {
    long double diff = std::abs(value - other.value);

    if (diff < EPSILON) {
      return 0;
    } else {
      return diff;
    }
  }
};

void print_difference(long double result) {
  if (result == 0) {
    std::println("The values are roughly equal.");
  } else if (result > 0) {
    std::println("{:f}", result);
  } else {
    std::println("{:f}", -result);
  }
}

int main() {
  long double result_cm = 0;
  long double result_in = 0;

  long double hundred = 100;
  long double thirtyNine = 39.37008;
  long double one = 1;

  std::println("Comparing with Epsilon: {:f}", EPSILON);

  std::println("");
  std::println("========");
  std::println("");

  std::println("Comparing {}cm to {}in.", hundred, thirtyNine);
  std::println("");

  cm hundred_cm = cm(hundred);
  in hundred_cm_in_inches = in(thirtyNine);

  std::println("{}cm in in: {}", hundred, hundred_cm.toInches());
  std::println("{}in in cm: {}", thirtyNine, hundred_cm_in_inches.toCm());

  result_cm = hundred_cm.difference(hundred_cm_in_inches.toCm());
  result_in = hundred_cm_in_inches.difference(hundred_cm.toInches());

  std::println("Difference in cm:");
  print_difference(result_cm);
  std::println("Difference in inches:");
  print_difference(result_in);

  std::println("");
  std::println("========");
  std::println("");

  std::println("Comparing {}cm to {}in.", one, one);
  std::println("");

  cm one_cm = cm(one);
  in one_inch = in(one);

  std::println("{}in in cm: {}", one_inch.getInches(), one_inch.toCm());
  std::println("{}cm in in: {}", one_cm.getCm(), one_cm.toInches());

  result_cm = one_cm.difference(one_inch.toCm());
  result_in = one_inch.difference(one_cm.toInches());

  std::println("Difference in cm:");
  print_difference(result_cm);
  std::println("Difference in inches:");
  print_difference(result_in);

  std::println("");
  std::println("========");
  return 0;
}

// Konya

// Expected output:

/*
Comparing with Epsilon: 0.000010

========

Comparing 100cm to 39.37008in.

100cm in in: 39.37007874015748
39.37008in in cm: 100.00000320000001
Difference in cm:
The values are roughly equal.
Difference in inches:
The values are roughly equal.

========

Comparing 1cm to 1in.

1in in cm: 2.54
1cm in in: 0.39370078740157477
Difference in cm:
1.540000
Difference in inches:
0.606299

========
*/
