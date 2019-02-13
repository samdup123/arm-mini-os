#ifndef CUSTOM_PRINTF_H_
#define CUSTOM_PRINTF_H_

#include <stdarg.h>
#include <stddef.h>

// This is the crux of the printf implementation for this lab.
// Synchronously writes a byte to serial.
void custom_putchar(char c);

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

#endif  // CUSTOM_PRINTF_H_
