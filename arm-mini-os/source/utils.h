#ifndef UTILS_H_
#define UTILS_H_

#include <time.h>

#define nullptr 0

#define debug_print(fmt, ...)                                           \
  do {                                                                  \
    if (DEBUG)                                                          \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, \
              __VA_ARGS__);                                             \
    time(0);                                                            \
  } while (0)

// terminates the program with a custom message
void die(void (*print_fn)(const char *), const char *msg);

// conditionally terminates the program with a custom message
void dieif(int should_die, void (*print_fn)(const char *), const char *msg);

#endif  // UTILS_H_
