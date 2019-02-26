#include "die.h"

#include "uart.h"

void die(void (*print_fn)(const char*), const char* message) {
  const char* const msg = message ? message : "unspecified error";
  while (1) {
    print_fn("\n\rfatal: stopping system and looping forever: ");
    print_fn(msg);

    /* delaying slightly */
    for (int count = 0xFFFFF; --count > 0;)
      for (int count2 = 4; --count2 > 0;)
        ;
  }
}