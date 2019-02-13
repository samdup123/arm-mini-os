#define LOGGING_USE_STDOUT 1
#include "calc.h"
#include "utils.h"

#include <assert.h>
#include <stddef.h>

// replacments for ARM assembly functions:
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

void atoi_test() {
  assert(atoi("32768") == 32768);
  assert(atoi("32767") == 32767);
  assert(atoi("25") == 25);
  assert(atoi("1") == 1);
  assert(atoi("0") == 0);
  assert(atoi("-0") == -0);
  assert(atoi("-1") == -1);
  assert(atoi("-25") == -25);
  assert(atoi("-32768") == -32768);
  assert(atoi("-32769") == -32769);
}

void parse_calc_expr_test() {
  calculator_expression_t expr;

  // test all operators
  expr = parse_calc_expr("1 + 1");
  assert(expr.a == 1);
  assert(expr.op == '+');
  assert(expr.b == 1);
  expr = parse_calc_expr("1 - 1");
  assert(expr.a == 1);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("1 * 1");
  assert(expr.a == 1);
  assert(expr.op == '*');
  assert(expr.b == 1);
  expr = parse_calc_expr("1 / 1");
  assert(expr.a == 1);
  assert(expr.op == '/');
  assert(expr.b == 1);

  // LEFT operand edge cases
  expr = parse_calc_expr("-32769 - 1");
  assert(expr.a == -32769);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("-32768 - 1");
  assert(expr.a == -32768);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("-1 - 1");
  assert(expr.a == -1);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("-0 - 1");
  assert(expr.a == -0);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("0 - 1");
  assert(expr.a == 0);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("1 - 1");
  assert(expr.a == 1);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("32767 - 1");
  assert(expr.a == 32767);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("32768 - 1");
  assert(expr.a == 32768);
  assert(expr.op == '-');
  assert(expr.b == 1);

  // RIGHT operand edge cases
  expr = parse_calc_expr("-32769 - -32769");
  assert(expr.a == -32769);
  assert(expr.op == '-');
  assert(expr.b == -32769);
  expr = parse_calc_expr("-32768 - -32768");
  assert(expr.a == -32768);
  assert(expr.op == '-');
  assert(expr.b == -32768);
  expr = parse_calc_expr("-1 - -1");
  assert(expr.a == -1);
  assert(expr.op == '-');
  assert(expr.b == -1);
  expr = parse_calc_expr("-0 - -0");
  assert(expr.a == -0);
  assert(expr.op == '-');
  assert(expr.b == -0);
  expr = parse_calc_expr("0 - 0");
  assert(expr.a == 0);
  assert(expr.op == '-');
  assert(expr.a == 0);
  expr = parse_calc_expr("1 - 1");
  assert(expr.a == 1);
  assert(expr.op == '-');
  assert(expr.a == 1);
  expr = parse_calc_expr("32767 - 32767");
  assert(expr.a == 32767);
  assert(expr.op == '-');
  assert(expr.a == 32767);
  expr = parse_calc_expr("32768 - 32768");
  assert(expr.a == 32768);
  assert(expr.op == '-');
  assert(expr.a == 32768);

  // prefix (+) sign
  expr = parse_calc_expr("+32768 - +1");
  assert(expr.a == 32768);
  assert(expr.op == '-');
  assert(expr.b == 1);
  expr = parse_calc_expr("+32767 - +0");
  assert(expr.a == 32767);
  assert(expr.op == '-');
  assert(expr.b == 0);
}

// RUN ALL TESTS:

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main() {
  // tests here:
  void (*tests[])() = {
      atoi_test,
      parse_calc_expr_test,
  };

  const size_t num_tests = sizeof(tests) / sizeof(tests[0]);
  for (size_t i = 0; i < num_tests; ++i) {
    printf("test %lu: ", i + 1);
    tests[i]();
    printf(ANSI_COLOR_GREEN "✔ Success" ANSI_COLOR_RESET "\n");
  }

  if (num_tests < 1)
    printf("No tests found.");
  else
    printf(ANSI_COLOR_GREEN "All tests successful.\n" ANSI_COLOR_RESET);
  return 0;
}
