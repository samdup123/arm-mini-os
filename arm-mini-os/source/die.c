#include "die.h"

#include "uart.h"

void die(const char* message) {
  const char* const msg = message ? message : "unspecified error";
  while (1) {
    uart_puts("\n\rfatal: ");
    uart_puts("stopping system and looping forever: ");
    uart_puts(msg);

    /* delaying slightly */
    for (int count = 0xFFFFF; --count > 0;)
      for (int count2 = 4; --count2 > 0;)
        ;
  }
}