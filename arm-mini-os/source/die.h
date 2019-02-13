#ifndef DIE_H_
#define DIE_H_

#include "uart.h"

// Stop system and loop forever, intermittently displaying a message.
void die(const char* message);

#endif  // DIE_H_
