#ifndef CALC_H_
#define CALC_H_

#include "utils.h"

// ARM assembly-implemented functions
extern int add(int a, int b),  // --> a + b
    sub(int a, int b),         // --> a - b
    mul(int a, int b),         // --> a * b
    // TODO: add assembly function for this
    div_remainder(int a, int b,
                  int *remainder);  // --> a / b, remainder=(a % b)

// calculate the result with the given mathematic operator
int calculate(int a, unsigned char op, int b, int *const remainder,
              void (*print_fn)(const char *)) {
  switch (op) {
    case '+':
      return add(a, b);
    case '-':
      return sub(a, b);
    case '*':
      return mul(a, b);
    case '/':
      // TODO: support division
      die(print_fn, "division not implemented");
      // return div_remainder(a, b, remainder);
    default:
      die(print_fn, "operator not recognized");
  }
}

int calculator(void (*print_fn)(const char *)) {
  // print menu/instructions
  print_fn("Enter an expression: (a {+|-|*|/} b)");

  int a = 0, b = 0, remainder = -1;  // parsed values and divmod remainder
  unsigned char op = '\0';           // parse input operator

  // continuously evaluate expressions, until a signal
  while (1) {
    // prompt user for the expression
    print_fn("\n> ");

    // parse the expression
    // dieif(scanf("%d %c %d", &a, &operator, &b) < 0, "bad expression");

    // calculate & print result (inc. remainder for '/')
    // printf("%d", calculate(a, operator, b, &remainder));
    if (remainder >= 0) {  // if remainder was set to a sane value
      // printf(" [remainder = %d]", remainder);  // express the remainder
      remainder = -1;  // set back to a not-sane value
    }
  }
}

#endif  // CALC_H_
