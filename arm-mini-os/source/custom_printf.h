#ifndef CUSTOME_PRINTF_H_
#define CUSTOME_PRINTF_H_

#include "uart.h"

#include <stdarg.h>
#include <stddef.h>

// This is the crux of the printf implementation for this lab.
// Synchronously writes a byte to serial.
void _putchar(char c) { uart_putc((uint8_t)c); }

#define uart_printf printf_
int printf_(const char* format, ...);

#define sprintf sprintf_
int sprintf_(char* buffer, const char* format, ...);

#define snprintf snprintf_
#define vsnprintf vsnprintf_
int snprintf_(char* buffer, size_t count, const char* format, ...);
int vsnprintf_(char* buffer, size_t count, const char* format, va_list va);

int fctprintf(void (*out)(char character, void* arg), void* arg,
              const char* format, ...);

#endif  // CUSTOME_PRINTF_H_
