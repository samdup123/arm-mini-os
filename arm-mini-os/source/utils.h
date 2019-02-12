#ifndef UTILS_H_
#define UTILS_H_

#define PRINTF_DISABLE_SUPPORT_LONG_LONG
#include "custom_printf.h"

#define nullptr 0

// terminates the program with a custom message
void die(void (*print_fn)(const char *), const char *msg) {
  const char *const error_message = msg ? msg : "unspecified error";
  while (1) {
    print_fn("\nfatal: ");
    print_fn(error_message);
  }
}
// conditionally terminates the program with a custom message
void dieif(int should_die, void (*print_fn)(const char *), const char *msg) {
  if (should_die) die(print_fn, msg);
}

#endif  // UTILS_H_