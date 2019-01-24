#include <stdio.h>
#include <stdlib.h>

void die(const char* msg) {
  printf("fatal: %s\n", msg ? msg : "unspecified error");
  exit(EXIT_FAILURE);
}
void dieif(int should_die, const char* msg) { if (should_die) die(msg); }

extern int
  add(int a, int b),                            // --> a + b
  sub(int a, int b),                            // --> a - b
  mul(int a, int b),                            // --> a * b
  div_remainder(int a, int b, int* remainder);  // --> a / b, remainder=(a % b)

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
  printf("Enter an expression: (a {+|-|*|/} b)");

  int a = 0, b = 0, remainder = -1;
  unsigned char operator = '\0';
  while (1) {
    printf("\n> ");
    dieif(scanf("%d %c %d", &a, &operator, &b) < 0, "bad expression");

    printf("%d", calculate(a, operator, b, &remainder));
    if (remainder >= 0) {
      printf(" [remainder = %d]", remainder);
      remainder = -1;
    }
  }
}
