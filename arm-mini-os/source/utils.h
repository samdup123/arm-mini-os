#ifndef UTILS_H_
#define UTILS_H_

#include "die.h"

#ifdef LOGGING_USE_STDOUT
#include <stdio.h>
#define LOGGING_PRINTF_FUNC printf
#else
#include "custom_printf.h"
#define LOGGING_PRINTF_FUNC uart_printf
#endif

#define nullptr 0

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
#define LOG(level, format, ...)                                               \
  do {                                                                        \
    if (LOGGING_ENABLED) {                                                    \
      const log_level_t log_level = LOG_LEVEL_##level;                        \
      const int is_fatal = (log_level == LOG_LEVEL_FATAL);                    \
      const int should_print = is_fatal || (log_level >= min_logging_level);  \
      if (should_print) {                                                     \
        LOGGING_PRINTF_FUNC("\n\r[" #level "] %s:%d:%s(): " format, __FILE__, \
                            __LINE__, __func__, __VA_ARGS__);                 \
      }                                                                       \
      if (is_fatal) {                                                         \
        /* print fatal message forever */                                     \
        void print_fn(const char* msg) { LOGGING_PRINTF_FUNC("%s", msg); }    \
        die(print_fn, "due to call to LOG(FATAL, ...)");                      \
      }                                                                       \
    }                                                                         \
  } while (0)

#define CHECK(expr, format, ...)                                     \
  do {                                                               \
    const int ok = (expr);                                           \
    if (!ok) {                                                       \
      LOG(FATAL, "CHECK failed for expression `" #expr "`: " format, \
          __VA_ARGS__);                                              \
    }                                                                \
  } while (0)

// PARSING:

int is_space(char c);

int is_digit(char c);

int is_allowed_number_character(char c);

int char_to_int(char c);

// - fails on null or empty string
// - `number_end` is assigned the first char in the input buffer after the
// number.
int atoi_to_end(const char* const number, const char** number_end);

int atoi(const char* const number);

#endif  // UTILS_H_
