#include "utils.h"

log_level_t min_logging_level = 0;

int is_space(char c) { return c == ' ' || c == '\t'; }
int is_digit(char c) { return c >= '0' && c <= '9'; }
int is_allowed_number_character(char c) { return is_digit(c) || c == '-'; }

int char_to_int(char c) { return c - '0'; }

// - fails on null or empty string
// - `number_end` is assigned the first char in the input buffer after the
// number.
int atoi_to_end(const char* const number, const char** number_end) {
  CHECK(number != nullptr, "%s", "atoi called with null string");
  CHECK(*number != '\0', "%s", "atoi called with empty string");

  const char* pos = number;
  while (is_space(*pos)) ++pos;  // permit and skip over leading space

  const int number_is_negative = (*pos == '-');
  const char* const most_significant_digit =
      (number_is_negative || (*pos == '+')) ? (pos + 1) : pos;
  CHECK(is_digit(*most_significant_digit),
        "atoi_to_end() input string [%s] is malformed", number);

  // Find the least significant digit (farthest right).
  const char* least_significant_digit = most_significant_digit;
  while (is_digit(least_significant_digit[1])) ++least_significant_digit;
  ;
  if (number_end) *number_end = (least_significant_digit + 1);

  // Accumulate the total moving from least significant to most significant
  // digit (right to left).
  int magnitude = 0;
  const char* riterator = least_significant_digit;
  int digit_weight = 1;  // 10^0, 10^1, 10^2, ...
  // TODO: are we ok with overflow?
  for (; riterator >= most_significant_digit; --riterator, digit_weight *= 10) {
    magnitude += (char_to_int(*riterator) * digit_weight);
  }

  return number_is_negative ? -magnitude : magnitude;
}

int atoi(const char* const number) { return atoi_to_end(number, nullptr); }