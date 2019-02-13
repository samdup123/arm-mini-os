#ifndef UTILS_H_
#define UTILS_H_

#include "custom_printf.h"

#define nullptr 0

#define DEBUG 1

#define LOG(level, format, ...)                                           \
  do {                                                                    \
    if (DEBUG) {                                                          \
      uart_printf("[" #level "] %s:%d:%s(): " format, __FILE__, __LINE__, \
                  __func__, __VA_ARGS__);                                 \
    }                                                                     \
  } while (0)

// terminates the program with a custom message
void die(void (*print_fn)(const char *), const char *msg);

// conditionally terminates the program with a custom message
void dieif(int should_die, void (*print_fn)(const char *), const char *msg);

#endif  // UTILS_H_
