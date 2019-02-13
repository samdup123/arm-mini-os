#include "utils.h"

log_level_t min_logging_level = 0;

void die(void (*print_fn)(const char *), const char *msg) {
  const char *const error_message = msg ? msg : "unspecified error";
  while (1) {
    print_fn("\nfatal: ");
    print_fn(error_message);
  }
}

void dieif(int should_die, void (*print_fn)(const char *), const char *msg) {
  if (should_die) die(print_fn, msg);
}
