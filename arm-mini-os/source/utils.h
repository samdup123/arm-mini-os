#ifndef UTILS_H_
#define UTILS_H_

#include "custom_printf.h"

#define nullptr 0

// terminates the program with a custom message
void die(void (*print_fn)(const char *), const char *msg);

// conditionally terminates the program with a custom message
void dieif(int should_die, void (*print_fn)(const char *), const char *msg);

#define LOGGING_ENABLED 1

typedef enum {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,  // terminates the program
} log_level_t;

extern log_level_t min_logging_level;

// Usage:
//   LOG(ERROR, "expected 100, got %d", 101);
//
// Above would output to terminal:
//  --> [ERROR] your_file.c:34:your_function(): expected 100, got 101
#define LOG(level, format, ...)                                              \
  do {                                                                       \
    if (LOGGING_ENABLED) {                                                   \
      const log_level_t log_level = LOG_LEVEL_##level;                       \
      const int is_fatal = (log_level == LOG_LEVEL_FATAL);                   \
      const int should_print = is_fatal || (log_level >= min_logging_level); \
      if (should_print) {                                                    \
        uart_printf("\n\r[" #level "] %s:%d:%s(): " format, __FILE__,        \
                    __LINE__, __func__, __VA_ARGS__);                        \
      }                                                                      \
      if (is_fatal) {                                                        \
        /* print fatal message forever */                                    \
        while (1) {                                                          \
          uart_printf("\n\rfatal: stopping system and looping forever");     \
                                                                             \
          /* delaying slightly */                                            \
          for (int count = 0xFFFFF; --count > 0;)                            \
            for (int count2 = 4; --count2 > 0;)                              \
              ;                                                              \
        }                                                                    \
      }                                                                      \
    }                                                                        \
  } while (0)

#define CHECK_FMT(expr, format, ...)                                    \
  do {                                                                  \
    const int ok = (expr);                                              \
    if (!ok) {                                                          \
      LOG(FATAL, "CHECK_EQ failed for expression `" #expr "`: " format, \
          __VA_ARGS__);                                                 \
    }                                                                   \
  } while (0)

#define CHECK(expr)                         \
  do {                                      \
    CHECK_FMT(expr, "%s", "(unspecified)"); \
  } while (0)

#endif  // UTILS_H_
