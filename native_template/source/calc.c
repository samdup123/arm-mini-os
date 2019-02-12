/**
 * Instructor:  Eugene Rockey
 * Author:      Nolan Holden
 * Assignment:  Lab 1
 */

#include <stdio.h>
#include <stdlib.h>

// terminates the program with a custom message
void die(const char* msg) {
  printf("fatal: %s\n", msg ? msg : "unspecified error");
  exit(EXIT_FAILURE);
}
// conditionally terminates the program with a custom message
void dieif(int should_die, const char* msg) { if (should_die) die(msg); }

// ARM assembly-implemented functions
extern int
  add(int a, int b),                            // --> a + b
  sub(int a, int b),                            // --> a - b
  mul(int a, int b),                            // --> a * b
  div_remainder(int a, int b, int* remainder);  // --> a / b, remainder=(a % b)

// calculate the result with the given mathematic operator
int calculate(int a, unsigned char operator, int b, int* const remainder) {
  switch (operator) {
    case '+': return add(a, b);
    case '-': return sub(a, b);
    case '*': return mul(a, b);
    case '/': return div_remainder(a, b, remainder);
    default: die("operator not recognized");
  }
}

int main(void) {
  // print menu/instructions
  printf("Enter an expression: (a {+|-|*|/} b)");

  int a = 0, b = 0, remainder = -1;  // parsed values and divmod remainder
  unsigned char operator = '\0';     // parse input operator

  // continuously evaluate expressions, until a signal
  while (1) {
    // prompt user for the expression 
    printf("\n> ");

    // parse the expression
    dieif(scanf("%d %c %d", &a, &operator, &b) < 0, "bad expression");

    // calculate & print result (inc. remainder for '/')
    printf("%d", calculate(a, operator, b, &remainder));
    if (remainder >= 0) {  // if remainder was set to a sane value
      printf(" [remainder = %d]", remainder);  // express the remainder
      remainder = -1;  // set back to a not-sane value
    }
  }
}

