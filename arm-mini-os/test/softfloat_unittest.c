#define TEST_NO_ARM 1
#include "softfloat.h"
#include "utils.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define str_to_i  ASCII_to_float32
#define cut float32_to_ASCII

void float32_to_ASCII_test() {
    char buf[40];
    cut(str_to_i("7.125"), buf);
    assert(0 == strcmp(buf, "7.125"));

    cut(str_to_i("-7.125"), buf);
    assert(0 == strcmp(buf, "-7.125"));

    // .05
    cut(0b00111101010011001100110011001100, buf);
    assert(0 == strcmp(buf, ".0499999"));

    //-.05
    cut(0b10111101010011001100110011001100, buf);
    assert(0 == strcmp(buf, "-.0499999"));

    // .00625
    cut(0b00111011110011001100110011001100, buf);
    assert(0 == strcmp(buf, ".0062499"));

    cut(str_to_i("7.034"), buf);
    assert(0 == strcmp(buf, "7.0339994"));

    cut(str_to_i("-7.034"), buf);
    assert(0 == strcmp(buf, "-7.0339994"));

    cut(str_to_i("-237.034"), buf);
    assert(0 == strcmp(buf, "-237.0339965"));
}

// RUN ALL TESTS:

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main() {
  // tests here:
  void (*tests[])() = {
      float32_to_ASCII_test,
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
