#include "calc.h"

calculator_expression_t parse_calc_expr(const char *const expression) {
  calculator_expression_t expr = {
      .a = -1,
      .b = -1,
      .op = '\0',
  };

  const char *pos = expression;

  // refuse null or empty
  CHECK(expression != nullptr);
  CHECK(*expression != '\0');

  // parse `a`
  expr.a = atoi_to_end(pos, &pos);
  // permit for any space between `a` and `operator`
  while (is_space(*pos)) ++pos;
  // parse `op`
  expr.op = *pos++;
  // parse `b`
  expr.b = atoi(pos);

  return expr;
}

int calculate(const calculator_expression_t *expr, int *const remainder) {
  switch (expr->op) {
    case '+':
      return add(expr->a, expr->b);
    case '-':
      return sub(expr->a, expr->b);
    case '*':
      return mul(expr->a, expr->b);
    case '/':
      // TODO: support division
      LOG(FATAL, "%s", "division not implemented");
    default:
      LOG(FATAL, "%s", "operator not recognized");
  }
}

int calculator(void (*print_fn)(const char *, ...)) {
  // print menu/instructions
  print_fn("\n\rEnter an expression: (a {+|-|*|/} b)");

  calculator_expression_t expr = {
      .a = 0,
      .b = 0,
      .op = '\0',
  };

  int division_remainder = -1;

  // continuously evaluate expressions
  while (1) {
    print_fn("\n\r> ");  // user prompt

    // parse the expression
    // dieif(scanf("%d %c %d", &a, &operator, &b) < 0, "bad expression");

    // calculate & print result (inc. remainder for '/')
    print_fn("%d", calculate(&expr, &division_remainder));
    if (division_remainder >= 0) {  // if remainder was set to a sane value
      print_fn(" [remainder = %d]", division_remainder);
      division_remainder = -1;  // set back to a not-sane value
    }
  }
}