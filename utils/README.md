 # C Utilities Library

This C library provides a collection of utility functions for various common tasks. It includes functions for counting lines in a file, calculating the greatest common divisor (GCD) and least common multiple (LCM) of two numbers, sorting and reversing arrays, splitting numbers into their individual digits, removing prefixes and suffixes from strings, converting integers to strings and vice versa, and more.

## Installation

To use this library, simply include the `rayutils.h` header file in your C source code.

## Usage

### Counting Lines in a File

The `countlines` function counts the number of lines in a text file. It takes the name of the file as an argument and returns the number of lines in the file.

```c
#include "rayutils.h"

int main() {
  int num_lines = countlines("myfile.txt");
  printf("Number of lines in myfile.txt: %d\n", num_lines);

  return 0;
}
```

### Calculating GCD and LCM

The `pgcd` and `ppcm` functions calculate the greatest common divisor (GCD) and least common multiple (LCM) of two numbers, respectively. They take two integers as arguments and return the GCD or LCM of the two numbers.

```c
#include "rayutils.h"

int main() {
  int a = 12;
  int b = 18;

  int gcd = pgcd(a, b);
  int lcm = ppcm(a, b);

  printf("GCD of %d and %d: %d\n", a, b, gcd);
  printf("LCM of %d and %d: %d\n", a, b, lcm);

  return 0;
}
```

### Sorting and Reversing Arrays

The `sort` and `reverse` functions sort and reverse an array of integers, respectively. They take an array and its size as arguments and modify the array in place.
