#ifndef UTILS_H_
#define UTILS_H_

#include "custom_printf.h"

#define nullptr 0

#define LOGGING_ENABLED 1

typedef enum {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,
} log_level_t;

log_level_t min_logging_level = LOG_LEVEL_DEBUG;

// Usage:
//   LOG(ERROR, "expected 100, got %d", 101);
//
// Above would output to terminal:
//  --> [ERROR] your_file.c:34:your_function(): expected 100, got 101
#define LOG(level, format, ...)                                       \
  do {                                                                \
    if (LOGGING_ENABLED) {                                            \
      const log_level_t log_level = LOG_LEVEL_##level;                \
      if (log_level >= min_logging_level) {                           \
        uart_printf("\r\n[" #level "] %s:%d:%s(): " format, __FILE__, \
                    __LINE__, __func__, __VA_ARGS__);                 \
      }                                                               \
    }                                                                 \
  } while (0)

// terminates the program with a custom message
void die(void (*print_fn)(const char *), const char *msg);

// conditionally terminates the program with a custom message
void dieif(int should_die, void (*print_fn)(const char *), const char *msg);

#endif  // UTILS_H_
